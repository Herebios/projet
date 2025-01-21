typedef enum {idle,course,attaque}t_anim;
typedef enum {bas,haut,gauche,droite,basgauche,basdroite,hautgauche,hautdroite}t_dir;
typedef enum {sortie, normal, obstacle} type_carre;
typedef enum {base, plaine, glace} nom_biome;//foret, volcan, marais, grotte, enfer, tour_magie, chateau_fort
typedef enum {consommable, arme, armure} cat_objet;

//?? pour les monstres
typedef enum {administrateur, guerrier, mage, archer, assassin, informaticien, druide, necromancien} t_classe;

typedef struct {
    int x;
    int y;
}t_pos;

typedef struct{
/*
anim est l'indice de la texture courante
max_anim sert à boucler sur l'animation (taille maximale de la texture)
dir et num_anim sont les indices pour le sprite (multipliés par la taille)
rect est l'emplacement sur l'écran, sprite le rectangle sur la texture
*/
	//bool monstre/joueur
    unsigned char num_anim, max_anim, nb_textures, vit, niveau;
	int vie, attaque, defense, magie, mana;
	t_classe classe;
	t_pos pos_map;//indices pour map.tuiles
    SDL_Rect sprite, rect;//rect = coo sur tuile
    t_anim anim;
    t_dir dir;
    SDL_Texture *textures[NB_ANIM], *texture_courante;//sprite
}t_perso;

typedef struct{
	int id;
	char nom[16];
	SDL_Texture *texture;
	SDL_Rect rect;
}t_objet;

typedef struct{
	int id;
	SDL_Rect rect;
	char nom[16];
	SDL_Texture *texture;
	int *quetes;//pas encore de struct
}t_pnj;

typedef struct{
/*enum type_carre comme indice dans textures
-->autant de types de textures dans chaque biome
*/
	nom_biome id_biome;
	SDL_Texture *textures[NB_TEXTURES_BIOME];
	unsigned char nb_textures;
//?? etat, relatif aux évènements, si chaque biome est unique sur la map, sinon dans tuile
}t_biome;

typedef struct{
//15x8 textures de 128x128 pour écran 1920x1080

	t_biome *biome;//pointeur sur un des biomes du tableau chargé un mémoire
	type_carre id_texture[HAUTEUR_TUILE][LARGEUR_TUILE];

	//tableau de pointeurs car les objets sont déjà en mémoire
	t_objet *objets[NB_OBJETS_TUILE];
	t_pnj *pnj[NB_PNJ_TUILE];
	t_perso *ennemis[NB_ENNEMIS_TUILE];
}t_tuile;

//?? map est peut-être inutile comme j'ai déplacé séparé les textures dans les biomes
typedef struct{
	t_tuile tuiles[HAUTEUR_MAP][LARGEUR_MAP];
//	SDL_Texture *textures[NB_TEXTURES]; unsigned char nb_textures;
}t_map;

typedef struct{
	//?? int seed;
	t_map map;
	t_perso perso[NB_PERS_MAX];//tableau, joueur en 0
	unsigned char nb_perso;
	t_tuile *tuile_courante;
	SDL_Texture *texture_tuile;
	//?? texture_prec + pos_prec
}t_jeu;

void end(int code);
//void init_objets(void);
void generer_tuile(t_tuile*, nom_biome);//id_texture
void charger_tuile_courante(void);
void init_jeu(void);
void init_map(void);
void init_biomes(void);
void nouv_surface(char* path);
void nouv_texture(SDL_Texture** textures, unsigned char* nb);//voir définition pour spéc.
void changer_anim(t_perso*, t_anim);
void nouv_perso(char* nom);//pour trouver ses textures
void avancer(t_perso*);
void changer_dir(t_perso*, Uint8 mask);
void setup(void);
void afficher_tuile_courante();
void effacer_joueur(t_perso*);
void afficher_perso(t_perso*);
void position_perso(t_perso*, t_pos*);
