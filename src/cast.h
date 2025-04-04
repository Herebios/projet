#ifndef __CAST__
#define __CAST__

/**
 * @file cast.h
 * @author Lucas
 * @brief Structure et fonction pour la généricité de la liste des différents type d'envoie de compétences.
 */

#include <time.h>

#include "def.h"
#include "types.h"
#include "perso.h"
#include "math.h"

typedef struct {
	unsigned short int id;
	struct timespec lastUpdate;
} cast_t;

/**
 * @fn int comparer(unsigned short int *e1, cast_t *e2)
 * @brief Compare l'id d'un cast avec celui d'un autre cast
 */
int comparer(unsigned short int *e1, cast_t *e2);
int comparer_cb(void *e1, void *e2);

void* getCast (tuile_t *tuile, unsigned short int id);
void* removeCast (tuile_t *tuile, unsigned short int id);

#endif

