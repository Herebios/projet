#ifndef _CLI_JEU_H_
#define _CLI_JEU_H_

#include "perso_cli.h"
#include "id_actions.h"

void init_joueurs_client(perso_cli_t *);
void detruire_joueurs_client(perso_cli_t *);

void ramasser_objet(perso_t *, int ind_o);
void lacher_objet(perso_t *, int ind_inv);

//lit les infos du serv dans le buffer
void changer_tuile(perso_t *, char * buffer);
#endif
