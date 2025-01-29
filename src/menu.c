#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>


#define BOUTON_X 400
#define BOUTON_LARG 125
#define BOUTON_LONG 400
#define NB_BOUTONS 10

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *surface = NULL;

TTF_Font * police;


typedef struct {
    SDL_Rect posBoutonFen;
    SDL_Texture * texture;
}bouton_t;

unsigned char nb_boutons_charge = 0;

bouton_t tab[NB_BOUTONS];

SDL_Color couleurBlanche = { 255, 255, 255, 255 };
SDL_Color couleurNoire = { 0, 0, 0, 255 };






//temporaire
void end(int nb){
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    for(int i = 0 ; i < nb_boutons_charge ; i++){
        SDL_DestroyTexture(tab[i].texture);
    }
    

    IMG_Quit();
    SDL_Quit();
    exit(nb);
}


void init_sdl(){
    if (SDL_Init(SDL_INIT_VIDEO) || !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) end(1);
    window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1080, 1080, SDL_WINDOW_SHOWN);
    if (!window) end(2);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) end(3);
}



void cree_bouton(bouton_t * bouton, char * nomFich){
    surface = IMG_Load(nomFich);
    if(!surface) end(4);

    bouton->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!bouton->texture) end(5);
   
    SDL_FreeSurface(surface);
    nb_boutons_charge++;
    
}

void affiche_boutons(){
    for(int i = 0 ; i < nb_boutons_charge ; i++){
        int t = SDL_RenderCopy(renderer, tab[i].texture, NULL, &tab[i].posBoutonFen);
    }
}


char * nomJeu = "nom temporaire";

int menu(){
    init_sdl();
    TTF_Init();
    
    police = TTF_OpenFont("../include/Go-Regular.ttf", 45);
    int sortieMenu = 0;

    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    
    //créations des boutons avec structures
    
    tab[0] = (bouton_t) {(SDL_Rect){BOUTON_X, 400, BOUTON_LONG, BOUTON_LARG}, NULL};
    tab[1] = (bouton_t){(SDL_Rect){BOUTON_X, 800, BOUTON_LONG, BOUTON_LARG}, NULL};
    
    cree_bouton(tab, "../img/Boutons/boutonMenuLarge.png");   
    cree_bouton(tab + 1, "../img/Boutons/boutonMenuLarge.png");   


    surface = IMG_Load("../img/imgMenu.jpg");
    
    SDL_Texture * backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!backgroundTexture) end(6);
    SDL_FreeSurface(surface);


    surface = TTF_RenderText_Solid(police, nomJeu, couleurBlanche);

    SDL_Texture * textureTexte = SDL_CreateTextureFromSurface(renderer, surface);
    if(!textureTexte) end(7);
    SDL_FreeSurface(surface);


    SDL_Rect rectNomJeu = {300, 50, 400, 200};

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    SDL_RenderCopy(renderer, textureTexte, NULL, &rectNomJeu);
         
 

    affiche_boutons();


    SDL_RenderPresent(renderer);


    SDL_Event event;

    while(!sortieMenu){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) sortieMenu = 1;
            if(event.key.keysym.sym == SDLK_ESCAPE) sortieMenu = 1;
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