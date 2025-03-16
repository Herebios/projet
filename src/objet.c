/**
 * @file objets.c
 * @author Nathan
 * @brief stats des objets
 */

#include <stdio.h>
#include "objet.h"

//modifier NB_OBJETS dans le .h
objet_t tab_objets[NB_OBJETS]={
{"Baguette du magicien", commun, {{0,null},{0,null},{10,add},{0,0}}},
{"Epee lourde", 		commun, {{0,null},{10,add},{0,null},{-2,add}}},
{"Bague du magicien", 	commun, {{1.2, mult}, {0, null}, {0, null}, {0, null}}},
{"Bottes du magicien", 	commun, {{1.1, mult}, {0, null}, {0, null}, {6, add}}},
{"Bracelet du GOAT", 	commun, {{0, null}, {0, null}, {23, add}, {0, null}}},
{"Bague du mage noir", 	commun, {{1.25, mult}, {0, null}, {0, null}, {0, null}}},
{"Baguette runique", 	commun, {{1.3, mult}, {0, null}, {0, null}, {-4, add}}},
{"Gants du combattant", commun, {{0, null}, {1.15, mult}, {0, null}, {0, null}}},
{"Gants en acier", 		commun, {{0, null}, {1.1, mult}, {0, null}, {0, null}}},
{"Casque du gardien", 	commun, {{0, null}, {0, null}, {12, add}, {0, null}}},
{"Gants renforcés", 	commun, {{0, null}, {0, null}, {8, add}, {0, null}}},
{"Bottes du vent", 		commun, {{0, null}, {0, null}, {0, null}, {5, add}}},
{"Charme du destin", 	commun, {{0, null}, {0, null}, {5, add}, {0, null}}},
{"Anneau du hasard", 	commun, {{0, null}, {0, null}, {4, add}, {0, null}}},

{"Talisman des arcanes", rare, {{1.4, mult}, {0, null}, {0, null}, {-2, add}}},
{"Anneau de sagesse", 	rare, {{1.2, mult}, {0, null}, {10, add}, {0, null}}},
{"Épée des tempêtes",	rare, {{0, null}, {1.2, mult}, {0, null}, {-2, add}}},
{"Plastron du roc", 	rare, {{0, null}, {0, null}, {20, add}, {-3, add}}},
{"Bottes en acier", 	rare, {{0, null}, {0, null}, {15, add}, {-2, add}}},
{"Anneau de vélocité", 	rare, {{0, null}, {0, null}, {0, null}, {7, add}}},
{"Bracelet d'agilité", 	rare, {{0, null}, {0, null}, {0, null}, {8, add}}},
{"Sacoche du vagabond", rare, {{0, null}, {0, null}, {8, add}, {0, null}}},

{"Tome des anciens", 	epique, {{1.5, mult}, {0, null}, {0, null}, {-3, add}}},
{"Ceinture du colosse", epique, {{0, null}, {1.3, mult}, {0, null}, {-3, add}}},
{"Cape du sprinteur", 	epique, {{0, null}, {0, null}, {0, null}, {12, add}}},
{"Lance des cieux", 	epique, {{1.2, mult}, {1.3, mult}, {0, null}, {-5, add}}},
{"Épée du roi déchu", 	epique, {{1.1, mult}, {1.2, mult}, {0, null}, {-4, add}}},
{"Médaillon porte-bonheur", epique, {{0, null}, {0, null}, {12, add}, {0, null}}},

{"Marteau du titan", 	legendaire, {{0, null}, {1.5, mult}, {0, null}, {-5, add}}},
{"Orbe divine", 		legendaire, {{10,add},{0.9,mult},{2,mult},{0,null}}},
{"Bouclier du dragon", 	legendaire, {{0, null}, {0, null}, {30, add}, {-5, add}}},
{"Bottes célestes", 	legendaire, {{0, null}, {0, null}, {0, null}, {10, add}}},
{"Talisman de la fortune", legendaire, {{0, null}, {0, null}, {15, add}, {0, null}}},
{"Orbe mystique", 		legendaire, {{1.5, mult}, {0.8, mult}, {20, add}, {0, null}}},
{"Bâton du sorcier-roi", legendaire, {{1.6, mult}, {0.9, mult}, {10, add}, {-3, add}}},
{"Cuirasse du paladin", legendaire, {{0, null}, {1.1, mult}, {25, add}, {-3, add}}}
};

//!!Il faudra afficher sur la fenêtre sdl
void afficher_objet(objet_t * obj) {
    printf("%s :\n", obj->nom);
    printf("\tRarete   : %d\n", obj->rarete);
    printf("\tVie      : val=%.1f\tprio=%d\n", obj->stats[vie].valeur, obj->stats[vie].priority);
    printf("\tForce    : val=%.1f\tprio=%d\n", obj->stats[force].valeur, obj->stats[force].priority);
    printf("\tMagie    : val=%.1f\tprio=%d\n", obj->stats[magie].valeur, obj->stats[magie].priority);
    printf("\tSpeed    : val=%.1f\tprio=%d\n\n", obj->stats[speed].valeur, obj->stats[speed].priority);
}
