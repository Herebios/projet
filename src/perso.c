#include "perso.h"

void creerPerso(perso_t * nouveau){
    int valide = 1;
    switch(persoACreer){
        case mage:
            nouveau.nom = "mage";
            nouveau.pv = 50;
            nouveau.capa = "heal";
            nouveau.dash = "tpTuile";
            break;
        case archer:
            nouveau.nom = "archer";
            nouveau.pv = 60;
            nouveau.capa = "tirRapide";
            nouveau.dash = "dash4cases";
            break;
        case tank:
            nouveau.nom = "tank";
            nouveau.pv = 100;
            nouveau.capa = "bouclier";
            nouveau.dash = "0 dash";
            break;
        case epeiste:
            nouveau.nom = "epeiste";
            nouveau.pv = 80;
            nouveau.capa = "heal";
            nouveau.dash = "sauteMontagne";
            break;
        case informaticien:
            nouveau.nom = "informaticien";
            nouveau.pv = 30;
            nouveau.capa = "observateur";
            nouveau.dash = "tpObservateur";
            break;
        case ninja:
            nouveau.nom = "ninja";
            nouveau.pv = 60;
            nouveau.capa = "poison";
            nouveau.dash = "invisibility";
            break;
        case druide:
            nouveau.nom = "druide";
            nouveau.pv = 50;
            nouveau.capa = "jsp";
            nouveau.dash = "jspNonPlus";
            break;
        case aspergeur:
            nouveau.nom = "aspergeur";
            nouveau.pv = 40;
            nouveau.capa = "slow";
            nouveau.dash = "encreMarioKart";
            break;
        default:
            printf("Nom de personage non valide : %d\n", persoACreer);
            valide = 0;
            break;
    }
    if(valide){
            printf("Perso créé avec succès\n");
            return nouveau;        
    }
    else{
        printf("erreur\n");
    }
}


void initPersos(classe_t * tab, int nb, t_perso * tabRes) {
    perso_t temp;
    for (int i = 0; i < nbJoueursMax; i++) {
        if (!strcmp("mage", tabPersos[i])) {
             tabRes[i] = creerPerso(mage);
        }
        else if (!strcmp("archer", tabPersos[i])) {
             tabRes[i] = creerPerso(archer);
        }
        else if (!strcmp("tank", tabPersos[i])) {
             tabRes[i] = creerPerso(tank);
        }
        else if (!strcmp("epeiste", tabPersos[i])) {
             tabRes[i] = creerPerso(epeiste);
        }
        else if (!strcmp("informaticien", tabPersos[i])) {
             tabRes[i] = creerPerso(informaticien);
        }
        else if (!strcmp("ninja", tabPersos[i])) {
             tabRes[i] = creerPerso(ninja);
        }
        else if (!strcmp("druide", tabPersos[i])) {
             tabRes[i] = creerPerso(druide);
        }
    }
}

int main(void){
    int nb_joueurs = 4;//info du server
    classe_t joueurs[nb_joueurs]={guerrier, mage, archer, assassin};
    t_perso testTabPerso[nb_joueurs];

    initListePersos(joueurs, nbJoueurs, testTabPerso);

    for (int i = 0; i < nbJoueurs; i++) {
        printf("%i ) %s\n", i + 1, (testTabPerso + i)->nom);
    }
    return 0;
}
