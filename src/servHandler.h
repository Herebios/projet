#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

#include "perso.h"
#define PORT 2051
#define BUFFER_SIZE 101
#define NB_CLIENTS 3

#define flush fflush(stdout)
#define endl putchar('\n')

typedef struct {
    int socket;
    pthread_t thread;
    bool online;
	struct sockaddr_in addr;
} socket_struct;

typedef struct {
	socket_struct socket;
} server_socket_struct;


typedef struct {
    socket_struct server_struct;
    bool premier_client, clients_on[NB_CLIENTS];
    int nb_clients, nb_on;
} info_server;

void * client_thread(void *);
void * accept_thread(void *);
int setup_server(info_server *);
void fermeture_server(int, info_server *, socket_struct *);
void broadcast(char *string, info_server *s, socket_struct clients[NB_CLIENTS]);







