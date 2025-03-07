/**
 * @file objets.c
 * @author Nathan
 * @brief fichier contenant les fonctions permettant la création des objets et la mises à jour des compétences des persos
 */

#include <stdio.h>
#include "objets.h"

//modifier NB_OBJETS dans le .h
objet_t tab_objets[NB_OBJETS]={
{"Baguette de magicien", commun, {{0,null},{0,null},{10,add},{0,0}}},
{"Epee lourde", commun, {{0,null},{10,add},{0,null},{-2,add}}},
{"Orbe divin", legendaire, {{10,add},{0.9,mult},{2,mult},{0,null}}},
{"Bague du magicien", commun, {{1.2, mult}, {0, null}, {0, null}, {0, null}}},
{"Bottes du magicien", commun, {{1.1, mult}, {0, null}, {0, null}, {6, add}}},
{"Baguette du magicien", commun, {{1.3, mult}, {0, null}, {0, null}, {-4, add}}},
{"Bracelet du GOAT", commun, {{0, null}, {0, null}, {23, add}, {0, null}}},
{"Bague du mage noir", commun, {{1.25, mult}, {0, null}, {0, null}, {0, null}}},
{"Talisman des arcanes", rare, {{1.4, mult}, {0, null}, {0, null}, {-2, add}}},
{"Baguette runique", commun, {{1.3, mult}, {0, null}, {0, null}, {-4, add}}},
{"Tome des anciens", epique, {{1.5, mult}, {0, null}, {0, null}, {-3, add}}},
{"Anneau de sagesse", rare, {{1.2, mult}, {0, null}, {10, add}, {0, null}}},
{"Gants du combattant", commun, {{0, null}, {1.15, mult}, {0, null}, {0, null}}},
{"Ceinture du colosse", epique, {{0, null}, {1.3, mult}, {0, null}, {-3, add}}},
{"Marteau du titan", legendaire, {{0, null}, {1.5, mult}, {0, null}, {-5, add}}},
{"Épée des tempêtes", rare, {{0, null}, {1.2, mult}, {0, null}, {-2, add}}},
{"Gants en acier", commun, {{0, null}, {1.1, mult}, {0, null}, {0, null}}},
{"Casque du gardien", commun, {{0, null}, {0, null}, {12, add}, {0, null}}},
{"Plastron du roc", rare, {{0, null}, {0, null}, {20, add}, {-3, add}}},
{"Bouclier du dragon", legendaire, {{0, null}, {0, null}, {30, add}, {-5, add}}},
{"Gants renforcés", commun, {{0, null}, {0, null}, {8, add}, {0, null}}},
{"Bottes en acier", rare, {{0, null}, {0, null}, {15, add}, {-2, add}}},
{"Bottes célestes", legendaire, {{0, null}, {0, null}, {0, null}, {10, add}}},
{"Anneau de vélocité", rare, {{0, null}, {0, null}, {0, null}, {7, add}}},
{"Bottes du vent", commun, {{0, null}, {0, null}, {0, null}, {5, add}}},
{"Cape du sprinteur", epique, {{0, null}, {0, null}, {0, null}, {12, add}}},
{"Bracelet d'agilité", rare, {{0, null}, {0, null}, {0, null}, {8, add}}},
{"Charme du destin", commun, {{0, null}, {0, null}, {5, add}, {0, null}}},
{"Sacoche du vagabond", rare, {{0, null}, {0, null}, {8, add}, {0, null}}},
{"Médaillon porte-bonheur", epique, {{0, null}, {0, null}, {12, add}, {0, null}}},
{"Talisman de la fortune", legendaire, {{0, null}, {0, null}, {15, add}, {0, null}}},
{"Anneau du hasard", commun, {{0, null}, {0, null}, {4, add}, {0, null}}},
{"Épée du roi déchu", epique, {{1.1, mult}, {1.2, mult}, {0, null}, {-4, add}}},
{"Orbe mystique", legendaire, {{1.5, mult}, {0.8, mult}, {20, add}, {0, null}}},
{"Bâton du sorcier-roi", legendaire, {{1.6, mult}, {0.9, mult}, {10, add}, {-3, add}}},
{"Lance des cieux", epique, {{1.2, mult}, {1.3, mult}, {0, null}, {-5, add}}},
{"Cuirasse du paladin", legendaire, {{0, null}, {1.1, mult}, {25, add}, {-3, add}}}
};
/*
void creer_objet(objet_t * objet, char * nom, rarete_t rarete, prio_t vie, prio_t force, prio_t magie, prio_t speed){
    objet->nom = strdup(nom);
    objet->rarete = rarete;
    objet->stats[0] = vie;
    objet->stats[1] = force;
    objet->stats[2] = magie;
    objet->stats[3] = speed;
}*/

