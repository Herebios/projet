#include "cast_server.h"

cast_zone_t * newCastZone(tuile_t *tuile, comp_t *comp, pos_t pos, time_t fin){
    static unsigned short int last_id = 0;
    cast_zone_t *cast = (cast_zone_t*) malloc(sizeof(cast_zone_t));
    cast->cast.id = last_id;
    cast->comp = comp;
    cast->pos = pos;
    cast->fin = fin;
    ajout_fin_liste(tuile->liste_casts, cast, sizeof (cast_zone_t *));
    //Broadcast // 300
    last_id++;
    return cast;
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

//char as bool
char 

void updateCastZone(tuile_t *tuile, unsigned short int id){
    cast_zone_t *cast = getCastZone(tuile, id);
    tete_liste(tuile->liste_casts);
    while (!hors_liste(tuile->liste_casts)){
        if ()
    }
}

