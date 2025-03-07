#include "servHandler.h"

void broadcast(char *string, info_server *serv, socket_struct clients[NB_CLIENTS]){
	for (int i = 0; i < serv->nb_clients; i++){
		/*if (clients[i].online){
		}*/
		send(clients[i].socket, string, strlen(string), 0);
	}
}

void *client_thread(void *arg){
/*on récupère un pointeur sur nb_clients et le tableau de socket_struct clients avec l'indice du client courant*/
    int ind=*(int*)arg;
    int* nb_clients=*(int**)(arg+4);
    socket_struct* clients=*(socket_struct**)(arg+12);
    free(arg);
    printf("thread ecoute du client %d\n", ind);flush;

    int buff_size;
    char buffer[BUFFER_SIZE];
    bool valide=1;
    while(valide){
        buff_size = recv(clients[ind].socket, buffer, BUFFER_SIZE-1, 0);
        if(buff_size > 0){
            buffer[buff_size] = '\0';
            switch(*buffer){
                //signal qui met fin au thread, le client ind se déconnecte
                case '!': valide=0;break;
                //message normal
                default:
                    printf("%d)> '%s'\n", buff_size, buffer);flush;
                    for (int i=0; i < *nb_clients; i++) {
                    //on envoie à chaque client encore connecté qui n'est pas l'envoyeur
                        if(i!=ind && clients[i].online)
                            send(clients[i].socket, buffer, buff_size, 0);
                    }
            }
        }else{
            valide=0;
            printf("déconnexion brutale %d\n", ind);
        }
    }

    send(clients[ind].socket, "!", 1, 0);//ferme le thread d'écoute du client
    printf("fin %d\n", ind);flush;
    clients[ind].online=0;//pour savoir quels clients il reste et arrêter le server
    return NULL;
}


void *accept_thread(void *arg){
    info_server* server=*(info_server**)arg;
    socket_struct* clients=*(socket_struct**)(arg+8);
    free(arg);

    //nb_clients correspond aussi à l'indice du nouveau client qu'on traite, numéro nb_clients+1
    int nb_clients, addr_size=sizeof(struct sockaddr_in);

    /*Boucle pour accepter de nouveaux clients, lance un thread pour chaque.
    S'arrête grâce au champ online de la socket_struct du server qui dépend
    de la boucle du programme principal qui regarde si tous les clients sont déconnectés.
    On ferme le thread si le nombre max de clients est atteint*/

    while (server->server_struct.online && server->nb_clients < NB_CLIENTS){
        //il n'y a pas de sleep dans la boucle car elle bloque sur accept() ou se ferme
        nb_clients=server->nb_clients;
        if ((clients[nb_clients].socket = accept(server->server_struct.socket, (struct sockaddr *)&clients[nb_clients].addr, &addr_size)) != -1){

            //informations pour la boucle principale
            server->clients_on[nb_clients]=1;
            server->nb_on++;
            server->premier_client=1;
            clients[nb_clients].online=1;

            //on envoie dans le thread:
            void* info=malloc(20);
            *(int*)info=nb_clients;//l'indice du client dont il s'occupe
            *(int**)(info+4)=&server->nb_clients;//pointeur sur le nombre de clients
/*on pourrait récupérer l'indice du client par le pointeur mais nb_clients sera incrémenté juste après,
donc on passe directement l'indice du client en paramètre pour être sûr d'avoir la bonne valeur*/
            *(socket_struct**)(info+12)=clients;//le tableau de socket_struct des clients
            pthread_create(&clients[nb_clients].thread, NULL, client_thread, info);

            printf("client %d\n", server->nb_clients++);flush;
        }
    }
    printf("fin thread accept\n");flush;
    return NULL;
}

void fermeture_server(int error_code, info_server * server, socket_struct * clients){
/*
code 0 est le comportement normal, on détruit tout à la fin
server est fantôme si code 1 ou 2
clients est NULL si code != 0
*/
    printf("libération\n");
    switch(error_code){
case 0:
    for (int i=0; i<server->nb_clients; i++)
    #ifdef _WIN32
    closesocket
    #else
    close
    #endif
    (clients[i].socket);
case 4:
case 3:
    #ifdef _WIN32
    closesocket
    #else
    close
    #endif
    (server->server_struct.socket);
case 2:
    #ifdef _WIN32
    WSACleanup();
    #endif
case 1:
    break;
    }
}

int setup_server(info_server * server){
    //uniquement pour windows
    #ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa))
        return 1;
    #endif

    if ((server->server_struct.socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        return 2;
    }
    server->server_struct.addr.sin_family = AF_INET;
    server->server_struct.addr.sin_port = htons(PORT);
    server->server_struct.addr.sin_addr.s_addr = INADDR_ANY;

    printf("Port : %d\n", PORT);flush;

    if (bind(server->server_struct.socket, (struct sockaddr *)&server->server_struct.addr, sizeof(server->server_struct.addr)) == -1) {
        return 3;
    }

    if (listen(server->server_struct.socket, NB_CLIENTS) == -1) {
        return 4;
    }
    return 0;
}
