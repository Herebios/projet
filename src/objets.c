/**
 * @file objets.c
 * @author nathan
 * @brief fichier contenant les fonctions permettant la création des objets et la mises à jour des compétences des persos
 */

#include <stdio.h>
#include <stdlib.h>
#include "objets.h"

t_objet tabObjets[NB_OBJETS];

void creer_objet(objet_t * objet, char * nom, rarete_t rarete, prio_t vie, prio_t force, prio_t magie, prio_t speed){
    objet->nom = nom;
    objet->rarete = rarete;
    objet->vie = vie;
    objet->force = force;
    objet->magie = magie;
    objet->speed = speed;
}

/*
Il faudra afficher sur la fenêtre sdl
*/
void affiche_objet(t_objet * objet) {
    printf("%s :\n", objet->nom);
    printf("\tRarete : %d\n", objet->raretee);
    printf("\tMagie  : val=%f\tprio=%d\n", objet->magie.valeur, objet->magie.priority);
    printf("\tForce  : val=%f\tprio=%d\n", objet->force.valeur, objet->force.priority);
    printf("\tSoin   : val=%f\tprio=%d\n", objet->soin.valeur, objet->soin.priority);
    printf("\tSpeed  : val=%f\tprio=%d\n\n", objet->moveSpeed.valeur, objet->moveSpeed.priority);
}

void udpdate_stats(t_statsPerso * perso) {
    // Parcourt des éléments non modifiés, on leur appplique les stats de base du perso
    for (int i = 0; i < perso->nbObjets; i++) {
        if (perso->listeObj[i].magie.priority == 0) {
            perso->magie.newStats = perso->magie.statsBase;
        }
        if (perso->listeObj[i].force.priority == 0) {
            perso->force.newStats = perso->force.statsBase;
        }
        if (perso->listeObj[i].soin.priority == 0) {
            perso->pv.newStats = perso->pv.statsBase;
        }
        if (perso->listeObj[i].moveSpeed.priority == 0) {
            perso->vitesse.newStats = perso->vitesse.statsBase;
        }
    }

    //parcourt des élément à multiplier
    for (int i = 0; i < perso->nbObjets; i++) {
        if (perso->listeObj[i].magie.priority == 1) {
            perso->magie.newStats = (perso->magie.statsBase) * (perso->listeObj[i].magie.valeur);
        }
        if (perso->listeObj[i].force.priority == 1) {
            perso->force.newStats = (perso->force.statsBase) * (perso->listeObj[i].force.valeur);
        }
        if (perso->listeObj[i].soin.priority == 1) {
            perso->pv.newStats = (perso->pv.statsBase) * (perso->listeObj[i].soin.valeur);
        }
        if (perso->listeObj[i].moveSpeed.priority == 1) {
            perso->vitesse.newStats =(perso->vitesse.statsBase) * (perso->listeObj[i].moveSpeed.valeur);
        }
    }

    //parcourt des éléments à ajouter
    for (int i = 0; i < perso->nbObjets; i++) {
        if (perso->listeObj[i].magie.priority == 2) {
            perso->magie.newStats = (perso->magie.statsBase) + (perso->listeObj[i].magie.valeur);
        }
        if (perso->listeObj[i].force.priority == 2) {
            perso->force.newStats = (perso->force.statsBase) + (perso->listeObj[i].force.valeur);
        }
        if (perso->listeObj[i].soin.priority == 2) {
            perso->pv.newStats =(perso->pv.statsBase) + (perso->listeObj[i].soin.valeur);
        }
        if (perso->listeObj[i].moveSpeed.priority == 2) {
            perso->vitesse.newStats = (perso->vitesse.statsBase) + (perso->listeObj[i].moveSpeed.valeur);
        }
    }
}

void affiche_stats_perso(t_statsPerso * perso) {
    printf("Stats de base :\n");
    printf("\tMagie   : %f\n", perso->magie.statsBase);
    printf("\tForce   : %f\n", perso->force.statsBase);
    printf("\tPV      : %d\n", perso->pv.statsBase);
    printf("\tVitesse : %d\n\n", perso->vitesse.statsBase);
    printf("Stats actualisées :\n");
    printf("\tMagie   : %f\n", perso->magie.newStats);
    printf("\tForce   : %f\n", perso->force.newStats);
    printf("\tPV      : %d\n", perso->pv.newStats);
    printf("\tVitesse : %d\n\n", perso->vitesse.newStats);
} 

void nouvel_objet(t_statsPerso * perso, t_objet objetAjoute) {
    if (perso->nbObjets == 5) {
        printf("Le joueur a déja 5 objets, on ne peut pas en rajouter un autre\n");
        exit(0);
    }
    else {
        perso->listeObj[perso->nbObjets] = objetAjoute;
        (perso->nbObjets)++;
    }
    
}
void retirer_objet(t_statsPerso * perso, int positionInventaire) {
    if (perso->nbObjets == 0) {
        printf("Le joueur n'a plus d'objets, on ne peut pas lui en retirer\n");
        exit(1);
    }
    else {
        for (int i = 1; i < (perso->nbObjets) + 1; i++) {
            if (i >= positionInventaire) {
                perso->listeObj[i - 1] = perso->listeObj[i];
            }
        }
        (perso->nbObjets)--;
    }
    
}

