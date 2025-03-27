#ifndef __CAST__
#define __CAST__

#include "def.h"
#include "types.h"
#include "perso.h"

typedef struct {
	unsigned short int id;
} cast_t;

int comparer(cast_t *e1, cast_t *e2);
int comparer_cb(void *e1, void *e2);

void trouver_supprimer_cb(liste * l, unsigned short int id);

#endif
