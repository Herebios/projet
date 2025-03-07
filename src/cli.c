#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

#include "../datastruct/file.h"
#include "perso_cli.h"

file * file_socket;

#define PORT 2051
#define BUFFER_SIZE 101
#define flush fflush(stdout)
#define endl putchar('\n')

typedef struct {
    int socket;
    struct sockaddr_in addr;
    pthread_t thread;
    bool online;
} socket_struct;

void * ecoute_thread(void *);
int setup_client(socket_struct *, char *);
void fermeture_client(int, socket_struct *);

void init_joueurs(perso_cli joueurs[]){
	char * data;
	int i;
	//finit par chaine vide
	while((data=defiler(file_socket)) && *data){
		usleep(50000);
		//classe pseudo indice equipe
		sscanf(data, "%d %s %d %d", (int*)&joueurs[i].perso.classe, joueurs[i].perso.nom, (int*)&joueurs[i].perso.iperso, (int*)&joueurs[i].perso.equipe);
	}
}

int main_client(int nb_joueurs, char * ip) {
	//setup socket
	printf("'%s'\n", ip);flush;
	socket_struct client;
	int error_code;
	if((error_code=setup_client(&client, ip)) > 0){
		fermeture_client(error_code, &client);
		return error_code;
	}
	puts("setup client OK\n");flush;

	file_socket = newFile();

	int ecr_size;
	char ecr[BUFFER_SIZE];

	pthread_create(&client.thread, NULL, ecoute_thread, (void*)&client);

	//attente de lancement
	char * data;
	char end=0;
	while(!end){
		data=defiler(file_socket);
		if(data){
			printf("Message : ");
			if(strcmp(data, "start")==0)
				end=1;
			printf("%s !!", data);flush;
			free(data);
			data=NULL;
		}
		putchar('\n');
		usleep(1000000);
	}
	if(data){
		puts(data);
		free(data);
	}

//	perso_cli joueurs[nb_joueurs];
//	init_joueurs(joueurs);
	puts("boucle");flush;
	bool valide=1;
	while(valide && client.online){//si le thread est fermé prématurément
		fgets(ecr,BUFFER_SIZE,stdin);
		ecr_size=strlen(ecr);
		if (ecr_size>1){
			if (ecr[ecr_size-1] == '\n')
				ecr[--ecr_size]='\0';
	    	send(client.socket, ecr, ecr_size, 0);
		}else{
			valide=0;
			send(client.socket, "!", 1, 0);
		}
		while(!fileVide(file_socket)){
			data=defiler(file_socket);
			printf("'%s'\n", (char*)data);flush;
			free(data);
		}
		sleep(1);
	}
	while(client.online) sleep(1);//attend l'arrêt du thread d'écoute

	fermeture_client(0, &client);
    return error_code;
}

int main(){
	return main_client(1, "172.18.41.164");
}

void* ecoute_thread(void* arg){
/*
S'arrête quand le serveur envoie '!'
Signal par pointeur qui arrête le main
*/
	socket_struct* client=(socket_struct*)arg;
	int buffer_size;
    char buffer[BUFFER_SIZE];
    bool valide=1;
	while(valide){
		buffer_size = recv(client->socket, buffer, BUFFER_SIZE-1, 0);
		printf("Message reçu\n");
		if(buffer_size > 0){
            buffer[buffer_size] = '\0';
            switch(*buffer){
                case '!':
					valide=0;
					break;
                default:
					//copie du message dans la file
					printf("On enfile : %s\n", buffer);
					enfiler(file_socket, buffer, buffer_size+1);
            }
        }else
			valide=0;
	}
	puts("fin ecoute thread\n");flush;
	client->online=0;
	return NULL;
}
void fermeture_client(int error_code, socket_struct * client){
/*
Libération correspondant au code renvoyé par le setup en cas d'échec,
tout à la fin du programme, avec le code 0.
*/
	printf("fermeture\n");
	fileFree(&file_socket, free);
	switch(error_code){
case 0:
case 3:
	#ifdef _WIN32
    closesocket
    #else
    close
    #endif
    (client->socket);
case 2:
    #ifdef _WIN32
    WSACleanup();
    #endif
case 1:
	break;
	}
}

int setup_client(socket_struct * client, char * ip){
	int error_code;
	#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa))
		return 1;
	#endif

/* Si input de la forme ip:port
	char ip[16];
	char port[6];
	char *p=strchr(argv[1], ':');
	*p++='\0';
	strcpy(ip,argv[1]);
	strcpy(port,p);
*/
	if ((client->socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return 2;

	client->addr.sin_family = AF_INET;
	client->addr.sin_port = htons(PORT);//atoi(port)
	client->addr.sin_addr.s_addr = inet_addr(ip);

	if(connect(client->socket, (struct sockaddr *)&client->addr, sizeof(client->addr)) == -1)
		return 3;

	return 0;
}
