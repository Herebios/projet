/**
 * @file serv_jeu.c
 * @author Baptiste
 * @brief fonctions de contrôle du jeu
 */
#include "serv_jeu.h"

//map
map_t * map;

void serv_init_map(){
	tuile_t * t;
	int h,w,i;
	for(h=0; h<HAUTEUR_MAP; h++)
		for(w=0; w<LARGEUR_MAP; w++){
			t=map->tuiles[h]+w;
			for(i=0; i<NB_OBJETS_TUILE; i++)
				t->objets[i].objet=NULL;
			for(i=0; i<NB_PNJ_TUILE; i++)
				t->pnj[i]=NULL;
			for(i=0; i<NB_ENNEMIS_TUILE; i++)
				t->ennemis[i]=NULL;
		}
}

//objets
//??Quoi renvoyer pour le main et l'envoi aux clients
void spawn_objet(rarete_t r) {
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
	objet_t * nouv=tab_objets + ind;
	int xmap, ymap, xtuile, ytuile, i;
	char valide=0;
	tuile_t * tuile;
	while(!valide){
		//recherche d'une tuile qui a une place d'objet libre
		xmap=rand()%LARGEUR_MAP;
		ymap=rand()%HAUTEUR_MAP;
		tuile = map->tuiles[ymap] + xmap;
		for(i=0; i<NB_OBJETS_TUILE; i++){
			if(!tuile->objets[i].objet)//NULL : libre
				while(!valide){
					//recherche d'une case pour l'objet
					xtuile=rand()%LARGEUR_TUILE;
					ytuile=rand()%HAUTEUR_TUILE;
					if(tuile->id_texture[ytuile][xtuile]==normal){
						//on copie le pointeur sur objet et la pos
						tuile->objets[i] = (objet_tuile_t){nouv, (pos_t){xtuile, ytuile}};
						valide=1;//fin while
						i=NB_OBJETS_TUILE;//fin for
					}
				}
		}
	}
}

//joueurs
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
