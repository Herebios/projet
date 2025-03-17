#include "../include/vector/vector.h"
#include "../src/perso.h" // maybe useless

typedef enum {zone, projectile, instant} castType; // in perso.h
typedef enum {onTouch, onEnd} state;

typedef struct cast_s cast;
typedef struct cast_s{
	tile* tile;
	castType type;
	vector *v;
	 caster;
	unsigned int velocity; // zone : ticks; instant : speedofthecast; projectil : speed
	unsigned int size;
	long damage;
	point pos;
};



cast *newCast(perso_t *p, comp_t *c);
void castUpdate(liste *castListe);
