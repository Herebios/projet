/**
 * @file jeu.h
 * @author Baptiste
 * @brief fonctions pour le jeu communes serv/cli
 */

#include "jeu.h"

tuile_t map[HAUTEUR_MAP][LARGEUR_MAP];
biome_t biomes[NB_BIOMES];
SDL_Window *window=NULL;
SDL_Renderer *renderer=NULL;

pos_t deplacement[8] = {
    {0,1}, // BAS
    {0,-1}, // HAUT
    {-1,0}, // GAUCHE
    {1,0}, // DROITE
    {-1,1}, // BAS_GAUCHE
    {1,1}, // BAS_DROITE
    {-1,-1}, // HAUT_GAUCHE
    {1,-1}  // HAUT_DROITE
};

void detruire_tuile(tuile_t *t){
	detruire_liste(&t->liste_joueurs);
	detruire_liste(&t->liste_objets);
	detruire_liste(&t->liste_mobs);
}

void end(int code){
    unsigned char i,j;

    //textures map
    for(i=0; i<NB_BIOMES; i++)
        for(j=0; j<NB_TEXTURES_BIOME; j++)
            if(biomes[i].textures[j])
                SDL_DestroyTexture(biomes[i].textures[j]);

	for(i=0; i<HAUTEUR_MAP; i++)
		for(j=0; j<LARGEUR_MAP; j++)
			detruire_tuile(map[i] + j);

    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
    if (code) exit(code);
    //fin de programme normale si 0
}

void init_sdl(){
	if (SDL_Init(SDL_INIT_VIDEO) || !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) end(1);
	window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
	if (!window) end(2);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) end(3);
}

void init_jeu(){
	init_biomes();
	init_map();

	for(int i=0; i<NB_OBJETS; i++)
		tab_objets[i].ind=i;
}

void init_biomes(){
	//init
	int i,j;
	for(i=0; i<NB_BIOMES; i++){
		biomes[i].id_biome=i;
		for (j=0; j<NB_TEXTURES_BIOME; j++)
			biomes[i].textures[j]=NULL;
			biomes[i].nb_textures=0;
	}

	//charger textures
	biome_t *biome;
	char *noms[]={"base", "desert", "foret", "glace", "montagne", "neige", "plaine"};
	char path[100]="../img/Tiles/Biomes/";
	for(i=0; i<NB_BIOMES; i++){
	    //!! base, id 0
	    if(i){

	    biome=biomes+i;
	    for(j=0; j<NB_TEXTURES_BIOME; j++){
	        strcat(path, noms[i]);
	        switch(j){
				//type_carre
	            case 0:
	                strcat(path, "/sortie.png");
	                break;
	            case 1:
	                strcat(path, "/normal.png");
	                break;
	            case 2:
	                strcat(path, "/obstacle1.png");
	                break;
	            case 3:
	                strcat(path, "/obstacle2.png");
	                break;
	        }
			nouv_texture(path, biome->textures, &biome->nb_textures);
			path[20]='\0';//"../img/Tiles/Biomes/"
	    }
	    }
	}
}

/*Initialise toutes les tuiles avec un biome aléatoire*/
void init_map(){
//!! Système pour placer les biomes
	for (int l=0,c; l<HAUTEUR_MAP; l++)
		for (c=0; c<LARGEUR_MAP; c++)
			init_tuile(map[l] + c, rand() % (NB_BIOMES - 1) + 1, l, c);
}

