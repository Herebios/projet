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

void en_tete(liste *l) {
	l->ec = l->drapeau->suiv;
}

void en_queue(liste *l) {
	l->ec = l->drapeau->prec;
}

void suivant(liste *l) {
	l->ec = l->ec->suiv;
}

void precedent(liste *l) {
	l->ec = l->ec->prec;
}

void * get(liste *l) {
	return l->ec->ptr;
}

void set(liste *l, void * data, size_t size) {
	memcpy(l->ec->ptr, data, size);
}
/*supprimer place sur l'élément précédent
permet d'enlever des éléments dans une boucle en faisant toujours suivant()
*/
void supprimer(liste *l) {
	l->ec->prec->suiv = l->ec->suiv;
	l->ec->suiv->prec = l->ec->prec;
	temp = l->ec;
	precedent(l);
	free(temp->ptr);
	free(temp);
	temp=NULL;
}

void detruire_liste(liste **l){
	if(*l){
		for(en_tete(*l);!hors_liste(*l);suivant(*l))
			supprimer(*l);
		free((*l)->drapeau);
		free(*l);
		*l=NULL;
	}
}

void ajout_droit(liste *l, void * data, size_t size) {
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
void ajout_gauche(liste *l, void * data, size_t size) {
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

void ajout_debut(liste *l, void * data, size_t size){
	en_tete(l);
	ajout_gauche(l, data, size);
}
void ajout_fin(liste *l, void * data, size_t size){
	en_queue(l);
	ajout_droit(l, data, size);
}

int taille_liste(liste *l){
	int t=0;
	for(en_tete(l);!hors_liste(l);suivant(l)) t++;
	return t;
}
