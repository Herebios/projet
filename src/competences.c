#include "competences.h"
/* Pour le serveur
Tableau statique de toutes les compétences (5 par classe)
*/
//nom, description, comp_type, value, distance, rechargement (ms), fonction_calcul
comp_t tab_comp[NB_CLASSES][NB_COMP]={
	{//tank
{"Attaque 1", "Se base sur la force", instant, 1.2, 40, 2000, tank_attaque_force},
{"Attaque 2", "200\% de la force à très courte portée", instant, 2, 20, 5000, tank_attaque_force},
{"Skill", "", instant, 0, 0, 12000, NULL},
{"Mouvement", "Charge sans possibilité de changer de direction", projectile, 
	},
};
