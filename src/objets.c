/**
 * @file objets.c
 * @author Nathan
 * @brief fichier contenant les fonctions permettant la création des objets et la mises à jour des compétences des persos
 */

#include <stdio.h>
#include "objets.h"

//modifier NB_OBJETS dans le .h
objet_t tab_objets[NB_OBJETS]={
{"Baguette de magicien", commun, {{0,0},{0,0},{10,add},{0,0}}},
{"Epee lourde", commun, {{0,0},{10,add},{0,0},{-2,add}}},
{"Orbe divin", legendaire, {{10,add},{0.9,mult},{2,mult},{0,0}}}
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
