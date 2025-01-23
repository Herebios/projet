#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "prepro.h"
#include "def.h"
#include "fonctions.h"

t_jeu jeu;//?? pourrait tout contenir, dupliquer les pointeurs à l'extérieur
t_map *map = &jeu.map;
t_perso *perso;//?? fonction pour perso = jeu.perso + jeu.nb_perso

t_biome biomes[NB_BIOMES];//?? inclus dans jeu ou map

//t_objet *objets[NB_CAT_OBJETS];

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *surface = NULL;

void end(int code) {
	unsigned char i,j;
	//objets
	/*for (i=0; i<NB_CAT_OBJETS; i++)
		if(objets[i]) free(objets[i]);
	}*/

	//textures perso
	for (i=0; i < jeu.nb_perso; i++){
		for (j=0; j < jeu.perso[i].nb_textures; j++)
			SDL_DestroyTexture(jeu.perso[i].textures[j]);
	}

	if (surface) SDL_FreeSurface(surface);

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

	//!setup
	IMG_Quit();
	SDL_Quit();
	if (code) exit(code);
	//fin de programme normale si 0
}
/*
//l'enum cat_objet donne les indices des tableaux d'objets dans total
void init_objets(){
	for (int i=0; i<NB_CAT_OBJETS; i++) objets[i]=NULL;

	t_objet *consommables=(t_objet*)malloc(sizeof(t_objet)*1),
		*armes=(t_objet*)malloc(sizeof(t_objet)*1),
		*armures=(t_objet*)malloc(sizeof(t_objet)*1),

	objets[0]=consommables;
	objets[1]=armes;
	objets[2]=armures;

	consommables[0]=(t_objet){0,"potion de soin"};
	armes[0]=(t_objet){100,"epee en diamant");
	armures[0]=(t_objet){200,"cote de mailles");
	//manque texture à charger et rect au moment où l'objet est affecté à une tuile
}
*/
void generer_tuile(t_tuile* tuile, nom_biome id_biome){//map
/*suppose que les biomes sont construits de la même manière avec
type_carre indice de texture dans biome->textures[]
*/
//!! il faudra adapter quand on aura tous les biomes et leurs textures

	tuile->biome = biomes + id_biome;//pointeur sur le biome de la tuile dans le tableau biomes
	int lig,col;
	for (lig=0; lig<NB_OBJETS_TUILE; lig++)
		tuile->objets[lig]=NULL;
	for (lig=0; lig<NB_PNJ_TUILE; lig++)
		tuile->pnj[lig]=NULL;
	for (lig=0; lig<NB_ENNEMIS_TUILE; lig++)
		tuile->ennemis[lig]=NULL;

	//textures aléatoires sur toute la zone
	//!! ajouter règles de génération, dépendantes du biome?
	for(lig=0; lig<HAUTEUR_TUILE; lig++)
		for(col=0; col<LARGEUR_TUILE; col++)
			tuile->id_texture[lig][col]=rand()%(NB_TEXTURES_BIOME-1) +1;//ne prend pas l'id 0, carre de sortie

	//sorties gauche et droite, indice 0
	for(col=0; col < LARGEUR_TUILE; col+=LARGEUR_TUILE-1){
		tuile->id_texture[HAUTEUR_TUILE/2 -1][col]=sortie;
		tuile->id_texture[HAUTEUR_TUILE/2][col]=sortie;
		if(HAUTEUR_TUILE%2)//3 carres de sortie si impair
			tuile->id_texture[HAUTEUR_TUILE/2 +1][col]=sortie;
	}
	//sorties haut et bas
	for(lig=0; lig < HAUTEUR_TUILE; lig+=HAUTEUR_TUILE-1){
		tuile->id_texture[lig][LARGEUR_TUILE/2 -1]=sortie;
		tuile->id_texture[lig][LARGEUR_TUILE/2]=sortie;
		if(LARGEUR_TUILE%2)
			tuile->id_texture[lig][LARGEUR_TUILE/2 +1]=sortie;
	}
}

/*void afficher_idtextures_tuile(t_tuile *t){
	for(int lig=0,col; lig<HAUTEUR_TUILE; lig++){
        for(col=0; col<LARGEUR_TUILE; col++)
			printf("%d ", t->id_texture[lig][col]);
		endl;
	}
}*/

t_tuile* ptr_tuile_courante(){//map
	perso = jeu.perso;//joueur
	return map->tuiles[perso->pos_map.y] + perso->pos_map.x;
}

