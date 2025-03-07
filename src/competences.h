#include "types.h"
struct comp_s{
    char *nom, *description;
    comp_type type;
    float valeur;
    int distance;//pour un déplacement / la portée d'un skill
    short int cd;//rechargement en ms
	short int ttl;//maintient compétence en ms
    int (*fonction)(perso_t *, comp_t*);
};

