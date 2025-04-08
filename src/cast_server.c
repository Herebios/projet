#include "cast_server.h"

cast_zone_t * newCastZone(tuile_t *tuile, comp_t *comp, pos_t pos, struct timespec fin){
    static unsigned short int last_id = 0;
    cast_zone_t *cast = (cast_zone_t*) malloc(sizeof(cast_zone_t));
    cast->cast.id = last_id;
    cast->comp = comp;
    cast->pos = pos;
    cast->fin = fin;
    ajout_fin_liste(tuile->liste_casts, cast, sizeof (cast_zone_t *));

    char paquet[512];
    //  sprintf(paquet, "%d",);


    sprintf(paquet, ";\0");
    broadcast(paquet, -1);

    last_id++;
    return cast;
}

//accesseur
// use get as callBack
cast_zone_t *getCastZone(tuile_t *tuile, unsigned short int id){
    return getCast(tuile, id);
    // multicast
}
//accesseur
// use remove as callBack
cast_zone_t *removeCastZone(tuile_t *tuile, unsigned short int id){
    return removeCast(tuile, id);
    // multicast
}

//char as bool
char isPlayerInZone(perso_t * perso, cast_zone_t *cast){
	double distance = sqrt(abs(perso->rect.x - cast->pos.x) + abs(perso->rect.y - cast->pos.y));
    return (distance < cast->comp->distance);
}

void updateCastZone(tuile_t *tuile, unsigned short int id){
    cast_zone_t *cast = getCastZone(tuile, id);
    tete_liste(tuile->liste_joueurs);
    while (!hors_liste(tuile->liste_joueurs)){
        perso_t *perso = (perso_t *) get_liste(tuile->liste_joueurs);
        if (isPlayerInZone(perso, cast)){
            // perso take damage (unicast)
        }
        suivant_liste(tuile->liste_joueurs);
    }
    struct timespec tUpdate = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &tUpdate);
    if (cast->fin.tv_sec < tUpdate.tv_sec || (cast->fin.tv_sec == tUpdate.tv_sec && cast->fin.tv_nsec < tUpdate.tv_nsec)){
        removeCastZone(tuile, id);
    }
}

