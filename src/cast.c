#include "cast.h"

int comparer(unsigned short int *e1, cast_t *e2){
    if (*e1 == e2->id){
        return 0;
    }
    return (*e1 > e2->id) ? 1 : 0;
}

int comparer_cb(void *e1, void *e2){
    return comparer(e1, e2);
}

void * trouver_supprimer_cb(liste * l, unsigned short int id){
	return trouver_supprimer_liste(l, &id, comparer_cb);
}
