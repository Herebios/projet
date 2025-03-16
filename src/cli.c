#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

#include "../datastruct/file.h"
#include "perso_cli.h"
#include "id_actions.h"

file * file_socket;

#define PORT 2048
#define BUFFERLEN 101
#define flush fflush(stdout)
#define endl putchar('\n')

typedef struct {
    int socket;
    struct sockaddr_in addr;
    pthread_t thread;
    bool online;
} socket_struct;

//variables utilisées en global
socket_struct client;
int indice, nb_joueurs;

void * ecoute_thread(void * null);
int setup_client(char * ip);
void fermeture_client(int code);

/*nb_joueurs en global*/
void init_joueurs_client(perso_cli_t joueurs[]){
	char *data;
	int ind=0;//on sait qu'on lit dans l'ordre, serv n'envoie pas l'ind
	int equipe;
	classe_t classe;
    char nom[32];
	while(ind < nb_joueurs){
		if(fileVide(file_socket))
			usleep(100000);
		else{
			data=defiler(file_socket);
			sscanf(data, "%d %s %d", (int*)&classe, nom, &equipe);
			creer_perso(&joueurs[ind].perso, classe, nom, ind, equipe);
			free(data);
			ind++;
		}
	}
}

void detruire_joueurs_client(perso_cli_t * joueurs){
	for(int i=0; i<nb_joueurs; i++)
		detruire_perso(&joueurs[i].perso);
}

/* Utilise va_arg pour envoyer facilement ce qu'on veut
socket et ind en global*/
void sendf(char * format, ...){
	char buffer[BUFFERLEN], *pformat=format;
	sprintf(buffer, "%d ", indice);
	va_list va;
	va_start(va, format);
	while(*pformat)
		switch(*pformat++){
			case 'd':
				sprintf(buffer+strlen(buffer), "%d ", va_arg(va, int));
				break;
			case 's':
				sprintf(buffer+strlen(buffer), "%s ", va_arg(va, char*));
				break;
		}
	va_end(va);
	send(client.socket, buffer, strlen(buffer), 0);
}

//obligatoirement le joueur ; connaître id objet
void ramasser_objet(perso_t *perso, int ind_o){
	sendf("%d %d", ADD_OBJET, ind_o);
	ajouter_objet(perso, ind_o);
	update_stats(perso);
}
//position dans l'inventaire
void lacher_objet(perso_t *perso, int ind_inv){
	sendf("%d %d", RM_OBJET, ind_inv);
	retirer_objet(perso, ind_inv);
	update_stats(perso);
}

int main_client(char * ip, char * pseudo, classe_t classe) {
	//setup socket
	int error_code;
	if((error_code=setup_client(ip)) > 0){
		fermeture_client(error_code);
		return error_code;
	}
	puts("setup client OK\n");flush;

	file_socket = newFile();

	int buffer_size;
	char buffer[BUFFERLEN];

	pthread_create(&client.thread, NULL, ecoute_thread, NULL);

	//attente de lancement
	char * data;
	char end=0;
	while(!end){
		data=defiler(file_socket);
		if(data){
			puts(data);flush;
			if(strcmp(data, "start")==0)
				end=1;
			free(data);
			data=NULL;
		}
		putchar('\n');
		sleep(1);
	}
	if(data){
		puts(data);
		free(data);
	}

	//Récupère son indice
	while(fileVide(file_socket))
		sleep(1);
	data=defiler(file_socket);
	sscanf(data, "%d %d", &indice, &nb_joueurs);
	free(data);
	printf("Je suis le client %d/%d !\n", indice, nb_joueurs);

	//serv init le perso
	sendf("ds", classe, pseudo);

	perso_cli_t joueurs[nb_joueurs];
	init_joueurs_client(joueurs);

	puts("Les joueurs sont :");
	for(int i=0; i<nb_joueurs; i++){
        printf("ind %d ; classe %d ; nom %s ; equipe %d\n", i, joueurs[i].perso.classe, joueurs[i].perso.nom, joueurs[i].perso.equipe);
    }
//	bool valide=1;
//	while(valide && client.online){//si le thread est fermé prématurément
		ramasser_objet(&joueurs[indice].perso, 0);
		lacher_objet(&joueurs[indice].perso, 0);
		ramasser_objet(&joueurs[indice].perso, 0);
		send(client.socket, "!", 1, 0);

/*		while(!fileVide(file_socket)){
			data=defiler(file_socket);
			printf("'%s'\n", (char*)data);flush;
			free(data);
		}
		sleep(1);
*/
//	}
	while(client.online){
		puts("attente");
		sleep(1);//attend fin ecoute_thread
	}

    detruire_joueurs_client(joueurs);
	fermeture_client(0);
    return 0;
}

int main(int argc, char *argv[]){
	return main_client("127.0.0.1", "boi", 1);
}

void* ecoute_thread(void *arg){
/*
S'arrête quand le serveur envoie '!'
Signal par pointeur qui arrête le main
*/
	int buffer_size;
    char buffer[BUFFERLEN];
    bool valide=1;
	client.online=1;
	while(valide){
		buffer_size = recv(client.socket, buffer, BUFFERLEN, 0);
		if(buffer_size > 0){
            buffer[buffer_size] = '\0';
			printf("Recu : '%s'\n", buffer);flush;
            switch(*buffer){
                case '!':
					valide=0;
					break;
                default:
					//copie du message dans la file
					enfiler(file_socket, buffer, buffer_size+1);
            }
        }else{
			valide=0;
			puts("Le serveur est mort, je crois.");
		}
	}
	puts("fin ecoute thread\n");flush;
	client.online=0;
	return NULL;
}
void fermeture_client(int error_code){
/*
Libération correspondant au code renvoyé par le setup en cas d'échec,
tout à la fin du programme, avec le code 0.
*/
	printf("fermeture\n");
	if(file_socket)fileFree(&file_socket, free);
	switch(error_code){
case 0:
case 3:
	#ifdef _WIN32
    closesocket
    #else
    close
    #endif
    (client.socket);
case 2:
    #ifdef _WIN32
    WSACleanup();
    #endif
case 1:
	break;
	}
}

int setup_client(char * ip){
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
	if ((client.socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return 2;

	client.addr.sin_family = AF_INET;
	client.addr.sin_port = htons(PORT);//atoi(port)
	client.addr.sin_addr.s_addr = inet_addr(ip);

	if(connect(client.socket, (struct sockaddr *)&client.addr, sizeof(client.addr)) == -1)
		return 3;

	return 0;
}
