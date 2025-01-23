#include <stdio.h>

//portées d'attaque
#define pMage 15
#define pArcher 10 
#define pTank 1
#define pEpeiste 3
#define pInformaticien 4 //temporaire
#define pNinja 5
#define pDruide 9
#define pAspergeur 12

typedef enum{
    mage = pMage, 
    archer = pArcher, 
    tank = pTank, 
    epeiste = pEpeiste, 
    informaticien = pInformaticien, 
    ninja = pNinja, 
    druide = pDruide, 
    aspergeur = pAspergeur
}porteePerso;


typedef struct {
    int portee;
    float pv;
    char * capa;
    char * dash;
}t_perso;


t_perso creerPerso(porteePerso persoACreer){
    t_perso nouveau;
    nouveau.portee = persoACreer;
    int valide = 1;
    switch(persoACreer){
        case mage:
            nouveau.pv = 50;
            nouveau.capa = "heal";
            nouveau.dash = "tpTuile";
            break;
        case archer:
            nouveau.pv = 60;
            nouveau.capa = "tirRapide";
            nouveau.dash = "dash4cases";
            break;
        case tank:
            nouveau.pv = 100;
            nouveau.capa = "bouclier";
            nouveau.dash = "0 dash";
            break;
        case epeiste:
            nouveau.pv = 80;
            nouveau.capa = "heal";
            nouveau.dash = "sauteMontagne";
            break;
        case informaticien:
            nouveau.pv = 30;
            nouveau.capa = "observateur";
            nouveau.dash = "tpObservateur";
            break;
        case ninja:
            nouveau.pv = 60;
            nouveau.capa = "poison";
            nouveau.dash = "invisibility";
            break;
        case druide:
            nouveau.pv = 50;
            nouveau.capa = "jsp";
            nouveau.dash = "jspNonPlus";
            break;
        case aspergeur:
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



int main(void){
    t_perso nouveau = creerPerso(mage);
    return 0;
}