//!!Il faudra afficher sur la fenêtre sdl
void afficher_objet(objet_t * obj) {
    printf("%s :\n", obj->nom);
    printf("\tRarete   : %d\n", obj->rarete);
    printf("\tVie      : val=%.1f\tprio=%d\n", obj->stats[vie].valeur, obj->stats[vie].priority);
    printf("\tForce    : val=%.1f\tprio=%d\n", obj->stats[force].valeur, obj->stats[force].priority);
    printf("\tMagie    : val=%.1f\tprio=%d\n", obj->stats[magie].valeur, obj->stats[magie].priority);
    printf("\tSpeed    : val=%.1f\tprio=%d\n\n", obj->stats[speed].valeur, obj->stats[speed].priority);
}
/*
int main() {
    creer_objet(tabObjets + i++, "Bague du magicien", commun, (prio_t){1.2, 1}, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Bottes du magicien", commun, (prio_t){1.1, 1}, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){6, 2});
    creer_objet(tabObjets + i++, "Baguette du magicien", commun, (prio_t){1.3, 1}, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){-4, 2});
    creer_objet(tabObjets + i++, "Bracelet du GOAT", commun, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){23, 2}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Bague du mage noir", commun, (prio_t){1.25, 1}, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Talisman des arcanes", rare, (prio_t){1.4, 1}, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){-2, 2});
    creer_objet(tabObjets + i++, "Baguette runique", commun, (prio_t){1.3, 1}, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){-4, 2});
    creer_objet(tabObjets + i++, "Tome des anciens", epique, (prio_t){1.5, 1}, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){-3, 2});
    creer_objet(tabObjets + i++, "Anneau de sagesse", rare, (prio_t){1.2, 1}, (prio_t){0, 0}, (prio_t){10, 2}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Gants du combattant", commun, (prio_t){0, 0}, (prio_t){1.15, 1}, (prio_t){0, 0}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Ceinture du colosse", epique, (prio_t){0, 0}, (prio_t){1.3, 1}, (prio_t){0, 0}, (prio_t){-3, 2});
    creer_objet(tabObjets + i++, "Marteau du titan", legendaire, (prio_t){0, 0}, (prio_t){1.5, 1}, (prio_t){0, 0}, (prio_t){-5, 2});
    creer_objet(tabObjets + i++, "Épée des tempêtes", rare, (prio_t){0, 0}, (prio_t){1.2, 1}, (prio_t){0, 0}, (prio_t){-2, 2});
    creer_objet(tabObjets + i++, "Gants en acier", commun, (prio_t){0, 0}, (prio_t){1.1, 1}, (prio_t){0, 0}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Casque du gardien", commun, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){12, 2}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Plastron du roc", rare, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){20, 2}, (prio_t){-3, 2});
    creer_objet(tabObjets + i++, "Bouclier du dragon", legendaire, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){30, 2}, (prio_t){-5, 2});
    creer_objet(tabObjets + i++, "Gants renforcés", commun, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){8, 2}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Bottes en acier", rare, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){15, 2}, (prio_t){-2, 2});
    creer_objet(tabObjets + i++, "Bottes célestes", legendaire, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){10, 2});
    creer_objet(tabObjets + i++, "Anneau de vélocité", rare, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){7, 2});
    creer_objet(tabObjets + i++, "Bottes du vent", commun, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){5, 2});
    creer_objet(tabObjets + i++, "Cape du sprinteur", epique, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){12, 2});
    creer_objet(tabObjets + i++, "Bracelet d'agilité", rare, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){8, 2});
    creer_objet(tabObjets + i++, "Charme du destin", commun, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){5, 2}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Sacoche du vagabond", rare, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){8, 2}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Médaillon porte-bonheur", epique, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){12, 2}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Talisman de la fortune", legendaire, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){15, 2}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Anneau du hasard", commun, (prio_t){0, 0}, (prio_t){0, 0}, (prio_t){4, 2}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Épée du roi déchu", epique, (prio_t){1.1, 1}, (prio_t){1.2, 1}, (prio_t){0, 0}, (prio_t){-4, 2});
    creer_objet(tabObjets + i++, "Orbe mystique", legendaire, (prio_t){1.5, 1}, (prio_t){0.8, 1}, (prio_t){20, 2}, (prio_t){0, 0});
    creer_objet(tabObjets + i++, "Bâton du sorcier-roi", legendaire, (prio_t){1.6, 1}, (prio_t){0.9, 1}, (prio_t){10, 2}, (prio_t){-3, 2});
    creer_objet(tabObjets + i++, "Lance des cieux", epique, (prio_t){1.2, 1}, (prio_t){1.3, 1}, (prio_t){0, 0}, (prio_t){-5, 2});
    creer_objet(tabObjets + i++, "Cuirasse du paladin", legendaire, (prio_t){0, 0}, (prio_t){1.1, 1}, (prio_t){25, 2}, (prio_t){-3, 2});

    for (int i = 0; i < NB_OBJETS; i++)
	    afficher_objet(tab_objets + i);

    return 0;
}
*/
