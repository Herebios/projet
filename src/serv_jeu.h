/**
 * @file serv_jeu.h
 * @author Baptiste
 */
#include "serv_commun.h"
#include "def.h"
#include "id_actions.h"
//map
extern map_t * map;
void serv_init_map();

//objets
void spawn_objet(rarete_t);

//joueurs
void init_joueurs_server(perso_t *);
void detruire_joueurs_server(perso_t *);
void send_joueurs_server(info_server *, socket_struct *, perso_t *);
