

#include "menu.h"
#include "serv.c"
#include "cli.c"

#define DEFAULT_PORT

int main(int argc, char *argv[]){
    int port = (argc == 2) ? atoi(argv[1]) : 2080;
    char classe;
    int nbClient = 2;
    int code = -2;
    while (code != -1){
        menu(&classe);
        if (code){
            main_server(port, nbClient);
        }else{
            main_client(saisieIp, port, nomJoueur, classe);
        }
    }
    return 0;
}