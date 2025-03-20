/**
 * @file serv_jeu.c
 * @author Baptiste
 * @brief fonctions de contrôle du jeu
 */
#include "serv_jeu.h"

//objets
//fonction intermédiaire, renvoie position exacte et indice de l'objet choisi aléatoirement
static void spawn_objetbis(rarete_t r, int *pxmap, int *pymap, int *pxtuile, int *pytuile, int *ind_obj) {
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
	objet_t * nouv_obj=tab_objets + ind;
	int xmap, ymap, xtuile, ytuile;
	char valide=0;
	tuile_t *t;
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
				//on copie le pointeur sur objet et la pos
				objet_tuile_t temp = {nouv, (pos_t){xtuile, ytuile}};
				ajout_fin_liste(tuile->liste_objets, &temp, sizeof(objet_tuile_t));
				*pxmap = xmap; 	*pymap = ymap; 	*pxtuile = xtuile; *pytuile = ytuile;
				*ind_obj = ind;
				valide=1;//fin while
			}
		}
	}
}

void spawn_objet(rarete_t r){
	int xm, ym, xt, yt, ind_obj;
	spawn_objetbis(r, &xm, &ym, &xy, &yt, &ind_obj);

	char buffer[BUFFERLEN];
	sprintf(buffer, "%d %d %d %d %d %d", SPAWN_OBJET, ind_obj, xm, ym, xt, yt);

	//envoi aux joueurs déjà sur la tuile
	tuile_t *t=map[ym] + xm;
	perso_t *p;
	for(tete_liste(t->liste_joueurs); !hors_liste(t->liste_joueurs); suivant_liste(t->liste_joueurs)){
		p=get_liste(t->liste_joueurs);
		send(clients[p->iperso].socket, buffer, strlen(buffer), 0);
	}
}

//joueurs
/*Envoie au joueur les infos de la tuile*/
void maj_tuile(perso_t * joueurs, int ind, pos_t pos_map){
	char buffer[BUFFERLEN]="";
	tuile_t *t=map[pos_map.y]+pos_map.x;
	sprintf(buffer, "%d %d %d ", NOUV_TUILE, pos_map.x, pos_map.y);

	//envoi objets
	objet_tuile_t * obj;
	for(tete_liste(t->liste_objets); !hors_liste(t->liste_objets); suivant_liste(t->liste_objets)){
		obj = get_liste(t->liste_objets);
		if(obj->objet)
			sprintf(buffer+strlen(buffer), "%d %d %d ", obj->objet.ind, obj->pos.x, obj->pos.y);
	}
}

/*Reçoit les infos de chaque client*/
void init_joueurs_server(perso_t * joueurs){
    char * data;
    int equipe=1;//alterne à chaque boucle
    classe_t classe;
    char nom[32];
    int ind, nb=NB_CLIENTS;
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
void detruire_joueurs_server(perso_t * joueurs){
    for(int i=0; i<NB_CLIENTS; i++){
        detruire_perso(joueurs+i);
    }
}
/*Envoie à tous les clients les autres infos*/
void send_joueurs_server(info_server * serv, socket_struct clients[NB_CLIENTS], perso_t joueurs[NB_CLIENTS]){
    char data[128];
    for(int i=0; i<NB_CLIENTS; i++){
        sprintf(data, "%d %s %d", joueurs[i].classe, joueurs[i].nom, joueurs[i].equipe);
        broadcast(data, serv, clients, -1);//exception i, envoi inutile de ses infos
    }
}