void init_tuile(tuile_t *tuile, nom_biome_t id_biome, int ymap, int xmap){//map
/*suppose que les biomes sont construits de la même manière avec
type_carre indice de texture dans biome->textures[]
*/
    tuile->biome = biomes + id_biome;
	tuile->liste_joueurs = creer_liste();
	tuile->liste_objets = creer_liste();
	tuile->liste_mobs = creer_liste();

    int lig,col;
    //textures aléatoires sur toute la zone
    //!! ajouter règles de génération, dépendantes du biome?
    for(lig=0; lig<HAUTEUR_TUILE; lig++)
        for(col=0; col<LARGEUR_TUILE; col++) {
            if(rand()%6)// 5/6
                tuile->id_texture[lig][col]=normal;
            else if (rand() % 2)
                tuile->id_texture[lig][col]=obstacle1;
            else
                tuile->id_texture[lig][col]=obstacle2;
        }

    /*On ajoute une 3e sortie si taille impaire
    Test position map : pas de sortie aux bords*/
    //gauche
    if (xmap) {
        tuile->id_texture[HAUTEUR_TUILE/2 -1][0]=sortie;
        tuile->id_texture[HAUTEUR_TUILE/2][0]=sortie;
        if(HAUTEUR_TUILE%2)
            tuile->id_texture[HAUTEUR_TUILE/2 +1][0]=sortie;
    }
    //droite
    if (xmap != LARGEUR_MAP - 1) {
        tuile->id_texture[HAUTEUR_TUILE/2 -1][LARGEUR_TUILE-1]=sortie;
        tuile->id_texture[HAUTEUR_TUILE/2][LARGEUR_TUILE-1]=sortie;
        if(HAUTEUR_TUILE%2)//3 carres de sortie si impair
            tuile->id_texture[HAUTEUR_TUILE/2 +1][LARGEUR_TUILE-1]=sortie;
    }

    //haut
    if (ymap) {
        tuile->id_texture[0][LARGEUR_TUILE/2 -1]=sortie;
        tuile->id_texture[0][LARGEUR_TUILE/2]=sortie;
        if(LARGEUR_TUILE%2)
            tuile->id_texture[0][LARGEUR_TUILE/2 +1]=sortie;
    }
    //bas
    if (ymap != HAUTEUR_MAP - 1) {
        tuile->id_texture[HAUTEUR_TUILE-1][LARGEUR_TUILE/2 -1]=sortie;
        tuile->id_texture[HAUTEUR_TUILE-1][LARGEUR_TUILE/2]=sortie;
        if(LARGEUR_TUILE%2)
            tuile->id_texture[HAUTEUR_TUILE-1][LARGEUR_TUILE/2 +1]=sortie;
    }
}

void ajouter_objet_tuile(tuile_t * t, int ind_o, pos_t pos_tuile){
	//!!verifier
	ajout_fin_liste(t->liste_objets, &(objet_tuile_t){tab_objets + ind_o, (pos_t){pos_tuile.x, pos_tuile.y}}, sizeof(objet_tuile_t));
}

//!! bug possible si 2 objets identiques sur la même tuile
void retirer_objet_tuile(tuile_t * t, int ind_o){
	objet_tuile_t *obj;
	for(tete_liste(t->liste_objets); !hors_liste(t->liste_objets); suivant_liste(t->liste_objets)){
		obj=get_liste(t->liste_objets);
		if(obj->objet->ind == ind_o){
			supprimer_liste(t->liste_objets);
			return;
		}
	}
}

/*Une texture est créée à partir du path
Aucun traitement supplémentaire n'est nécessaire (modification par pointeur)*/
void nouv_texture(char * path, SDL_Texture *textures[], unsigned char *nb_textures){
    SDL_Surface *surface = IMG_Load(path);
    if(textures[*nb_textures] = SDL_CreateTextureFromSurface(renderer, surface))
        (*nb_textures)++;
    SDL_FreeSurface(surface);
}

SDL_Texture * get_nouv_texture(char * path){
    SDL_Surface *surface = IMG_Load(path);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
	return tex;
}
int inclus(SDL_Rect* a, SDL_Rect* b){
    return (a->x >= b->x) && (a->y >= b->y) && ((a->x + a->w) <= (b->x + b->w)) && ((a->y + a->h) <= (b->y + b->h));
}

//mouvement d'un perso à chaque boucle de jeu
//!!gérer collisions avec obstacles
void avancer(perso_t *p){
	if(p->dir == nulldir) return;

    SDL_Rect rect_tuile={0,0,W,H};
    SDL_Rect rect = p->rect;
    int deltax=deplacement[p->dir].x * p->stats[speed];
    int deltay=deplacement[p->dir].y * p->stats[speed];

    /*Ne pas dépasser les bords. Tests x et y séparés pour ne pas être bloqué
    si 2 touches sont appuyées et une des directions est un bord*/

    rect.x+=deltax;
    //test de la nouvelle position
    if(inclus(&rect, &rect_tuile))
        p->rect.x=rect.x;
        //correct = application
    else
        rect.x=p->rect.x;
        //sinon correction pour le test de hauteur

    rect.y+=deltay;
    if(inclus(&rect, &rect_tuile))
        p->rect.y=rect.y;

}

tuile_t * get_tuile_from_pos(pos_t pos){
	return map[pos.y] + pos.x;
}

pos_t get_pos_from_coo(int x, int y){
	return (pos_t){x, y};
}

tuile_t *get_tuile_joueur(perso_t * p){
    return map[p->pos_map.y] + p->pos_map.x;
}

//pos_tuile
void position_perso(perso_t *p, pos_t* pos){
	//~milieu du perso
	pos->x = (p->rect.x + (p->rect.w >> 1)) / CARRE_W;
	pos->y = (p->rect.y + (p->rect.h >> 1)) / CARRE_H;
}
