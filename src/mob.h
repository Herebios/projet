/**
 * @file mob.h
 * @author Nathan
 * @brief Déclaration des monstres, est inclus dans mob.c
 */

#include "types.h"
#include "SDL_def.h"

typedef struct{
	int stats[4];   	/**< statitiques des mobs {vie, force, magie, speed, NB_STATS}*/
	SDL_Rect pos_map;	/**< position du mob, largeur et hauteur*/
}mob_t;


/**
 * @brief calcule les coordonnées du milieu d'un monstre
 * @param mob pointeur sur un monstre
 * @return retourne les coordonnées du centre du monstre
 */
pos_t * calculMilieuMob(mob_t * mob);

/**
 * @brief calcule les coordonnées du milieu d'un personnage
 * @param p pointeur sur un personnage
 * @return retourne les coordonnées du centre du personnage
 */
pos_t * calculMilieuPerso(perso_t * p);

/**
 * @brief Calcule la distance entre le personnage et le monstre tous les deux passés en paramètres
 * @param p pointeur sur un personnage
 * @param mob pointeur sur un monstre
 * @return Distance entre le personnage et le monstre
 */
double distance_mob(perso_t *p, mob_t *mob);

/**
 * @brief Trouve le joueur de la liste Joueurs le plus proche du monstre passé en paramètres 
 * @param listePersos liste de pointeurs sur personnage
 * @param mob pointeur sur un monstre
 * @param nbJoueurs nombre de joueurs dans la liste
 * @return Distance entre le personnage et le monstre
 */
perso_t * joueur_plus_proche_mob(perso_t ** listePersos, mob_t *mob, int nbJoueurs);

/**
 * @brief Retourne l'angle en radians entre le vecteur le personnage et le monstre 
 * @param p pointeur sur un personnage
 * @param mob pointeur sur un monstre
 * @return angle entre le personnage et le monstre
 */
double angle_perso_mob(perso_t *p, mob_t *mob);

/**
 * @brief Retourne l'angle en radians entre le vecteur (personnage, monstre) tous les deux passés en paramètres et le vecteur horizontal dirigé vers la droite
 * @param p pointeur sur un personnage
 * @param mob pointeur sur un monstre
 * @return angle entre le personnage et le monstre
 */
void update_pos_mob(perso_t *p, mob_t *mob);