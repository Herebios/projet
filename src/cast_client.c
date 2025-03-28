#include "cast_client.h"

cast_zone_t * newCastZone(tuile_t *tuile, comp_t *comp, unsigned short int id, pos_t pos){ // 300
    cast_zone_t *c = (cast_zone_t *) malloc(sizeof(cast_zone_t));
    c->cast.id = id;
    c->comp = comp;
    c->pos = pos;
    ajout_fin_liste(tuile->liste_casts, c, sizeof (cast_zone_t *));
}

//accesseur
// use get as callBack
cast_zone_t *getCastZone(tuile_t *tuile, unsigned short int id){
    return getCast(tuile, id);
}
//accesseur
// use remove as callBack
cast_zone_t *removeCastZone(tuile_t *tuile, unsigned short int id){
    return removeCast(tuile, id);
}

