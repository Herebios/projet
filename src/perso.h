/**
 * @file perso.h
 * @brief Permet la créations de personnages des joueurs
 * @author Baptiste
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "objets.h"

#define unsigned char octet;

typedef enum {administrateur, guerrier, mage, archer, assassin, informaticien, druide, necromancien} classe_t;
typedef enum {vie, force, magie, speed} stats_t;

typedef enum {zone, projectile, instant} comp_type;
typedef enum {atk1, atk2, skill, mouv, ult, NB_COMP} icomp_t;

typedef struct{
	char *nom, *description;
	comp_type type;
	float value;
	short int distance;//pour un déplacement ou la portée d'un skill
	int cd;//rechargement en ms
	int (*fonction)(perso_t *, comp_t*);
}comp_t;

typedef struct {
	classe_t classe;
	octet niveau;
    char * nom;
	stats_t stats_base[4];//stats de base
	stats_t stats[4];//stats après objets
	comp_t competences[NB_COMP];//icomp_t
	objet_t objets[PERSO_OBJETS_MAX];
	int posX;
	int posY;
	size_t persoIndex;
}perso_t;

/**
 * @brief Créer une structure en fonction du nom passé en paramètre
 * @param persoACreer nom du personnage à creer
 * @return Renvoie une structure t_perso en fonction du nom passé en paramètre
 */
void creerPerso(perso_t *);

/**
 * @brief Créer la liste des personnages qui seront jouées
 * @param tabPersos La liste des personnages en entrée (char*) qui seront à créer
 * @param nbJoueurs Le nombre de joueurs présents dans la partie.
 * @param tabRes Le tableau de structure t_perso
 * @return Renvoie un pointeur sur une liste de personnages de type t_perso.
 */
void initListePersos(char ** tabPersos, int nbJoueurs, t_perso * tabRes);
