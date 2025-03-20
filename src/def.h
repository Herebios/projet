#include "types.h"
#include "perso.h"
#include "SDL_def.h"

typedef enum {idle,course,attaque}anim_t;
typedef enum {bas,haut,gauche,droite,basgauche,basdroite,hautgauche,hautdroite}dir_t;
typedef enum {sortie, normal, obstacle1, obstacle2} type_carre;
typedef enum {base, desert, foret, glace, montagne, neige, plaine} nom_biome_t;//foret, volcan, marais, grotte, enfer, tour_magie, chateau_fort


typedef struct{
//anim est l'indice de la texture courante
//max_anim sert à boucler sur l'animation (taille maximale de la texture)
//dir et num_anim sont les indices pour le sprite (multipliés par la taille)
//rect est l'emplacement sur l'écran, sprite le rectangle sur la texture

	//bool monstre/joueur
    unsigned char num_anim, max_anim, nb_textures, vit, niveau;
	int vie, attaque, magie;
	//int mana; Pas implémenté pour le moment
	classe_t classe;
	pos_t pos_map;//indices pour map.tuiles
    SDL_Rect sprite, rect;//rect = coo sur tuile
    anim_t anim;
    dir_t dir;
    SDL_Texture *textures[NB_ANIM], *texture_courante;//sprite
}perso_t;


typedef struct{
	objet_t * objet;
	pos_t pos;
}objet_tuile_t;

typedef struct{
	int id;
	SDL_Rect rect;
	char nom[16];
	SDL_Texture *texture;
	int *quetes;//pas encore de struct
}pnj_t;

typedef struct{
	nom_biome_t id_biome;
	SDL_Texture *textures[NB_TEXTURES_BIOME];//type_carre indice
	unsigned char nb_textures;
}biome_t;

typedef struct{
//15x8 textures de 128x128 pour écran 1920x1080

	biome_t *biome;//pointeur sur un des biomes du tableau chargé un mémoire
	type_carre id_texture[HAUTEUR_TUILE][LARGEUR_TUILE];

	//!! initialiser les pointeurs à NULL
	objet_tuile_t objets[NB_OBJETS_TUILE];
	//quand un objet est initialisé on copie le ptr et on initialise la pos
	pnj_t *pnj[NB_PNJ_TUILE];
	perso_t *ennemis[NB_ENNEMIS_TUILE];
}tuile_t;

typedef struct{
	//?? int seed;
	tuile_t *tuile_courante;
	SDL_Texture *texture_tuile;
	//?? texture_prec + pos_prec
}jeu_t;
