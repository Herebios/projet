#ifndef _CLI_JEU_H_
#define _CLI_JEU_H_

#include "cli_commun.h"
#include "jeu.h"
#include "id_actions.h"
#include "perso.h"
#include "inventaire.h"

#define ecran() SDL_RenderPresent(renderer)

typedef enum{
    UN, DEUX, TROIS, QUATRE, CINQ, NUL
}supp_t;

extern SDL_Texture * texture_tuile;

void init_joueurs_client(perso_t *);
void charger_sdl_objets(SDL_Texture * textures_objets[NB_OBJETS]);
void charger_sdl_joueurs(perso_t *, SDL_Texture * textures_joueurs[][4]);

void detruire_objets_client(SDL_Texture * textures_objets[NB_OBJETS]);
void detruire_joueurs_client(perso_t *, SDL_Texture * textures_joueurs[][4]);

void ramasser_objet(perso_t *, int ind_o);
void lacher_objet(perso_t *, int ind_inv);

//lit les infos du serv dans le buffer
void changer_tuile(perso_t *, char * buffer);

void changer_dir(perso_t *, char mask);

void afficher_tuile();
void charger_tuile(tuile_t * tuile);

void attaqueBasique(perso_t *p, dir_t dir);

#endif