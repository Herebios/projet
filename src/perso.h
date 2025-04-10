/**
 * @file perso.h
 * @author Baptiste
 * @brief Permet la créations de personnages des joueurs
 */

#ifndef _PERSO_H_
#define _PERSO_H_

#include "prepro.h"
#include "objet.h"
#include "competences.h"
#include "SDL_def.h"
#include "types.h"

typedef struct perso_s{
	classe_t classe;
	octet niveau;
    char *nom;
	dir_t dir;
	//statistiques du perso, stat_t indice
	int stats_base[4];//stats de base
	int stats[4];//stats après objets
	int vie_reelle;
	SDL_Texture * textures_objets[5];

	comp_t * competences[NB_COMP];//icomp_t indice
	objet_t * objets[PERSO_OBJETS_MAX];//pointeurs sur les objets statiques

	unsigned char iperso, equipe;
	SDL_Rect rect;//position tuile
	pos_t pos_map;//position map, indices pour map[][]
}perso_t;

/**
 * @brief Créer un perso
 * @param sortie : Pointeur sur le perso
 * @param classe du perso
 * @param pseudo joueur
 * @param indice client
 */
void creer_perso(perso_t *, classe_t, char *, int ind, int equipe);

/**
 * @brief Détruire un perso
 * @param Pointeur sur le perso
 */
void detruire_perso(perso_t *);

/**
 * @brief Affiche les objets d'un joueur en console
 * @param Pointeur sur perso
 */
void afficher_objets_perso(perso_t *);

/**
 * @brief Affiche les stats d'un perso en console
 * @param Pointeur sur le perso
 */
void afficher_stats_perso(perso_t *);

/**
 * @brief Recalcule les stats d'un personnage en prenant en compte ses objets
 * @param Pointeur sur perso
 */
void update_stats(perso_t *);


/**
 * @brief Ajoute un objet à l'inventaire d'un joueur
 * @param Pointeur sur perso
 * @param Indice de l'objet dans tab_objets
 * @return un entier
 */
int ajouter_objet_joueur(perso_t *, int);

/**
 * @brief Retire un objet de l'inventaire du joueur
 * @param Pointeur sur perso
 * @param Indice de l'objet dans l'inventaire
 */
void retirer_objet_joueur(perso_t *, int);

#endif
