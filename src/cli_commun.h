#ifndef _CLI_H_
#define _CLI_H_

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

#include "def.h"
#include "file.h"
#include "prepro.h"

#define PORT 2050
#define BUFFERLEN 101

typedef struct {
    int socket;
    struct sockaddr_in addr;
    pthread_t thread;
    char online;
} socket_struct;

extern file * file_socket;
extern socket_struct client;
extern int indice, nb_joueurs;

void * ecoute_thread(void * null);
int setup_client(char * ip);
void fermeture_client(int code);

void sendf(char *, ...);
char * data_skip(char *, int);

int main_client(char * ip, char * nom, classe_t);

#endif
