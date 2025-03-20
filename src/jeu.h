/**
 * @file jeu.h
 * @author Baptiste
 * @brief fonctions pour le jeu communes serv/cli
 */

#ifndef _JEU_H_
#define _JEU_H_

#include "prepro.h"

#include "SDL_def.h"
#include "def.h"

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

void nouv_texture(char*, SDL_Texture *textures[], unsigned char*);

//a dans b
bool inclus(SDL_Rect* a, SDL_Rect* b);

#endif
