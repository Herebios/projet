/**
 * @file objet.h
 * @author Nathan
 * @brief Déclaration des objets, est inclus dans perso.h
 */

#ifndef _OBJET_H_
#define _OBJET_H_

#include "types.h"

#define NB_OBJETS 36
#define NB_OBJETS_C 14
#define NB_OBJETS_R 8
#define NB_OBJETS_E 6
#define NB_OBJETS_L 8
#define PERSO_OBJETS_MAX 5

typedef enum {commun, rare, epique, legendaire} rarete_t;
typedef enum {null, mult, add} priority_t;

/**
 * @brief Représente la priorité des calculs entre somme et produit
 */
typedef struct {
    float valeur;       /**< bonus apparté par l'objet */
    priority_t priority;/**< priorité de l'objet (calcul des addition avant les multiplications) */
} prio_t;

/**
 * @brief Représente un objet
 */
struct objet_s {
    char * nom;         /**< nom de l'objet */
    rarete_t rarete;    /**< raretée de l'objet */
	prio_t stats[4];
    char isSpawn;   /**< statistiques de l'objet */
	int ind;  /**< indice de l'objet dans l'inventaire */
};

extern objet_t tab_objets[NB_OBJETS];

/**
 * @brief Afficher les champs d'un objet en console
 * @param objet_t pointeur sur objet
 */
void afficher_objet(objet_t *);

#endif
