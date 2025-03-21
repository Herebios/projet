#ifndef __CAST_SERVER__
#define __CAST_SERVER__

#include <time.h>
#include "def.h"
#include "types.h"
#include "../src/perso.h" // maybe useless

typedef enum {onTouch, onEnd} state;

typedef struct cast_zone_s cast_zone;
typedef struct cast_zone_s{
	unsigned short int id;
	comp_t* comp;
	pos_t pos;
	time_t fin; // use difftime
};

cast_zone * newCastZone(tuile_t *tuile, comp_t *comp, pos_t pos, time_t fin);
unsigned int updateCastZone(tuile_t *tuile, cast_zone *cast);

#endif