#ifndef __CAST_SERVER__
#define __CAST_SERVER__

#include <time.h>
#include "cast.h"



typedef enum {onTouch, onEnd} state;

typedef struct cast_zone_s cast_zone_t;
typedef struct cast_zone_s{
	unsigned short int id;
	comp_t* comp;
	pos_t pos;
	time_t fin; // use difftime
};

cast_zone_t * newCastZone(tuile_t *tuile, comp_t *comp, unsigned short int id,  pos_t pos, time_t fin);
void updateCastZone(tuile_t *tuile, unsigned short int id);

#endif