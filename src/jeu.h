/**
 * @file jeu.h
 * @author Baptiste
 * @brief fonctions pour le jeu communes serv/cli
 */

#ifndef _JEU_H_
#define _JEU_H_

#include "types.h"
#include "objet.h"
#include "prepro.h"
#include "liste.h"
#include "SDL_def.h"
#include "def.h"
#include "perso.h"

extern tuile_t map[HAUTEUR_MAP][LARGEUR_MAP];
extern biome_t biomes[NB_BIOMES];
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern pos_t deplacement[8];//multiplicateur pour la direction


void end(int);
//Fonctions d'initialisation du jeu
void init_sdl(void);

void init_jeu(void);
void init_biomes(void);
void init_map(void);
void init_tuile(tuile_t*, nom_biome_t, int, int);
void detruire_tuile(tuile_t*, int mode);

void ajouter_objet_tuile(tuile_t * t, int ind_o, pos_t pos_tuile);
//!! bug possible si 2 objets identiques sur la même tuile
void retirer_objet_tuile(tuile_t * t, int ind_o);

void ajouter_joueur_tuile(tuile_t * t, int ind_j);
void retirer_joueur_tuile(tuile_t * t, int ind_j);

void nouv_texture(char*, SDL_Texture *textures[], unsigned char*);
SDL_Texture * get_nouv_texture(char*);

//a dans b
int inclus(SDL_Rect* a, SDL_Rect* b);
char collision(SDL_Rect a, SDL_Rect b);

void avancer(perso_t *);

tuile_t * get_tuile_from_pos(pos_t pos);
pos_t get_pos_from_coo(int x, int y);
tuile_t *get_tuile_joueur(perso_t * p);

//pos_tuile
void position_perso(perso_t *p, pos_t* pos);

#endif
