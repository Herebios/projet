#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perso.h"

void creer_perso(perso_t * p, classe_t classe, char * nom, int indice, int equipe){
	if(nom && *nom)
		p->nom=strdup(nom);
	else
		p->nom=strdup("Gauss");
	p->classe=classe;
	p->niveau=1;
	p->x=p->y=0;
	p->iperso=indice;
	p->equipe=equipe;

	int i;
	for (i=0; i<NB_COMP; i++)
		p->competences[i]=NULL;
	for (i=0; i<PERSO_OBJETS_MAX; i++)
		p->objets[i]=NULL;

	//stats de base en fonction de la classe
	switch(classe){
		case tank:
            memcpy(p->stats_base, (int[4]){120,60,5,8}, sizeof(int[4]));
			break;
		case guerrier:
            memcpy(p->stats_base, (int[4]){100,50,10,16}, sizeof(int[4]));
			break;
		case mage:
			memcpy(p->stats_base, (int[4]){50,10,50,12}, sizeof(int[4]));
			break;
		case archer:
			memcpy(p->stats_base, (int[4]){60,40,15,18}, sizeof(int[4]));
			break;
		case informaticien:
			memcpy(p->stats_base, (int[4]){70,15,20,12}, sizeof(int[4]));
			break;
		case ninja:
			memcpy(p->stats_base, (int[4]){65,30,10,20}, sizeof(int[4]));
			break;
		case druide:
			memcpy(p->stats_base, (int[4]){85,25,40,14}, sizeof(int[4]));
			break;
	}
	update_stats(p);
}

/*
A compléter en fonction de l'implémentation de objets/compétences, etc.
*/
void detruire_perso(perso_t * p){
	free(p->nom);
	p->nom=NULL;
}

void afficher_objets_perso(perso_t * perso) {
    for (int i = 0; i < PERSO_OBJETS_MAX; i++) {
        if(perso->objets[i]){
            printf("Objet %d : ", i + 1);
			afficher_objet(perso->objets[i]);
		}
    }
}

void afficher_stats_perso(perso_t * perso) {
    printf("Stats de base :\n");
    printf("\tVie     : %d\n", perso->stats_base[vie]);
    printf("\tForce   : %d\n", perso->stats_base[force]);
    printf("\tMagie   : %d\n", perso->stats_base[magie]);
    printf("\tSpeed   : %d\n", perso->stats_base[speed]);
    printf("Stats avec objets :\n");
    printf("\tVie     : %d\n", perso->stats[vie]);
    printf("\tForce   : %d\n", perso->stats[force]);
    printf("\tMagie   : %d\n", perso->stats[magie]);
    printf("\tSpeed   : %d\n", perso->stats[speed]);
}

/*
Appel à cette fonction après chaque ajout/retrait
pour que l'ordre de calcul soit respecté
*/
void update_stats(perso_t * p) {
	//remise à 0
	memcpy(p->stats, p->stats_base, sizeof(int[4]));
	//calcul
    for(int i=0,stat; i<PERSO_OBJETS_MAX; i++){
    if(p->objets[i])
        for(stat=0; stat<4; stat++){
            switch(p->objets[i]->stats[stat].priority){
                case add:
                    //ajoute la valeur de l'objet
                    p->stats[stat] += p->objets[i]->stats[stat].valeur;
                    break;
                case mult:
                    //ajoute une multiplication de la stat de base
                    p->stats[stat] += (p->objets[i]->stats[stat].valeur - 1) * p->stats_base[stat];
                    break;
                case null:
                    //pas de valeur
                    break;
            }

        }
    }
}

void ajouter_objet(perso_t * perso, int ind_obj) {
    int i=0;
    //trouver la première place libre
    while(perso->objets[i] && i<PERSO_OBJETS_MAX) i++;
    if(i==PERSO_OBJETS_MAX)return;//pas de place
    perso->objets[i] = tab_objets+ind_obj;
}
void retirer_objet(perso_t * perso, int ind_inv) {
    perso->objets[ind_inv] = NULL;
}
/*
int main(void){
    int nb_joueurs = 1;//info du server
    perso_t tab_perso[nb_joueurs];
	perso_t *p=tab_perso;
	creer_perso(p, mage, "Maggie", 0);

	ajouter_objet(p, tab_objets+0);
	ajouter_objet(p, tab_objets+1);
	ajouter_objet(p, tab_objets+2);
	update_stats(p);
	retirer_objet(p, 1);
	ajouter_objet(p, tab_objets+2);
	update_stats(p);

	afficher_objets_perso(p);
	afficher_stats_perso(p);

	detruire_perso(tab_perso);
    return 0;
}
*/
