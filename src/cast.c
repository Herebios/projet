#include "cast.h"

cast *newCast(perso_t *p, compt_t *comp){
	cast *c = (cast) malloc(sizeof (cast));
	c->type = comp->type;
	switch (c->type){
	case zone:
		c->v = NULL;
		c->casterIndex = persoIndex;
		c->pos->x = p->posX;
		c->pos->y = p->posY;
		c->velocity = -1;

	c->victimIndex = -1;
	c->damage = comp->fonction(p, comp);
	c->next = NULL;
