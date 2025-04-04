
#include "menu.h"
#include "cli.h"

int main(){
    int classe;
    init_sdl();
    char port[5];
    char nbClient;
    int code = -2;
    classe_t vraieClasse;
    
    while (code != -1){
        code = menu(&classe, port, &nbClient);
        switch(classe){
            case 0 : vraieClasse = mage; break;
            case 1 : vraieClasse = ninja; break;
            case 2 : vraieClasse = vampire; break;
            case 3 : vraieClasse = archer; break;

            default : printf("Classe %d inconnue.\n", classe); break;
        }
        int vraiPort = atoi(port);
        printf("Ip : %s | Port : %d | Nom Joueur : %s | Classe : %d|\n", saisieIp, vraiPort, nomJoueur, vraieClasse);



        //être serveur
        if(code == 1 || code == 2){
            char commande[15]; commande[0] = '\0';
            strcat(commande, " ./serv ");
            strcat(commande, port);
            strcat(commande, "&\0");
            system(commande);
            SDL_Delay(1000);
            if(code == 2) main_client("127.0.0.1", vraiPort, nomJoueur, vraieClasse);
        }
        
        else if (code == 0){
            main_client(saisieIp, vraiPort, nomJoueur, vraieClasse);
        }
    }
    return 0;
}