void afficher_objets_perso(t_statsPerso * perso) {
    for (int i = 0; i < perso->nbObjets; i++) {
        printf("Objet %d : %s\n", i + 1, perso->listeObj[i].nom);
    }
}


int main() {
    int i = 0;
    creer_objet(tabObjets + i++, "Bague du magicien", commun, (t_objetPrio){1.2, 1}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Bottes du magicien", commun, (t_objetPrio){1.1, 1}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){6, 2});
    creer_objet(tabObjets + i++, "Baguette du magicien", commun, (t_objetPrio){1.3, 1}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){-4, 2});
    creer_objet(tabObjets + i++, "Bracelet du GOAT", commun, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){23, 2}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Bague du mage noir", commun, (t_objetPrio){1.25, 1}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Talisman des arcanes", rare, (t_objetPrio){1.4, 1}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){-2, 2});
    creer_objet(tabObjets + i++, "Baguette runique", commun, (t_objetPrio){1.3, 1}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){-4, 2});
    creer_objet(tabObjets + i++, "Tome des anciens", epique, (t_objetPrio){1.5, 1}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){-3, 2});
    creer_objet(tabObjets + i++, "Anneau de sagesse", rare, (t_objetPrio){1.2, 1}, (t_objetPrio){0, 0}, (t_objetPrio){10, 2}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Gants du combattant", commun, (t_objetPrio){0, 0}, (t_objetPrio){1.15, 1}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Ceinture du colosse", epique, (t_objetPrio){0, 0}, (t_objetPrio){1.3, 1}, (t_objetPrio){0, 0}, (t_objetPrio){-3, 2});
    creer_objet(tabObjets + i++, "Marteau du titan", legendaire, (t_objetPrio){0, 0}, (t_objetPrio){1.5, 1}, (t_objetPrio){0, 0}, (t_objetPrio){-5, 2});
    creer_objet(tabObjets + i++, "Épée des tempêtes", rare, (t_objetPrio){0, 0}, (t_objetPrio){1.2, 1}, (t_objetPrio){0, 0}, (t_objetPrio){-2, 2});
    creer_objet(tabObjets + i++, "Gants en acier", commun, (t_objetPrio){0, 0}, (t_objetPrio){1.1, 1}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Casque du gardien", commun, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){12, 2}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Plastron du roc", rare, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){20, 2}, (t_objetPrio){-3, 2});
    creer_objet(tabObjets + i++, "Bouclier du dragon", legendaire, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){30, 2}, (t_objetPrio){-5, 2});
    creer_objet(tabObjets + i++, "Gants renforcés", commun, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){8, 2}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Bottes en acier", rare, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){15, 2}, (t_objetPrio){-2, 2});
    creer_objet(tabObjets + i++, "Bottes célestes", legendaire, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){10, 2});
    creer_objet(tabObjets + i++, "Anneau de vélocité", rare, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){7, 2});
    creer_objet(tabObjets + i++, "Bottes du vent", commun, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){5, 2});
    creer_objet(tabObjets + i++, "Cape du sprinteur", epique, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){12, 2});
    creer_objet(tabObjets + i++, "Bracelet d'agilité", rare, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){8, 2});
    creer_objet(tabObjets + i++, "Charme du destin", commun, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){5, 2}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Sacoche du vagabond", rare, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){8, 2}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Médaillon porte-bonheur", epique, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){12, 2}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Talisman de la fortune", legendaire, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){15, 2}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Anneau du hasard", commun, (t_objetPrio){0, 0}, (t_objetPrio){0, 0}, (t_objetPrio){4, 2}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Épée du roi déchu", epique, (t_objetPrio){1.1, 1}, (t_objetPrio){1.2, 1}, (t_objetPrio){0, 0}, (t_objetPrio){-4, 2});
    creer_objet(tabObjets + i++, "Orbe mystique", legendaire, (t_objetPrio){1.5, 1}, (t_objetPrio){0.8, 1}, (t_objetPrio){20, 2}, (t_objetPrio){0, 0});
    creer_objet(tabObjets + i++, "Bâton du sorcier-roi", legendaire, (t_objetPrio){1.6, 1}, (t_objetPrio){0.9, 1}, (t_objetPrio){10, 2}, (t_objetPrio){-3, 2});
    creer_objet(tabObjets + i++, "Lance des cieux", epique, (t_objetPrio){1.2, 1}, (t_objetPrio){1.3, 1}, (t_objetPrio){0, 0}, (t_objetPrio){-5, 2});
    creer_objet(tabObjets + i++, "Cuirasse du paladin", legendaire, (t_objetPrio){0, 0}, (t_objetPrio){1.1, 1}, (t_objetPrio){25, 2}, (t_objetPrio){-3, 2});

    /*
    for (int i = 0; i < NB_OBJETS; i++) {
        affiche_tout_objets(tabObjets + i);
    }
    */

    affiche_1_objet(tabObjets + 22);
    t_statsPerso mage; 

    creer_stats_perso(&mage, "Mage", 2, 0.5, 50, 10);

    nouvel_objet(&mage, tabObjets[0]);
    nouvel_objet(&mage, tabObjets[33]);
    afficher_objets_perso(&mage);

    udpdate_stats(&mage);
    affiche_stats_perso(&mage);

    return 0;
}