void charger_tuile_courante(){//jeu
	t_tuile* tuile = jeu.tuile_courante;
	SDL_SetRenderTarget(renderer, jeu.texture_tuile);
	for (int l=0,c; l<HAUTEUR_TUILE; l++)
		for (c=0; c<LARGEUR_TUILE; c++)
			SDL_RenderCopy(renderer, tuile->biome->textures[tuile->id_texture[l][c]], 0, &(SDL_Rect){c*CARRE_W,l*CARRE_H,CARRE_W,CARRE_H});
	SDL_SetRenderTarget(renderer, NULL);
}

void init_jeu(){
	//init_objets();
	init_biomes();
	init_map();

	jeu.nb_perso=0;
	nouv_perso("orc3");
	//??Le joueur est créé ici, mais ce sera le serv qui donnera l'id de tel joueur
	//dans le tableau pour que tous soient pareils

	jeu.texture_tuile = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, W, H);//toute la fenêtre
	jeu.tuile_courante = ptr_tuile_courante();
}

void init_map(){//map
//!! Système pour placer les biomes
	//tuiles
	for (int l=0,c; l<HAUTEUR_MAP; l++)
		for (c=0; c<LARGEUR_MAP; c++)
			//adresse de la tuile, biome aléatoire
			generer_tuile(map->tuiles[l*LARGEUR_MAP] + c, (nom_biome) c+1);//actuellement plaine puis glace
}

void init_biomes(){
/*Tous les biomes doivent respecter le même format pour que les textures chargent bien
*/
	//init
	int i,j;
	for(i=0; i<NB_BIOMES; i++){
		biomes[i].id_biome=(nom_biome)i;
		biomes[i].nb_textures=0;
		for (j=0; j<NB_TEXTURES_BIOME; j++)
			biomes[i].textures[j]=NULL;
	}

	//charger textures selon les biomes
	t_biome *biome_cour;
	char *noms[]={"base","plaine","glace"}, path[100]="img/";

	for(i=0; i<NB_BIOMES; i++){//actuellement 3
		//!! base, id 0
		if(i){

		biome_cour=biomes+i;

		for(j=0; j<NB_TEXTURES_BIOME; j++){//actuellement 3
			strcat(path, noms[i]);
			switch(j){
				case 0:
					strcat(path, "_sortie.png");
					break;
				case 1:
					strcat(path, "_normal.png");
					break;
				case 2:
					strcat(path, "_obstacle.png");
					break;
			}
			nouv_surface(path);
			path[4]='\0';//écrire à nouveau après 'textures/'
			nouv_texture(biome_cour->textures, &biome_cour->nb_textures);
		}
		}
	}
}

void nouv_surface(char * image) {
/*Charge une nouvelle surface à partir du path reçu en param*/
    if (surface) SDL_FreeSurface(surface);
    if ((surface = IMG_Load(image)) == NULL){//SDL_LoadBMP(image)
		printf("%s introuvable\n", image);
		end(6);
	}
}
void nouv_texture(SDL_Texture** textures, unsigned char *nb_textures){
/*Les paramètres sont supposés corrects,
crée une texture avec la surface (globale) courante, dans textures[nb_textures]
termine le programme en cas d'échec, aucune vérification n'est nécessaire après l'appel
*/
	if ((textures[*nb_textures] = SDL_CreateTextureFromSurface(renderer, surface)) == NULL)
		end(5);
	(*nb_textures)++;
}

void changer_anim(t_perso *p, t_anim anim){
	p->anim=anim;
	//texture qui correspond à l'anim
	p->texture_courante=p->textures[anim];

	//nb d'étapes de l'anim
	p->num_anim=1;
	switch(anim){
		case idle:
			p->max_anim=4;break;
		case course:
		case attaque:
			p->max_anim=8;break;
	}

	//ligne de lecture de l'anim sur la texture en fonction de la dir
	int y;
	switch(p->dir){
		case basgauche:
		case bas:
			y=0;break;
		case hautdroite:
		case haut:
			y=jh;break;
		case hautgauche:
		case gauche:
			y=jh*2;break;
		case basdroite:
		case droite:
			y=jh*3;break;
	}
	p->sprite.x=0;
	p->sprite.y=y;
}

