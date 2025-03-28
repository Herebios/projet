#ifndef __CAST__
#define __CAST__

#include "def.h"
#include "types.h"
#include "perso.h"

// only server side static unsigned short int last_id = 0;

typedef struct {
	unsigned short int id;
} cast_t;

int comparer(unsigned short int *e1, cast_t *e2);
int comparer_cb(void *e1, void *e2);

void* getCast (tuile_t *tuile, unsigned short int id);
void* removeCast (tuile_t *tuile, unsigned short int id);

#endif

