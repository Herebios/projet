/**
 * @file serv.c
 * @author Baptiste
 * @brief code principal du serveur
 */
#include "serv_socket.h"
#include "serv_jeu.h"

int main_server(int nb_clients) {
	//setup socket
	int error_code;
	if ((error_code = setup_server()) > 0){
		//sortie avec libération adaptée
		fermeture_server(error_code);
		return error_code;
	}
	//le server est prêt, on va s'occuper des clients
	puts("setup server OK\n");
	printf("Nombre de clients : %d, pas de place libérée quand déconnexion\n", nb_clients);flush;
	clients = malloc(sizeof(socket_struct) * nb_clients);

	serv_file = newFile();

	server.nb_clients=0;
	server.server_struct.online=1;
	server.nb_on=0;

	pthread_create(&server.server_struct.thread, NULL, accept_thread, &nb_clients);
	//nouv clients thread

	char buffer[BUFFERLEN]="Il y a ";
	while(server.nb_clients < nb_clients){
		printf("%d", server.nb_clients);flush;
		sprintf(buffer + 7, "%d", server.nb_clients);
		strcat(buffer, " clients !");
		broadcast(buffer, -1);
		sleep(1);
	}
	server.nb_on=nb_clients;
	//à partir d'ici on peut utiliser server.nb_clients (global)
	broadcast("start", -1);

	srand(time(0));
	int random_seed = rand();
	//Chaque client reçoit son indice et la seed random
	for (int i=0; i<nb_clients; i++) {
		sprintf(buffer, "%d %d %d", i, nb_clients, random_seed);
		send(clients[i].socket, buffer, strlen(buffer), 0);
	}

	perso_t joueurs[nb_clients];
	init_joueurs_server(joueurs, nb_clients);
	send_joueurs_server(joueurs, nb_clients);
	puts("Joueurs :");
	for(int i=0; i<nb_clients; i++){
		printf("ind %d , classe %d , nom %s , equipe %d\n", i, joueurs[i].classe, joueurs[i].nom, joueurs[i].equipe);
	}
	flush;
	/*on[i] correspond à clients[i].online, pour mémoriser lequels sont off et ne les compter qu'une fois
	on décrémente nb_on, qui est incrémenté quand le thread accepte un nouveau client
	quand nb_on sera à 0 et premier_client à 1, le serveur s'arrêtera
	*/
	char * data;
	int ind_j;//ind du joueur qui envoie
	int action;
	int compteur=0;

//<<	init_jeu();
	while (server.nb_on){
		while(!fileVide(serv_file)){
			data=defiler(serv_file);
			sscanf(data, "%d %d", &ind_j, &action);
			switch(action){
				case JOUEUR_CHANGE_DIR:
					sscanf(data_skip(data, 2), "%d", (int*)&joueurs[ind_j].dir);
					break;
				case ADD_OBJET:{
					int ind_o;
					sscanf(data_skip(data, 2), "%d", &ind_o);
					ajouter_objet(joueurs + ind_j, ind_o);
					update_stats(joueurs + ind_j);
					break;
				}
				case RM_OBJET:{
					int ind_inv, ind_o;
					sscanf(data_skip(data, 2), "%d", &ind_inv);
					ind_o = joueurs[ind_j].objets[ind_inv]->ind;
					retirer_objet(joueurs + ind_j, ind_inv);
					update_stats(joueurs + ind_j);

					//on ajoute l'objet sur la tuile
					pos_t pos_tuile;
					position_perso(joueurs + ind_j, &pos_tuile);
					spawn_objet((rarete_t)rand()%4, 1, ind_o, joueurs[ind_j].pos_map, pos_tuile);
					break;
				}
			}
			free(data);
		}

		//gerer les deco
		server.nb_on=server.nb_clients;
		for (int i=0; i<server.nb_clients; i++){
			if(!clients[i].online){
				server.nb_on--;
			}
		}

/*		//bouger les joueurs
		for(int i=0; i<nb_clients; i++){
			avancer(joueurs+i);
		}

		//evenements
		if(compteur >= 2000){
			puts("Spawn obj\n");flush;
			spawn_objet(commun);
			compteur=0;
		}else
			compteur+=DELAY;
*/
		SDL_Delay(DELAY);
	}
	puts("fin boucle");flush;

	detruire_joueurs_server(joueurs, nb_clients);
	//libération complète
	fermeture_server(0);
	return 0;
}

int main(int argc, char *argv[]){
	main_server(2);
	return 0;
}
