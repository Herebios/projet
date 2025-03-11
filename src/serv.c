#include "servHandler.h"

int main_server() {
	//setup socket
	info_server server;
	int error_code;
	if ((error_code = setup_server(&server)) > 0){
		//sortie avec libération adaptée
		fermeture_server(error_code, &server, NULL);
		return error_code;
	}
	//le server est prêt, on va s'occuper des clients
	puts("setup server OK\n");
	printf("Nombre de clients max : %d, pas de place libérée quand déconnexion\n", NB_CLIENTS);flush;
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

	int i;

	char buffer[32]="Il y a ";
	while(server.nb_clients < NB_CLIENTS){
		printf("%d", server.nb_clients);flush;
		sprintf(buffer + 7, "%d", server.nb_on);
		strcat(buffer, " clients !");
		broadcast(buffer, &server, clients);
		sleep(1);
	}
	broadcast("start", &server, clients);

	//Chaque client reçoit son indice
	for (i=0; i<NB_CLIENTS; i++) {
		sprintf(buffer, "%d", i);
		send(clients[i].socket, buffer, strlen(buffer), 0);
	}

/*	perso_t joueurs[NB_CLIENTS];
	init_joueurs_server(joueurs, NB_CLIENTS);
	send_joueurs_server(server, clients, joueurs, NB_CLIENTS);
*/
	/*on[i] correspond à clients[i].online, pour mémoriser lequels sont off et ne les compter qu'une fois
	on décrémente nb_on, qui est incrémenté quand le thread accepte un nouveau client
	quand nb_on sera à 0 et premier_client à 1, le serveur s'arrêtera
	*/
	char * data;
	while (server.nb_on){
		for (i=0; i<server.nb_clients; i++){
			if(server.clients_on[i] && !clients[i].online){
				server.nb_on--;
				server.clients_on[i]=0;
			}
		}
		sleep(1);
		while(!fileVide(serv_file)){
			data=defiler(serv_file);
			printf("Message : '%s'\n", data);
			free(data);
		}
		flush;
	}

	//libération complète
	fermeture_server(0, &server, clients);
	sleep(1);
	return 0;
}

int main(){
	main_server();
	return 0;
}