void nouv_perso(char *s){//jeu, perso
//?? parametre classe
	if (jeu.nb_perso==NB_PERS_MAX) end(7);
	perso = jeu.perso + jeu.nb_perso;//pointeur sur nouv perso
	//valeurs par defaut
	t_classe classe=administrateur;
	*perso = (t_perso){0,0,0,VITESSE_BASE,NIVEAU_BASE,VIE_BASE,ATTAQUE_BASE,DEFENSE_BASE,MAGIE_BASE,MANA_BASE,classe};
	perso->pos_map = (t_pos){0,0};//position : map.tuiles[y][x]
	perso->sprite = (SDL_Rect){0, 0, jw, jh};
	perso->rect = (SDL_Rect){xdep, ydep, jw, jh};//position sur tuile

	//!!au lieu de char *s, on utilisera l'attribut classe du joueur
	//charger textures perso
	char chemin[50];
	strcpy(chemin, "img/");
	strcat(chemin, s);
	int fin=strlen(chemin);

	strcpy(chemin+fin, "_idle.png");
	nouv_surface(chemin);
	nouv_texture(perso->textures, &perso->nb_textures);
	strcpy(chemin+fin, "_run.png");
	nouv_surface(chemin);
	nouv_texture(perso->textures, &perso->nb_textures);
	strcpy(chemin+fin, "_attack.png");
	nouv_surface(chemin);
	nouv_texture(perso->textures, &perso->nb_textures);

	//sprite et anim de base
	perso->dir=droite;
	changer_anim(perso,idle);
	jeu.nb_perso++;
}
t_pos deplacement[] = {
    {0,1}, // BAS
    {0,-1}, // HAUT
    {-1,0}, // GAUCHE
    {1,0}, // DROITE
    {-1,1}, // BAS_GAUCHE
    {1,1}, // BAS_DROITE
    {-1,-1}, // HAUT_GAUCHE
    {1,-1}  // HAUT_DROITE
};

bool inclus(SDL_Rect* a, SDL_Rect* b){
    return (a->x >= b->x) && (a->y >= b->y) && ((a->x + a->w) <= (b->x + b->w)) && ((a->y + a->h) <= (b->y + b->h));
}

void avancer(t_perso *p){//uniquement pour le joueur
//!!gérer collisions avec obstacles
//?? carrés de sortie même pour les tuiles sur un bord de map ?
//-si non, modifier un peu cette fonction, et adapter génération des tuiles
//?? si sauvegarde précédente tuile dans struct jeu, il faudra ajouter un peu de code

	if(!p)return;
	SDL_Rect rect_tuile={0,0,W,H};
	SDL_Rect rect = p->rect;//séparé
	int deltax=deplacement[p->dir].x * p->vit, deltay=deplacement[p->dir].y * p->vit;
	bool sortie=0;
	t_pos pos;

	/*Ne pas dépasser les bords.
	2 tests pour ne pas être bloqué si 2 touches sont appuyées et une des directions est un bord*/

	rect.x+=deltax;
	if(inclus(&rect, &rect_tuile))
		p->rect.x=rect.x;
	else{//bord tuile dépassé
		position_perso(p, &pos);
		printf("%d %d\n", pos.x, pos.y);flush;
		//tuile de sortie?
		if(jeu.tuile_courante->id_texture[pos.y][pos.x]==0){
			if(pos.x==0 && p->pos_map.x!=0){//sortie gauche tuile et tuile pas bord gauche map
				p->pos_map.x--;
				p->rect.x = W - p->rect.w;//se retrouve côté droit
				sortie=1;
			}else if(pos.x==LARGEUR_TUILE-1/*pas besoin de verif normalement*/ && p->pos_map.x!=LARGEUR_MAP-1){
				p->pos_map.x++;
				p->rect.x = 0;//se retrouve côté gauche
				sortie=1;
			}
		}
		else//correction pour le test de hauteur
			rect.x=p->rect.x;
	}

	rect.y+=deltay;
	if(inclus(&rect, &rect_tuile))
		p->rect.y=rect.y;
	else{
		position_perso(p, &pos);

		if(jeu.tuile_courante->id_texture[pos.y][pos.x]==0){
			if(pos.y==0 && p->pos_map.y!=0){//sortie haut tuile et tuile pas bord haut map
				p->pos_map.y--;
				p->rect.y = H - p->rect.h;//se retrouve en bas
				sortie=1;
			}else if(pos.y==HAUTEUR_TUILE-1/*pas besoin de verif normalement*/ && p->pos_map.y!=HAUTEUR_MAP-1){
				p->pos_map.y++;
				p->rect.y = 0;//se retrouve en haut
				sortie=1;
			}
		}
	}
	if(sortie){
		jeu.tuile_courante=ptr_tuile_courante();
		charger_tuile_courante();
		afficher_tuile_courante();
		afficher_perso(p);
	}
	/*Anciens tests des bords
	if ((rect->x += deltax) + rect->w > W)
		rect->x -= deltax;
	else if(rect->x < 0)
		rect->x -= deltax;

	if ((rect->y += deltay) + rect->h > H)
		rect->y -= deltay;
	else if(rect->y < 0)
		rect->y -= deltay;
	*/
}



