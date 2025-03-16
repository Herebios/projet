/**
 * @file serv_socket.h
 * @author Baptiste
 */
#ifndef _SERV_SOCKET_H_
#define _SERV_SOCKET_H_

#include "serv_commun.h"

#define PORT 2048

void * client_thread(void *);
void * accept_thread(void *);
int setup_server(info_server *);
void fermeture_server(info_server *, socket_struct *, int code);

#endif
