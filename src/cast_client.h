#ifndef __CAST_CLIENT__
#define __CAST_CLIENT__

#include "cast.h"
// -lrt ou -lc
//seconds : 1.0e-9 ; ms : 1.0e-6
typedef enum {onTouch, onEnd} state;

typedef struct cast_zone_s cast_zone_t;
typedef struct cast_zone_s{
	cast_t cast;
	comp_t* comp;
	pos_t pos;
};

cast_zone_t * newCastZone(tuile_t *tuile, comp_t *comp, unsigned short int id, pos_t pos);
cast_zone_t *getCastZone(tuile_t *tuile, unsigned short int id);
cast_zone_t *removeCastZone(tuile_t *tuile, unsigned short int id);

#endif