#include "cast_client.h"

cast_zone_t * newCastZone(tuile_t *tuile, comp_t *comp, unsigned short int id, pos_t pos){ // 300
    cast_zone_t *c = (cast_zone_t *) malloc(sizeof(cast_zone_t));
    c->id = id;
    c->comp = comp;
    c->pos = pos;
    ajouter_fin_cb(tuile->liste_casts, c, sizeof (cast_zone_t *));
}

void updatePosCastZone(tuile_t *tuile, cast_zone_t *cast, pos_t pos){ // 301
 //useless ?
}

void removeCastZone(tuile_t *tuile, unsigned short int id){ // 302
    trouver_supprimer_cb(tuile->liste_casts, id);
}