void changer_dir(t_perso *p, Uint8 mask){
	switch(mask){
		//basdroite
		case 10:
		    p->dir=basdroite;
			break;
		//hautdroite
		case 9:
		    p->dir=hautdroite;
			break;
		//basgauche
		case 6:
		    p->dir=basgauche;
			break;
		//hautgauche
		case 5:
		    p->dir=hautgauche;
			break;
		//droite
		case 11:
		case 8:
		    p->dir=droite;
			break;
		//gauche
		case 7:
		case 4:
		    p->dir=gauche;
			break;
		//bas
		case 14:
		case 2:
		    p->dir=bas;
			break;
		//haut
		case 13:
		case 1:
		    p->dir=haut;
	}
}

void init_sdl(){
	if (SDL_Init(SDL_INIT_VIDEO) || !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) end(1);
    window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
    if (!window) end(2);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) end(3);
}

void afficher_tuile_courante(){
	SDL_RenderCopy(renderer, jeu.texture_tuile, 0, 0);
}

void effacer_perso(t_perso *p){
	SDL_RenderCopy(renderer, jeu.texture_tuile, &p->rect, &p->rect);//ce qu'il y avait dessous, redessiné dessus
}

void afficher_perso(t_perso *p){
	SDL_RenderCopy(renderer, p->texture_courante, &p->sprite, &p->rect);
}

void position_perso(t_perso *p, t_pos* pos){
	int y=p->rect.y + (p->rect.h >> 1);//ajout de hauteur/2, ~milieu du perso
	pos->y = y/CARRE_H;
	int x=p->rect.x + (p->rect.w >> 1);
	pos->x = x/CARRE_W;
}

//taille texture : SDL_QueryTexture(textures[0], NULL, NULL, &largeur_texture, &hauteur_texture);
int main(int argc, char *argv[]) {
	/*window, renderer, jeu(map(textures, tuiles), texture_tuile, perso)*/
	init_sdl();
	init_jeu();

	charger_tuile_courante();
	afficher_tuile_courante();

	t_perso *j=jeu.perso;//perso 0 = joueur
	afficher_perso(j);

//	t_tuile *tuiles = map->tuiles;//& map->tuiles[0][0]


    SDL_RenderPresent(renderer);
    SDL_Event event;
	const Uint8* clavier;
	Uint8 running=1, refresh_anim=2;
    while(running){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.sym==SDLK_m){
				running=0;break;
			}
		}

		clavier=SDL_GetKeyboardState(NULL);
		Uint8 mask=clavier[SDL_SCANCODE_RIGHT] << 3 | clavier[SDL_SCANCODE_LEFT] << 2 | clavier[SDL_SCANCODE_DOWN] << 1 | clavier[SDL_SCANCODE_UP];

		effacer_perso(j);

		//sauvegarde de dir et anim
		t_dir dir=j->dir;
		//on change la direction en fonction des input
		changer_dir(j, mask);
		switch(j->anim){
			case idle:
				if(mask){
					avancer(j);
					changer_anim(j,course);
				}
				break;
			case course:
				if(mask){
					avancer(j);
					if(dir!=j->dir)
						//on ne réinitialise pas l'animation comme on est déjà en course
						changer_anim(j,course);
				}else
					changer_anim(j,idle);
				break;
		}

		//gère anim, delai avec refresh pour ralentir la vitesse
		if(refresh_anim)
			refresh_anim--;
		else{
			if(j->num_anim < j->max_anim){
				//on avance dans l'animation
				j->sprite.x+=jw;
				j->num_anim++;
			}else{
				//on recommence l'animation
				j->sprite.x=0;
				j->num_anim=1;
			}
			refresh_anim=2;
		}

		//fin boucle
		afficher_perso(j);
			//SDL_RenderCopyEx(renderer, , &j->sprite, &j->rect, angle, centre:0, SDL_FLIP_HORIZONTAL);
		SDL_RenderPresent(renderer);
        SDL_Delay(60);
    }

	end(0);
    return 0;
}
