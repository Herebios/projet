#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define BOUTON_X 400
#define BOUTON_H 150
#define BOUTON_W 400
#define NB_BOUTONS 10

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *surface = NULL;
TTF_Font *police;

typedef struct {
    SDL_Rect posBoutonFen;
    SDL_Texture * texture;
    SDL_Texture * texte;

}bouton_t;

unsigned char nb_boutons = 0;
bouton_t tab_boutons[NB_BOUTONS];

SDL_Color couleurBlanche = { 255, 255, 255, 255 };
SDL_Color couleurNoire = { 0, 0, 0, 255 };


//temporaire
void end(int nb){
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    for(int i = 0 ; i < nb_boutons ; i++){
        SDL_DestroyTexture(tab_boutons[i].texture);
    }
	if (police)
		TTF_CloseFont(police);

	TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    if(nb) exit(nb);
}


void init_sdl(){
    if (SDL_Init(SDL_INIT_VIDEO) ||
		!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) ||
		TTF_Init()
	) end(1);

    window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1080, 1080, SDL_WINDOW_SHOWN);
    if (!window) end(2);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) end(3);
}


SDL_Texture * creer_texture(char * chemin){
	surface = IMG_Load(chemin);
	if(!surface) end(4);
    SDL_Texture * nouv_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(!nouv_texture) end(5);
	return nouv_texture;
}



void creer_bouton(bouton_t * bouton, char * nomFich, char * texte){
    bouton->texture = creer_texture(nomFich);
    if(!bouton->texture) end(5);

    surface = TTF_RenderUTF8_Blended(police, texte, couleurBlanche);
    //SDL_Blit pas mal à utiliser avec 
    //SDL_CreateRGBSurface
    SDL_Texture * textureTexte = SDL_CreateTextureFromSurface(renderer, surface);

    bouton->texte = textureTexte;
    nb_boutons++;
}

void afficher_boutons(){
    for(int i = 0 ; i < nb_boutons ; i++){
        SDL_RenderCopy(renderer, tab_boutons[i].texture, NULL, &tab_boutons[i].posBoutonFen);
        SDL_RenderCopy(renderer, tab_boutons[i].texte, NULL, &tab_boutons[i].posBoutonFen);
    }
}





char nomJeu[] = "nom temporaire";

int menu(){
    init_sdl();

    police = TTF_OpenFont("../include/Go-Regular.ttf", 100);
	if (!police) end(6);

    //créations des boutons avec structures
    tab_boutons[0] = (bouton_t) {(SDL_Rect){BOUTON_X, 400, BOUTON_W, BOUTON_H}, NULL, NULL};
    tab_boutons[1] = (bouton_t) {(SDL_Rect){BOUTON_X, 600, BOUTON_W, BOUTON_H}, NULL, NULL};
    tab_boutons[2] = (bouton_t) {(SDL_Rect){BOUTON_X, 800, BOUTON_W, BOUTON_H}, NULL, NULL};


    creer_bouton(tab_boutons, "../img/Boutons/boutonMenuLarge.png", "jouer"); //bouton jouer
    creer_bouton(tab_boutons + 1, "../img/Boutons/boutonMenuLarge.png", "paramètres"); //bouton paramètres
    creer_bouton(tab_boutons + 2, "../img/Boutons/boutonMenuLarge.png", "quitter"); //bouton quitter


	//arrière-plan
	SDL_Texture * backgroundTexture = creer_texture("../img/imgMenu.png");

	//nom du jeu
    SDL_Rect rectNomJeu = {300, 50, 400, 200};
    surface = TTF_RenderText_Solid(police, nomJeu, couleurBlanche);
    SDL_Texture * textureTexte = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(!textureTexte) end(7);

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    SDL_RenderCopy(renderer, textureTexte, NULL, &rectNomJeu);
    afficher_boutons();
    SDL_RenderPresent(renderer);

    SDL_Event event;


    int sortieMenu = 0;
	int xmouse, ymouse;
    while(!sortieMenu){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
				sortieMenu = 1;
				break;
			}

            //test clic bouton quitter
            
            if(event.type == SDL_MOUSEBUTTONDOWN){
                SDL_Point point = {event.button.x, event.button.y};
                if(SDL_PointInRect(&point, &tab_boutons[2].posBoutonFen)){
                    sortieMenu = 1;
                }
            }
            
        }

        SDL_Delay(100);
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(textureTexte);
    return 0;
}

int main(void){
    menu();
    end(0);
    return 0;
}
