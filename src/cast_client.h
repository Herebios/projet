#ifndef __CAST_CLIENT__
#define __CAST_CLIENT__

#include "def.h"
#include "types.h"
#include "../src/perso.h" // maybe useless

typedef enum {onTouch, onEnd} state;

typedef struct cast_zone_s cast_zone_t;
typedef struct cast_zone_s{
	unsigned short int id;
	comp_t* comp;
	pos_t pos;
};

cast_zone_t * newCastZone(tuile_t *tuile, comp_t *comp, unsigned short int id, pos_t pos);
void updatePosCastZone(tuile_t *tuile, cast_zone_t *cast, pos_t pos);
void removeCastZone(tuile_t *tuile, cast_zone_t *cast);
#endif