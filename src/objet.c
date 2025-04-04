/**
 * @file objets.c
 * @author Nathan
 * @brief stats des objets
 */

#include <stdio.h>
#include "objet.h"

//modifier NB_OBJETS dans le .h
objet_t tab_objets[NB_OBJETS] = {
    {"Baguette du magicien", 	commun, {{0, null}, {0, null}, {10, add}, {0, 0}}, {0, 0}},
    {"Epee lourde", 			commun, {{0, null}, {10, add}, {0, null}, {-2, add}}, {0, 0}},
    {"Bague du magicien", 		commun, {{1.2, mult}, {0, null}, {0, null}, {0, null}}, {0, 0}},
    {"Bottes du magicien", 		commun, {{1.1, mult}, {0, null}, {0, null}, {6, add}}, {0, 0}},
    {"Bracelet du GOAT", 		commun, {{0, null}, {0, null}, {23, add}, {0, null}}, {0, 0}},
    {"Bague du mage noir", 		commun, {{1.25, mult}, {0, null}, {0, null}, {0, null}}, {0, 0}},
    {"Baguette runique", 		commun, {{1.3, mult}, {0, null}, {0, null}, {-4, add}}, {0, 0}},
    {"Gants du combattant", 	commun, {{0, null}, {1.15, mult}, {0, null}, {0, null}}, {0, 0}},
    {"Gants en acier", 			commun, {{0, null}, {1.1, mult}, {0, null}, {0, null}}, {0, 0}},
    {"Casque du gardien", 		commun, {{0, null}, {0, null}, {12, add}, {0, null}}, {0, 0}},
    {"Gants renforces", 		commun, {{0, null}, {0, null}, {8, add}, {0, null}}, {0, 0}},
    {"Bottes du vent", 			commun, {{0, null}, {0, null}, {0, null}, {5, add}}, {0, 0}},
    {"Charme du destin", 		commun, {{0, null}, {0, null}, {5, add}, {0, null}}, {0, 0}},
    {"Anneau du hasard", 		commun, {{0, null}, {0, null}, {4, add}, {0, null}}, {0, 0}},

    {"Talisman des arcanes", 	rare, {{1.4, mult}, {0, null}, {0, null}, {-2, add}}, {0, 0}},
    {"Anneau de sagesse", 		rare, {{1.2, mult}, {0, null}, {10, add}, {0, null}}, {0, 0}},
    {"Epee des tempetes",		rare, {{0, null}, {1.2, mult}, {0, null}, {-2, add}}, {0, 0}},
    {"Plastron du roc", 		rare, {{0, null}, {0, null}, {20, add}, {-3, add}}, {0, 0}},
    {"Bottes en acier", 		rare, {{0, null}, {0, null}, {15, add}, {-2, add}}, {0, 0}},
    {"Anneau de velocite", 		rare, {{0, null}, {0, null}, {0, null}, {7, add}}, {0, 0}},
    {"Bracelet d'agilité", 		rare, {{0, null}, {0, null}, {0, null}, {8, add}}, {0, 0}},
    {"Sacoche du vagabond", 	rare, {{0, null}, {0, null}, {8, add}, {0, null}}, {0, 0}},

    {"Tome des anciens", 		epique, {{1.5, mult}, {0, null}, {0, null}, {-3, add}}, {0, 0}},
    {"Ceinture du colosse", 	epique, {{0, null}, {1.3, mult}, {0, null}, {-3, add}}, {0, 0}},
    {"Cape du sprinteur", 		epique, {{0, null}, {0, null}, {0, null}, {12, add}}, {0, 0}},
    {"Lance des cieux", 		epique, {{1.2, mult}, {1.3, mult}, {0, null}, {-5, add}}, {0, 0}},
    {"Epee du roi dechu", 		epique, {{1.1, mult}, {1.2, mult}, {0, null}, {-4, add}}, {0, 0}},
    {"Medaillon porte-bonheur", epique, {{0, null}, {0, null}, {12, add}, {0, null}}, {0, 0}},

    {"Marteau du titan", 		legendaire, {{0, null}, {1.5, mult}, {0, null}, {-5, add}}, {0, 0}},
    {"Orbe divine", 			legendaire, {{10, add}, {0.9, mult}, {2, mult}, {0, null}}, {0, 0}},
    {"Bouclier du dragon", 		legendaire, {{0, null}, {0, null}, {30, add}, {-5, add}}, {0, 0}},
    {"Bottes celestes", 		legendaire, {{0, null}, {0, null}, {0, null}, {10, add}}, {0, 0}},
    {"Talisman de la fortune", 	legendaire, {{0, null}, {0, null}, {15, add}, {0, null}}, {0, 0}},
    {"Orbe mystique", 			legendaire, {{1.5, mult}, {0.8, mult}, {20, add}, {0, null}}, {0, 0}},
    {"Baton du sorcier-roi", 	legendaire, {{1.6, mult}, {0.9, mult}, {10, add}, {-3, add}}, {0, 0}},
    {"Cuirasse du paladin", 	legendaire, {{0, null}, {1.1, mult}, {25, add}, {-3, add}}, {0, 0}}
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
