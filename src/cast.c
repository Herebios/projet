#include "cast.h"

int comparer(unsigned short int e1, cast_t *e2){
    if (e1 == e2->id){
        return 0;
    }
    return (e1 > e2->id) ? 1 : 0;
}
int comparer_cb(unsigned short int e1, void *e2){
    return comparer(e1, e2);
}

void* getCast (tuile_t *tuile, unsigned short int id){
    return trouver_liste(tuile, id, comparer_cb);
}
void* removeCast (tuile_t *tuile, unsigned short int id){
    return trouver_supprimer_liste(tuile->liste_casts, id, comparer_cb);
}