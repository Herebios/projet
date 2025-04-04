#include "cli_jeu.h"

SDL_Texture * texture_tuile;

/*nb_joueurs en global*/
void init_joueurs_client(perso_t *joueurs){
    char *data;
    int ind=0;//on sait qu'on lit dans l'ordre, serv n'envoie pas l'ind
    int equipe;
    classe_t classe;
    char nom[32];
	int nb=nb_joueurs;
    while(nb){
        if(!fileVide(file_socket)){
            data=defiler(file_socket);
            sscanf(data, "%s %d %d", nom, (int*)&classe, &equipe);
            creer_perso(joueurs + ind, classe, nom, ind, equipe);
            free(data);
            nb--;
			ind++;
        }
		else usleep(100000);
    }
}

void charger_sdl_objets(SDL_Texture * textures_objets[NB_OBJETS]){
	for(int i=0; i<NB_OBJETS; i++){
        printf("chaine : %s\n", tab_objets[i].nom);
		char * objnom = malloc(strlen(tab_objets[i].nom) + strlen("../img/Objets/") + strlen(".jpg") + 1);//ajouter .jpg et "../img/Objets/"
		strcpy(objnom, "../img/Objets/");
        strcat(objnom, tab_objets[i].nom);
		strcat(objnom, ".jpg");
		textures_objets[i] = get_nouv_texture(objnom);
	}
}

void charger_sdl_joueurs(perso_t joueurs[], SDL_Texture * textures_joueurs[][4]){
	memset(textures_joueurs, 0, 32 * nb_joueurs);
	char * fichier[]={"Face.png", "Dos.png", "Gauche.png", "Droite.png"};
	char path[128]="../img/Characters/";
	int len1=strlen(path);
	for (int i=0; i<nb_joueurs; i++){
		switch(joueurs[i].classe){
			case archer:
				strcat(path, "archer/");
				break;
			case mage:
				strcat(path, "mage/");
				break;
			case ninja:
				strcat(path, "ninja/");
				break;
			default:
			case vampire:
				strcat(path, "vampire/");
				break;
		}

		int len2=strlen(path);
		unsigned char nb_textures=0;
		for(int j=0; j<4; j++){
			strcat(path, fichier[j]);
			nouv_texture(path, textures_joueurs[i], &nb_textures);
			path[len2]=0;
		}
		path[len1]=0;
	}
}

void detruire_objets_client(SDL_Texture * textures_objets[NB_OBJETS]){
	for(int i=0; i<NB_OBJETS; i++)
		if(textures_objets[i])
			SDL_DestroyTexture(textures_objets[i]);
}

void detruire_joueurs_client(perso_t *joueurs, SDL_Texture * textures_joueurs[][4]){
    for(int i=0; i<nb_joueurs; i++){
        detruire_perso(joueurs + i);
		for(int j=0; j<4; j++)
			if(textures_joueurs[i][j])
				SDL_DestroyTexture(textures_joueurs[i][j]);
	}
}

//obligatoirement le joueur ; connaître id objet
void ramasser_objet(perso_t *perso, int ind_o){
    sendf("%d %d", ADD_OBJET_JOUEUR, ind_o);
    ajouter_objet_joueur(perso, ind_o);
    update_stats(perso);
}
//position dans l'inventaire
void lacher_objet(perso_t *perso, int ind_inv){
    if (perso->objets[ind_inv] == NULL)
        return;
        
    sendf("%d %d", RM_OBJET_JOUEUR, ind_inv);
    retirer_objet_joueur(perso, ind_inv);
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

void attaqueBasique(perso_t *p, dir_t dir){
    sendf("dd", BASIC_ATTACK, dir);
}