#include "cast_server.h"

int comparer(cast_zone_t *e1, cast_zone_t *e2){
    if (e1->id == e2->id){
        return 0;
    }
    return (e1->id > e2->id) ? 1 : 0;
}

int comparer_cb(void *e1, void *e2){
    return comparer(e1, e2);
}

cast_zone_t * newCastZone(tuile_t *tuile, comp_t *comp, unsigned short int id, pos_t pos, time_t fin){
    static unsigned short int last_id = 0;
    cast_zone_t *c = (cast_zone_t*) malloc(sizeof(cast_zone_t));
    c->id = last_id;
    c->comp = comp;
    c->pos = pos;
    c->fin = fin;
    ajouter_fin_liste(tuile->liste_casts, c, sizeof (cast_zone_t *));
    //Broadcast // 300
    last_id++;
    return c;
}

void updateCastZone(tuile_t *tuile, unsigned short int id){
    cast_t *cast = (cast_t*) trouver_liste(tuile->liste_casts);
    if (difftime(cast->fin, time(NULL)) > 0){
        // BC 302
        // tuile delete cast
        free(cast);
    }
    //detect collision
    // move
    //send collision and new pos
}
