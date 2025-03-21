/**
 * @file serv_jeu.h
 * @author Baptiste
 */
#include "serv_commun.h"
#include "def.h"
#include "id_actions.h"

//objets
void spawn_objet(rarete_t);

//joueurs
void maj_tuile(perso_t * joueurs, int ind, pos_t pos_map);
void init_joueurs_server(perso_t *);
void detruire_joueurs_server(perso_t *);
void send_joueurs_server(info_server *, socket_struct *, perso_t *);
tuile_t * get_tuile_from_perso(perso_t *);
