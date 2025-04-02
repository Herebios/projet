#ifndef _PREPRO_H_
#define _PREPRO_H_

/*Ratio important
W = CARRE_W * LARGEUR_TUILE
H = CARRE_H * HAUTEUR_TUILE
*/
#define W 800
#define H 600
#define CARRE_W 50
#define CARRE_H 50

#define NB_ANIM 3//nb de textures pour un perso
#define NB_PERS_MAX 1
#define VITESSE_BASE 8
#define NIVEAU_BASE 1
#define VIE_BASE 0
#define ATTAQUE_BASE 0
#define DEFENSE_BASE 0
#define MAGIE_BASE 0
#define MANA_BASE 0

#define NB_CAT_OBJETS 3

#define LARGEUR_TUILE 16
#define HAUTEUR_TUILE 12

#define NB_OBJETS_TUILE 1
#define NB_PNJ_TUILE 1
#define NB_ENNEMIS_TUILE 1

#define HAUTEUR_MAP 2
#define LARGEUR_MAP 2

//différencier perso et biome dans nouv_texture
#define TEXTURE_BIOME 0
#define TEXTURE_PERSO 1

#define jw 50
#define jh 50
#define xdep 100
#define ydep 100

#define endl putchar('\n')
#define flush fflush(stdout)

#define DELAY 20

#endif
