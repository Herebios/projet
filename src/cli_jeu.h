#ifndef _CLI_JEU_H_
#define _CLI_JEU_H_

#include "cli_commun.h"
#include "jeu.h"
#include "id_actions.h"

#define ecran() SDL_RenderPresent(renderer)

extern SDL_Texture * texture_tuile;

void init_joueurs_client(perso_t *);
void charger_sdl_joueurs(perso_t *, SDL_Texture * textures_joueurs[][4]);
void detruire_joueurs_client(perso_t *, SDL_Texture * textures_joueurs[][4]);

void ramasser_objet(perso_t *, int ind_o);
void lacher_objet(perso_t *, int ind_inv);

//lit les infos du serv dans le buffer
void changer_tuile(perso_t *, char * buffer);

void changer_dir(perso_t *, char mask);

void afficher_tuile();
void charger_tuile(tuile_t * tuile);

#endif
