/**
 * @file serv_jeu.c
 * @author Baptiste
 * @brief fonctions de contrôle du jeu
 */
#include "serv_jeu.h"

//objets
//fonction intermédiaire, renvoie position exacte et indice de l'objet choisi aléatoirement
static void spawn_objetbis(rarete_t r, int *ind_o, pos_t *p_map, pos_t *p_tuile) {
	int ind;
	switch(r){
		case commun:
			ind=rand()%NB_OBJETS_C;
			break;
		case rare:
			ind=rand()%NB_OBJETS_R + NB_OBJETS_C;
			break;
		case epique:
			ind=rand()%NB_OBJETS_E + NB_OBJETS_R + NB_OBJETS_C;
			break;
		case legendaire:
			ind=rand()%NB_OBJETS_L + NB_OBJETS-NB_OBJETS_L;
	}
	int xmap, ymap, xtuile, ytuile;
	*ind_o = ind;
	char valide=0;
	tuile_t *tuile;
	while(!valide){
		//recherche d'une tuile qui a une place d'objet libre
		xmap=rand()%LARGEUR_MAP;
		ymap=rand()%HAUTEUR_MAP;
		tuile = map[ymap] + xmap;
		while(!valide){
			//recherche d'une case pour l'objet
			xtuile=rand()%LARGEUR_TUILE;
			ytuile=rand()%HAUTEUR_TUILE;
			if(tuile->id_texture[ytuile][xtuile]==normal){
				//on renvoie les valeurs
				p_map->x = xmap; p_map->y = ymap; p_tuile->x = xtuile; p_tuile->y = ytuile;
				valide=1;//fin while
			}
		}
	}
}
/*Cette fonction est appelée quand un objet est ajouté sur la map.
Soit un nouveau apparaît (mode 0), paramètres générés par fonction bis,
soit un joueur laisse tomber un objet, paramètres connus.
*/
void spawn_objet(rarete_t r, int mode, int ind_o, pos_t p_map, pos_t p_tuile){
	if(mode==0)
		spawn_objetbis(r, &ind_o, &p_map, &p_tuile);

	tuile_t *t=get_tuile_from_pos(p_map);
	ajouter_objet_tuile(t, ind_o, p_tuile);

	//envoi aux joueurs déjà sur la tuile
	if(taille_liste(t->liste_joueurs) < 1) return;

	char buffer[BUFFERLEN];
	sprintf(buffer, "%d %d %d %d", SPAWN_OBJET, ind_o, p_tuile.x, p_tuile.y);

	perso_t *p;
	for(tete_liste(t->liste_joueurs); !hors_liste(t->liste_joueurs); suivant_liste(t->liste_joueurs)){
		p=get_liste(t->liste_joueurs);
		send(clients[p->iperso].socket, buffer, strlen(buffer), 0);
	}
}

/*Envoie au joueur les infos de la tuile*/
//!!compléter avec les autres infos
void maj_tuile(int ind, pos_t pos_map){
	char buffer[BUFFERLEN]="";
	tuile_t *t=map[pos_map.y]+pos_map.x;
	sprintf(buffer, "%d %d %d %d", JOUEUR_MV_TUILE, pos_map.x, pos_map.y, taille_liste(t->liste_objets));

	//envoi objets
	objet_tuile_t * obj;
	for(tete_liste(t->liste_objets); !hors_liste(t->liste_objets); suivant_liste(t->liste_objets)){
		obj = get_liste(t->liste_objets);
		if(obj->objet)
			sprintf(buffer+strlen(buffer), "%d %d %d ", obj->objet->ind, obj->pos.x, obj->pos.y);
	}
	send(clients[ind].socket, buffer, strlen(buffer), 0);
}

/*Reçoit les infos de chaque client*/
void init_joueurs_server(perso_t * joueurs, int nb){
    char * data;
    int equipe=1;//alterne à chaque boucle
    classe_t classe;
    char nom[32];
    int ind;
    /*On ne sait pas dans quel ordre on va lire, on utilise l'indice
    que le client envoie.*/
    while(nb){//nb de messages attendus
        if(fileVide(serv_file))
            sleep(1);
        else{
            data=defiler(serv_file);
            sscanf(data, "%d %d %s", &ind, (int*)&classe, nom);
            creer_perso(joueurs + ind, classe, nom, ind, equipe=!equipe);
            free(data);
            nb--;
        }
    }
}
void detruire_joueurs_server(perso_t * joueurs, int nb){
    for(int i=0; i<nb; i++){
        detruire_perso(joueurs+i);
    }
}
/*Envoie à tous les clients les autres infos*/
void send_joueurs_server(perso_t * joueurs, int nb){
    char data[128];
    for(int i=0; i<nb; i++){
        sprintf(data, "%s %d %d ", joueurs[i].nom, joueurs[i].classe, joueurs[i].equipe);
        broadcast(data, -1);
    }
}

/*Renvoie 1 si le perso p change de tuile
    Dans ce cas, le server envoie maj_tuile au client
Sinon renvoie 0
*/
int check_sortie_tuile(perso_t *p){
    tuile_t *t=map[p->pos_map.y] + p->pos_map.x;
    pos_t pos_tuile;
    position_perso(p, &pos_tuile);
    if(t->id_texture[pos_tuile.y][pos_tuile.x]==sortie){
        if(pos_tuile.x==0){
        //sortie gauche tuile
            p->pos_map.x--;
            p->rect.x = W - p->rect.w;//se retrouve côté droit
        }else if(pos_tuile.x==LARGEUR_TUILE-1){
            p->pos_map.x++;
            p->rect.x = 0;//se retrouve côté gauche
        }else if(pos_tuile.y==0){
        //sortie haut tuile
            p->pos_map.y--;
            p->rect.y = H - p->rect.h;//se retrouve en bas
        }else/* if (pos_tuile.y==HAUTEUR_TUILE-1)*/{
            p->pos_map.y++;
            p->rect.y = 0;//se retrouve en haut
        }
        return 1;
    }
    return 0;
}
