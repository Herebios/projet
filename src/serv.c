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

	server.nb_clients=0;
	server.premier_client=0;
	server.server_struct.online=1;
	server.nb_on=0;

	void* info=malloc(16);
	*(info_server**)info=&server;
	*(socket_struct**)(info+8)=clients;
	pthread_create(&server.server_struct.thread, NULL, accept_thread, info);
	//nouv clients thread

	char t[30]="Il y a ";
	while(server.nb_clients < NB_CLIENTS){
		printf("%d", server.nb_clients);
		sprintf(t + 7, "%d", server.nb_on);
		strcat(t, " clients !");
		broadcast(t, &server, clients);
		sleep(3);
	}
	broadcast("start", &server, clients);

	while (1){
		sleep(1);
	}

	int i;
	/*on[i] correspond à clients[i].online, pour mémoriser lequels sont off et ne les compter qu'une fois
	on décrémente nb_on, qui est incrémenté quand le thread accepte un nouveau client
	quand nb_on sera à 0 et premier_client à 1, le serveur s'arrêtera
	*/
	while (server.nb_on){
		for (i=0; i<server.nb_clients; i++){
			if(server.clients_on[i] && !clients[i].online){
				server.nb_on--;
				server.clients_on[i]=0;
			}
		}
		sleep(1);
	}
	server.server_struct.online=0;//fermeture de accept_thread
	//sinon il est déjà fermé
	if(server.nb_clients < NB_CLIENTS){
		pthread_cancel(server.server_struct.thread);//déso
		sleep(1);
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
