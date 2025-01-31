/**
 * @file perso.h
 * @brief Permet la créations de personnages des joueurs
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//portées d'attaque
#define pMage 15
#define pArcher 10 
#define pTank 1
#define pEpeiste 3
#define pInformaticien 4 //temporaire
#define pNinja 5
#define pDruide 9
#define pAspergeur 12

#define nbJoueursMax 4

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
    char * nom; ///< nom du personnage
    int portee; ///< portée de l'attaque du perso
    float pv;   ///< points de vie du personnage
    char * capa;
    char * dash;
}t_perso;

/**
 * @brief Créer une structure en fonction du nom passé en paramètre
 * @param persoACreer nom du personnage à creer
 * @return Renvoie une structure t_perso en fonction du nom passé en paramètre
 */
t_perso creerPerso(porteePerso persoACreer);

/**
 * @brief Créer la liste des personnages qui seront jouées
 * @param tabPersos La liste des personnages en entrée (char*) qui seront à créer
 * @param nbJoueurs Le nombre de joueurs présents dans la partie.
 * @param tabRes Le tableau de structure t_perso
 * @return Renvoie un pointeur sur une liste de personnages de type t_perso.
 */
void initListePersos(char ** tabPersos, int nbJoueurs, t_perso * tabRes);