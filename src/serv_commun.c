/**
 * @file serv_commun.c
 * @author Baptiste
 * @brief fonctions communes pour le serv
 */
#include "serv_commun.h"

file * serv_file;
socket_struct *clients;//malloc NB_CLIENTS
info_server server;

/*Utilisé pour lire après nb espaces
Voir switch main_serv*/
char * data_skip(char * data, int nb){
    char * skip=data + 1;
    while(nb){
        if(*skip++ == ' ')
            nb--;
    }
    return skip;
}

/*exception = indice du client à qui on ne veut pas envoyer
par défaut -1 ou NB_CLIENTS, pas des ind valides*/
void broadcast(char *data, int exception){
    for (int i=0, datalen=strlen(data); i < server.nb_clients; i++){
        //if (clients[i].online)
        if(i != exception)
            send(clients[i].socket, data, datalen, 0);
    }
}
