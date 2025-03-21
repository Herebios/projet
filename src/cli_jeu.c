#include "cli_jeu.h"

/*nb_joueurs en global*/
void init_joueurs_client(perso_cli_t *joueurs){
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

void detruire_joueurs_client(perso_cli_t *joueurs){
    for(int i=0; i<nb_joueurs; i++)
        detruire_perso(&joueurs[i].perso);
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

/**
@brief Reception du message JOUEUR_MV_TUILE
@param pointeur sur le joueur
@param buffer d'informations du serv
*/
//!!à compléter, voir maj_tuile du serv
void changer_tuile(perso_t *p, char * buffer){
    //position de la tuile
    int x, y, nb_obj;
    sscanf(data_skip(buffer, 1), "%d %d %d", &x, &y, &nb_obj);
    tuile_t *tuile=map[y]+x;
    p->pos_map.x=x; p->pos_map.y=y;

    int ind;
    //on va lire nb_obj * (ind, x, y) et ajouter les objets à la liste de la tuile
    for(int i=0; i<nb_obj; i++){
        sscanf(data_skip(buffer, 4 + 3*i), "%d %d %d", &ind, &x, &y);
        ajout_fin_liste(t->liste_objets, &(objet_tuile_t){tab_objets + ind, (pos_t){x, y}}, sizeof(objet_tuile_t));
    }
    //??charger_tuile(tuile);afficher_tuile(tuile);
}
