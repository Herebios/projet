/**
 * @file objets.h
 * @author Nathan
 * @brief Déclaration des objets, est inclus dans perso.h
 */

#include "types.h"

#define NB_OBJETS 3
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
	prio_t stats[4];//stats_t comme perso
};

extern objet_t tab_objets[NB_OBJETS];

/**
 * @brief Créer un nouvel objet
 * @param objet pointeur sur l'objet à créer
 * @param tous les champs de l'objet
 */
void creer_objet(objet_t *, char * nom, rarete_t rarete, prio_t vie, prio_t force, prio_t magie, prio_t speed);

/**
 * @brief Afficher les champs d'un objet en console
 * @param Pointeur sur objet
 */
void afficher_objet(objet_t *);
