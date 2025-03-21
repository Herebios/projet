#include "cast_client.h"

cast_zone_t * newCastZone(tuile_t *tuile, comp_t *comp, unsigned short int id, pos_t pos){
    cast_zone_t *c = (cast_zone_t *) malloc(sizeof(cast_zone_t));
    c->id = id;
    c->comp = comp;
    c->pos = pos;
    // liste add in tiles
}

void updatePosCastZone(tuile_t *tuile, cast_zone_t *cast, pos_t pos){

}

void removeCastZone(tuile_t *tuile, cast_zone_t *cast){
    //remove in tuile
    free(cast);
}
