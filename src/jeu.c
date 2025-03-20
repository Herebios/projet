/**
 * @file jeu.h
 * @author Baptiste
 * @brief fonctions pour le jeu communes serv/cli
 */

#include "jeu.h"

jeu_t jeu;
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

void end(int code){
    unsigned char i,j;

    //textures map
    for(i=0; i<NB_BIOMES; i++)
        for(j=0; j<NB_TEXTURES_BIOME; j++)
            if(biomes[i].textures[j])
                SDL_DestroyTexture(biomes[i].textures[j]);

    //jeu
    if (jeu.texture_tuile)
        SDL_DestroyTexture(jeu.texture_tuile);
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

	jeu.nb_perso=0;
	nouv_perso("orc3");

	jeu.texture_tuile = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, W, H);//toute la fenêtre
	jeu.tuile_courante = ptr_tuile_courante();
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
	char path[100]="img/Tiles/Biomes/";
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
			path[17]='\0';//"img/Tiles/Biomes/"
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
    int lig,col;
    for (lig=0; lig<NB_OBJETS_TUILE; lig++)
        tuile->objets[lig].objet=NULL;
    for (lig=0; lig<NB_PNJ_TUILE; lig++)
        tuile->pnj[lig]=NULL;
    for (lig=0; lig<NB_ENNEMIS_TUILE; lig++)
        tuile->ennemis[lig]=NULL;

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

/*Une texture est créée à partir du path
Aucun traitement supplémentaire n'est nécessaire (modification par pointeur)*/
void nouv_texture(char * path, SDL_Texture *textures[], unsigned char *nb_textures){
    SDL_Surface *surface = IMG_Load(path);
    if(textures[*nb_textures] = SDL_CreateTextureFromSurface(renderer, surface))
        *nb_textures++;
    SDL_FreeSurface(surface);
}

bool inclus(SDL_Rect* a, SDL_Rect* b){
    return (a->x >= b->x) && (a->y >= b->y) && ((a->x + a->w) <= (b->x + b->w)) && ((a->y + a->h) <= (b->y + b->h));
}
