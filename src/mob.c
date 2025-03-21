/**
 * @file mob.c
 * @author Nathan
 * @brief fonction permettant le deplacement de monstres
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "perso.h"
#include "mob.h"

#define PI 3.141592653589793



pos_t * calculMilieuMob(mob_t * mob) {
    pos_t * pos = malloc(sizeof(pos_t));
    pos->x = mob->pos_map.x - (mob->pos_map.w / 2);
    pos->y = mob->pos_map.y - (mob->pos_map.h / 2);
    return pos;
}



pos_t * calculMilieuPerso(perso_t * p) {
    pos_t * pos = malloc(sizeof(pos_t));
    pos->x = p->rect.x - (p->rect.w / 2);
    pos->y = p->rect.y - (p->rect.h / 2);
    return pos;
}



double distance_mob(perso_t *p, mob_t *mob) {
	int x = p->pos_map.x - mob->pos_map.x;
	int y = p->pos_map.y - mob->pos_map.y;
	return sqrt(x*x + y*y);
}



perso_t * joueur_plus_proche_mob(perso_t ** listePersos, mob_t *mob, int nbJoueurs) {
    int min = distance_mob(listePersos[0], mob);
    int ind = 0;
        
    for (int i = 1; i < nbJoueurs; i++) {
        int dist = distance_mob(listePersos[i], mob);
        if (dist < min) {
            min = dist;
            ind = i;
        }
    }

    return listePersos[ind];
}


double angle_perso_mob(perso_t *p, mob_t *mob) {
    int xa = p->pos_map.x;
    int ya = p->pos_map.y;
    
    int xb = xa + 1; // Pour que le vecteur soit vers la droite
    int yb = ya;
    int xc = mob->pos_map.x;
    int yc = mob->pos_map.y;
    
    int Xab = xb - xa;
    int Yab = yb - ya;
    int Xac = xc - xa;
    int Yac = yc - ya;
    
    int normeAB = sqrt(Xab * Xab + Yab * Yab);
	int normeAC = sqrt(Xac * Xac + Yac * Yac);

    double scalaire = Xab * Xac + Yab * Yac;

    return acos((double)(scalaire / (double)(normeAB * normeAC)));
}


void update_pos_mob(perso_t *p, mob_t *mob) {
    int angle =  angle_perso_mob(p, mob);

    //Haut
    if (angle >= PI / 4 && angle < (3 * PI) / 4){
        mob->pos_map.y -= mob->stats[speed];
    }
    //Gauche
    else if (angle >= (3 * PI) / 4 && angle < (5 * PI) / 4){
        mob->pos_map.x += mob->stats[speed];
    }
    //Bas
    else if (angle >= (5 * PI) / 4 && angle < (7 * PI) / 4){
        mob->pos_map.y += mob->stats[speed];
    }
    //Droite
    else {
        mob->pos_map.x -= mob->stats[speed];
    }
}

