#include <stdio.h>
#include "objet.h"

t_objet tabObjets[NB_OBJETS];


void creer_objet(t_objet * objet, char * nomObjet, t_raretee raretee, t_objetPrio structMagie, t_objetPrio structForce, t_objetPrio structSoin, t_objetPrio structmoveSpeed) {
    objet->nom = nomObjet;
    objet->raretee = raretee;
    objet->magie.valeur = structMagie.valeur;
    objet->magie.priority = structMagie.priority;
    objet->force.valeur = structForce.valeur;
    objet->force.priority = structForce.priority;
    objet->soin.valeur = structSoin.valeur;
    objet->soin.priority = structSoin.priority;
    objet->moveSpeed.valeur = structmoveSpeed.valeur;
    objet->moveSpeed.priority = structmoveSpeed.priority;
}

void affiche_objet(t_objet * objet) {
    printf("%s : \n", objet->nom);
    printf("\tRaretee : %d\n", objet->raretee);
    printf("\tMagie   : val=%f\tprio=%d\n", objet->magie.valeur, objet->magie.priority);
    printf("\tForce   : val=%f\tprio=%d\n", objet->force.valeur, objet->force.priority);
    printf("\tSoin    : val=%f\tprio=%d\n", objet->soin.valeur, objet->soin.priority);
    printf("\tSpeed   : val=%f\tprio=%d\n\n", objet->moveSpeed.valeur, objet->moveSpeed.priority);
}


void udpdateStats(t_statsPerso * perso, int * nbObjetsActuels) {
    for (int i = 0; i < *nbObjetsActuels; i++) {
        if (perso->listeObj[i].magie.priority == 1) {
            perso->magie *= perso->listeObj[i].magie.valeur;
        }
        if (perso->listeObj[i].force.priority == 1) {
            perso->force *= perso->listeObj[i].force.valeur;
        }
        if (perso->listeObj[i].soin.priority == 1) {
            perso->pv *= perso->listeObj[i].soin.valeur;
        }
        if (perso->listeObj[i].magie.priority == 1) {
            perso->vitesse *= perso->listeObj[i].moveSpeed.valeur;
        }
    }


    for (int i = 0; i < *nbObjetsActuels; i++) {
        if (perso->listeObj[i].magie.priority == 2) {
            perso->magie += perso->listeObj[i].magie.valeur;
        }
        if (perso->listeObj[i].force.priority == 2) {
            perso->force += perso->listeObj[i].force.valeur;
        }
        if (perso->listeObj[i].soin.priority == 2) {
            perso->pv += perso->listeObj[i].soin.valeur;
        }
        if (perso->listeObj[i].magie.priority == 2) {
            perso->vitesse += perso->listeObj[i].moveSpeed.valeur;
        }
    }
}

void nouvelObjet(t_statsPerso * perso, t_objet objetAjoute, int * nbObjetsActuels) {
    perso->listeObj[*nbObjetsActuels] = objetAjoute;
    (*nbObjetsActuels)++;
}
void retirerObjet(t_statsPerso * perso, t_objet objetAjoute, int * nbObjetsActuels) {
    (*nbObjetsActuels)--;
    perso->listeObj[*nbObjetsActuels] = NULL; //mettre a jour en tableau de poiteur sur t_objet (peut etre...)
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

        
    for (int i = 0; i < NB_OBJETS; i++) {
        affiche_objet(tabObjets + i);
    }

    return 0;
}

