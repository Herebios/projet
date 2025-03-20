/**
 * @file mob.c
 * @author Nathan
 * @brief fonction permettant le deplacement de monstres
 */

#include <stdio.h>
#include <math.h>

#include "perso.h"
#include "mob.h"

#define PI 3.1415

/**
 * @brief Retourne la distance entre le personnage et le monstre tous les deux passés en paramètres
 * @param Pointeur sur un personnage
 * @param Pointeur sur un monstre
 */
int distance_mob(perso_t *p, mob_t *mob) {
	int x = abs(p->pos_map.x - mob->pos_map.x);
	int y = abs(p->pos_map.y - mob->pos_map.y);
	return sqrt(x + y);
}

int joueur_plus_proche_mob(perso_t ** listePersos, mob_t *mob, int nbJoueurs) {
    int min = distance_mob(listePersos[0], mob);
    
    for (int i = 1; i < nbJoueurs; i++) {
        int dist = distance_mob(listePersos[i], mob);
        if (dist < min) {
            min = dist;
        }
    }
}

int angle_perso_mob(perso_t *p, mob_t *mob) {
    int normeX = abs(p->pos_map.x - mob->pos_map.x);
	int normeY = abs(p->pos_map.y - mob->pos_map.y);

    int xa = p->pos_map.x;
    int ya = p->pos_map.y;
    int xb = xa + 1; // Pour que le vecteur soit vers la droite
    int yb = ya;
    int xc = mob->pos_map.x;
    int yc = mob->pos_map.y;

    int Xab = xa + xb;
    int Yab = ya + yb;
    int Xac = xa + xc;
    int Yac = ya + yc;

    int scalaire = Xab * Xac + Yab * Yac;

    return acos(scalaire / (normeX * normeY));
}


int update_pos_mob(perso_t *p, mob_t *mob) {
    int angle =  angle_perso_mob(p, mob);

    //Haut
    if (angle >= PI / 4 && angle < (3 * PI) / 4){
        mob->pos_map.y += mob->stats[speed];
    }
    //Gauche
    else if (angle >= (3 * PI) / 4 && angle < (5 * PI) / 4){
        mob->pos_map.x -= mob->stats[speed];
    }
    //Bas
    else if (angle >= (5 * PI) / 4 && angle < (7 * PI) / 4){
        mob->pos_map.y -= mob->stats[speed];
    }
    //Droite
    else {
        mob->pos_map.x += mob->stats[speed];
    }
}

int main(void) {
    return 0;
}