#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

SDL_Rect posBouton = {274, 170, 302, 300};



void cree_bouton(SDL_Renderer * renderer, SDL_Rect rect, TTF_Font * police, SDL_Colour couleur, char * nomBouton){
    SDL_Surface * texteBouton = TTF_RenderText_Solid(police, nomBouton, couleur);
    SDL_Texture * textureTexte = SDL_CreateTextureFromSurface(renderer, texteBouton);
    //SDL_RenderDrawRect(renderer, &rect);
    SDL_Surface *surfaceBouton = IMG_Load("../img/boutonMenu.png");
    SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, surfaceBouton);
    
    SDL_RenderCopy(renderer, imageTexture, &posBouton, &rect);
    SDL_RenderCopy(renderer, textureTexte, NULL, &rect);
}


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *surface = NULL;

char * nomJeu = "nom temporaire";

int menu(){
    int sortieMenu = 0;

    window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1800, 1080, SDL_WINDOW_SHOWN);


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    surface = IMG_Load("../img/imgMenu.jpg");

    SDL_Texture * backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    TTF_Init();

    TTF_Font * police = TTF_OpenFont("../include/Go-Regular.ttf", 45);
    

    SDL_Color couleurBlanche = { 255, 255, 255, 255 };
    SDL_Color couleurNoire = { 0, 0, 0, 255 };


    SDL_Surface *surfaceTexte = TTF_RenderText_Solid(police, nomJeu, couleurBlanche);
    SDL_Texture * textureTexte = SDL_CreateTextureFromSurface(renderer, surfaceTexte);
    SDL_Event event;

    SDL_Rect zoneTexte = {300, 50, 400, 200};

    SDL_Rect boutonSelectPerso = {400, 400, 400, 125};



    while(!sortieMenu){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) sortieMenu = 1;
            if(event.key.keysym.sym == SDLK_ESCAPE) sortieMenu = 1;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        SDL_RenderCopy(renderer, textureTexte, NULL, &zoneTexte);  
        cree_bouton(renderer, boutonSelectPerso, police, couleurNoire, "test");    
        SDL_RenderPresent(renderer);

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(backgroundTexture);
    return 0;
}

int main(void){
    menu();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
