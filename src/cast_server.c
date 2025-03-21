#include "cast_server.h"

cast_zone * newCastZone(tuile_t *tuile, comp_t *comp, pos_t pos, time_t fin){
    static unsigned short int last_id = 0;
    cast_zone *c = (cast_zone*) malloc(sizeof(comp_t));
    c->id = last_id;
    c->comp = comp;
    c->pos = pos;
    c->fin = fin;
    //Liste add in tiles
    //Broadcast
    last_id++;
    return c;
}

void updateCastZone(tuile_t *tuile, cast_zone *cast){
    if (difftime(cast->fin, time(NULL)) > 0){
        //BC
        // tuile delete cast
        free(cast);
    }
    //detect collision
    // move
    //send collision and new pos
}
