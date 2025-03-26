#include "cli_jeu.h"

SDL_Texture * texture_tuile;

/*nb_joueurs en global*/
void init_joueurs_client(perso_cli_t *joueurs){
    char *data;
    int ind=0;//on sait qu'on lit dans l'ordre, serv n'envoie pas l'ind
    int equipe;
    classe_t classe;
    char nom[32];
	int nb=nb_joueurs;
    while(nb){
        if(fileVide(file_socket))
            usleep(100000);
        else{
            data=defiler(file_socket);
            sscanf(data, "%s %d %d", nom, (int*)&classe, &equipe);
            creer_perso(&joueurs[ind].perso, classe, nom, ind, equipe);
            free(data);
            nb--;
			ind++;
        }
    }
	puts("OK");flush;
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
        ajout_fin_liste(tuile->liste_objets, &(objet_tuile_t){tab_objets + ind, (pos_t){x, y}}, sizeof(objet_tuile_t));
    }
    //??charger_tuile(tuile);afficher_tuile(tuile);
}

//direction du joueur en fonction du clavier
void changer_dir(perso_t *p, char mask){
    switch(mask){
        //basdroite
        case 10:
            p->dir=basdroite;
            break;
        //hautdroite
        case 9:
            p->dir=hautdroite;
            break;
        //basgauche
        case 6:
            p->dir=basgauche;
            break;
        //hautgauche
        case 5:
            p->dir=hautgauche;
            break;
        //droite
        case 11:
        case 8:
            p->dir=droite;
            break;
        //gauche
        case 7:
        case 4:
            p->dir=gauche;
            break;
        //bas
        case 14:
        case 2:
            p->dir=bas;
            break;
        //haut
        case 13:
        case 1:
            p->dir=haut;
    }
}

void afficher_tuile(){
	SDL_RenderCopy(renderer, texture_tuile, 0, 0);
	return;
}

void charger_tuile(tuile_t * tuile){
    SDL_SetRenderTarget(renderer, texture_tuile);
    for (int l=0,c; l<HAUTEUR_TUILE; l++)
        for (c=0; c<LARGEUR_TUILE; c++)
            SDL_RenderCopy(renderer, tuile->biome->textures[tuile->id_texture[l][c]], 0, &(SDL_Rect){c*CARRE_W,l*CARRE_H,CARRE_W,CARRE_H});
    SDL_SetRenderTarget(renderer, NULL);
}
