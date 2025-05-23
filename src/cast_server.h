#ifndef __CAST_SERVER__
#define __CAST_SERVER__

#include "cast.h"
#include "serv_commun.h"

typedef enum {onTouch, onEnd} state;

typedef struct cast_zone_s cast_zone_t;
typedef struct cast_zone_s{
	cast_t cast;
	comp_t* comp;
	pos_t pos;
	struct timespec fin;
};

cast_zone_t * newCastZone(tuile_t *tuile, comp_t *comp,  pos_t pos, struct timespec fin);
cast_zone_t *getCastZone(tuile_t *tuile, unsigned short int id);
cast_zone_t *removeCastZone(tuile_t *tuile, unsigned short int id);




#endif