#include "types.h"

/* Tank */
int tank_attaque_force(perso_t *p, comp_t *c){
	//Multiplication de stat force par valeur
	return p->stats[force] * c->valeur;
}
