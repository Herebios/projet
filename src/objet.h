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
typedef struct {
    float valeur;
    priority_t priority;
} prio_t;


struct objet_s {
    char * nom;//permet de charger la texture
    rarete_t rarete;
	prio_t stats[4];//indices stats_t
	unsigned char ind;
};

extern objet_t tab_objets[NB_OBJETS];

/**
 * @brief Afficher les champs d'un objet en console
 * @param Pointeur sur objet
 */
void afficher_objet(objet_t *);

#endif
