#include <stdlib.h>
#include <string.h>
#include "liste.h"

element * temp=NULL;

liste * creer_liste() {
	liste *l=malloc(sizeof(liste));
	l->ec = l->drapeau->suiv = l->drapeau->prec = l->drapeau = (element*)malloc(sizeof(element));
}

int liste_vide(liste *l) {
	return l->drapeau->suiv == l->drapeau;
}

int hors_liste(liste *l) {
	return l->ec == l->drapeau;
}

void tete_liste(liste *l) {
	l->ec = l->drapeau->suiv;
}

void queue_liste(liste *l) {
	l->ec = l->drapeau->prec;
}

void suivant_liste(liste *l) {
	l->ec = l->ec->suiv;
}

void precedent_liste(liste *l) {
	l->ec = l->ec->prec;
}

void * get_liste(liste *l) {
	return l->ec->ptr;
}

void set_liste(liste *l, void * data, int size) {
	memcpy(l->ec->ptr, data, size);
}
/*supprimer place sur l'élément précédent
permet d'enlever des éléments dans une boucle en faisant toujours suivant()
*/
void supprimer_liste(liste *l) {
	l->ec->prec->suiv = l->ec->suiv;
	l->ec->suiv->prec = l->ec->prec;
	temp = l->ec;
	precedent_liste(l);
	free(temp->ptr);
	free(temp);
	temp=NULL;
}

void vider_liste(liste *l){
    if(!l)return;
    for(tete_liste(l);!hors_liste(l);suivant_liste(l))
        supprimer_liste(l);
}

void detruire_liste(liste **l){
	if(*l){
		for(tete_liste(*l);!hors_liste(*l);suivant_liste(*l))
			supprimer_liste(*l);
		free((*l)->drapeau);
		free(*l);
		*l=NULL;
	}
}

void ajout_droit_liste(liste *l, void * data, int size) {
	temp = malloc(sizeof(element));
	temp->ptr = malloc(size);
	memcpy(temp->ptr, data, size);

	temp->prec = l->ec;
	temp->suiv = l->ec->suiv;
	l->ec->suiv->prec = temp;
	l->ec->suiv = temp;

	l->ec = temp;
	temp=NULL;
}
void ajout_gauche_liste(liste *l, void * data, int size) {
	temp = malloc(sizeof(element));
	temp->ptr = malloc(size);
	memcpy(temp->ptr, data, size);

	temp->suiv = l->ec;
	temp->prec = l->ec->prec;
	l->ec->prec->suiv = temp;
	l->ec->prec = temp;

	l->ec = temp;
	temp=NULL;
}

void ajout_debut_liste(liste *l, void * data, int size){
	tete_liste(l);
	ajout_gauche_liste(l, data, size);
}
void ajout_fin_liste(liste *l, void * data, int size){
	queue_liste(l);
	ajout_droit_liste(l, data, size);
}

int taille_liste(liste *l){
	int t=0;
	for(tete_liste(l);!hors_liste(l);suivant_liste(l)) t++;
	return t;
}

void parcour_liste(liste * l, void* objet, int (*comparer)(void*, void*)){
	tete_liste(l);
	while (!hors_liste(l) && comparer(objet, get_liste(l)) != 0){
		suivant_liste(l);
	}
}

void * trouver_liste(liste *l, void* objet, int (*comparer)(void*, void*)){
	parcour_liste(l, objet, comparer);
	return (!hors_liste(l)) ? get_liste(l) : NULL;
}

void * trouver_supprimer_liste(liste *l, void* objet, int (*comparer)(void*, void*)){
	parcour_liste(l, objet, comparer);
	void * ret = get_liste(l);
	supprimer_liste(l);
	return ret;
}



