/**
 * @file serv_jeu.h
 * @author Baptiste
 */
#include "serv_commun.h"
#include "jeu.h"
#include "types.h"
#include "def.h"
#include "objet.h"
#include "perso.h"
#include "id_actions.h"

//objets
void spawn_objet(rarete_t, int mode, int ind_o, pos_t p_map, pos_t p_tuile);

//joueurs
void maj_tuile(perso_t * joueurs, int ind_j);
int check_sortie_tuile(perso_t * joueurs, int ind_j);

void init_joueurs_server(perso_t *, int);
void detruire_joueurs_server(perso_t *, int);
void send_joueurs_server(perso_t *, int);

