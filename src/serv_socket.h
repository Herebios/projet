/**
 * @file serv_socket.h
 * @author Baptiste
 */
#ifndef _SERV_SOCKET_H_
#define _SERV_SOCKET_H_

#include "serv_commun.h"

#define PORT 2050

void * client_thread(void *);
void * accept_thread(void *);
int setup_server(int port, int nb_clients);
void fermeture_server(int code);

#endif
