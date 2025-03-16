/**
 * @file serv.c
 * @author Baptiste
 * @brief code principal du serveur
 */
#include "serv_socket.h"
#include "serv_jeu.h"

int main_server() {
	//setup socket
	info_server server;
	int error_code;
	if ((error_code = setup_server(&server)) > 0){
		//sortie avec libération adaptée
		fermeture_server(&server, NULL, error_code);
		return error_code;
	}
	//le server est prêt, on va s'occuper des clients
	puts("setup server OK\n");
	printf("Nombre de clients : %d, pas de place libérée quand déconnexion\n", NB_CLIENTS);flush;
	socket_struct clients[NB_CLIENTS];

	serv_file = newFile();

	server.nb_clients=0;
	server.premier_client=0;
	server.server_struct.online=1;
	server.nb_on=0;

	void* info=malloc(16);
	*(info_server**)info=&server;
	*(socket_struct**)(info+8)=clients;
	pthread_create(&server.server_struct.thread, NULL, accept_thread, info);
	//nouv clients thread

	char buffer[32]="Il y a ";
	while(server.nb_clients < NB_CLIENTS){
		printf("%d", server.nb_clients);flush;
		sprintf(buffer + 7, "%d", server.nb_on);
		strcat(buffer, " clients !");
		broadcast(buffer, &server, clients, -1);
		sleep(1);
	}
	broadcast("start", &server, clients, -1);

	//Chaque client reçoit son indice
	for (int i=0; i<NB_CLIENTS; i++) {
		sprintf(buffer, "%d %d", i, NB_CLIENTS);
		send(clients[i].socket, buffer, strlen(buffer), 0);
	}

	perso_t joueurs[NB_CLIENTS];
	init_joueurs_server(joueurs);
	send_joueurs_server(&server, clients, joueurs);
	for(int i=0; i<NB_CLIENTS; i++){
		printf("ind %d , classe %d , nom %s , equipe %d\n", i, joueurs[i].classe, joueurs[i].nom, joueurs[i].equipe);
	}
	flush;
	/*on[i] correspond à clients[i].online, pour mémoriser lequels sont off et ne les compter qu'une fois
	on décrémente nb_on, qui est incrémenté quand le thread accepte un nouveau client
	quand nb_on sera à 0 et premier_client à 1, le serveur s'arrêtera
	*/
	char * data;
	int ind;//ind du joueur qui envoie
	int action;
	puts("deb boucle");flush;
	while (server.nb_on){
		sleep(1);
		while(!fileVide(serv_file)){
			data=defiler(serv_file);
			sscanf(data, "%d %d", &ind, &action);
			switch(action){
				case ADD_OBJET:
				{
					int ind_o;
					sscanf(data_skip(data, 2), "%d", &ind_o);
					ajouter_objet(joueurs + ind, ind_o);
					update_stats(joueurs + ind);
					break;
				}
				case RM_OBJET:{
					int ind_inv;
					sscanf(data_skip(data, 2), "%d", &ind_inv);
					retirer_objet(joueurs + ind, ind_inv);
					update_stats(joueurs + ind);
					break;
				}
			}
			free(data);
		}

		//gerer les deco
		for (int i=0; i<server.nb_clients; i++){
			if(server.clients_on[i] && !clients[i].online){
				server.nb_on--;
				server.clients_on[i]=0;
			}
		}
	}
	puts("fin boucle");flush;
	afficher_objets_perso(joueurs);
	afficher_stats_perso(joueurs);

	detruire_joueurs_server(joueurs);
	//libération complète
	fermeture_server(&server, clients, 0);
	return 0;
}

int main(int argc, char *argv[]){
	main_server();
	return 0;
}
