/**
 * @file serv_commun.h
 * @author Baptiste
 */
#ifndef _SERV_COMMUN_H_
#define _SERV_COMMUN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

#include "prepro.h"
#include "file.h"

#define BUFFERLEN 101

typedef struct {
    int socket;
    pthread_t thread;
    bool online;
    struct sockaddr_in addr;
} socket_struct;

typedef struct {
    socket_struct server_struct;
    int nb_clients, nb_on;
} info_server;

extern file * serv_file;
extern socket_struct * clients;
extern info_server server;

static char * data_skip(char *, int);
void broadcast(char *, int exception);

#endif
