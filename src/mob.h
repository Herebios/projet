/**
 * @file mob.h
 * @author Nathan
 * @brief Déclaration des monstres, est inclus dans mob.c
 */

#include "types.h"

typedef struct{
	int stats[4];   //On utilise l'enum stat_t comme indice typedef enum {vie, force, magie, speed, NB_STATS} stat_t;
	pos_t pos_map;
}mob_t;