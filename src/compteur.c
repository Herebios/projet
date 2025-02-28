#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#define W 600
#define H 300

#define endl putchar('\n')
#define flush fflush(stdout)
#define COLOR_WHITE (SDL_Color){255,255,255,255}
#define COLOR_BLACK (SDL_Color){0,0,0,255}
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Surface *surface;
/*
void end(int code) {
	if (surface) SDL_FreeSurface(surface);
    if (nb_textures) for (int i=0; i<nb_textures; i++) SDL_DestroyTexture(textures[i]);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	if (code==0) return;//fin de programme normale
	exit(code);
}

void init_textures() {nb_textures=0; for (int i=0; i<NB_TEXTURES_MAX; i++) textures[i]=NULL;}

SDL_Surface * nouv_surface(char * image) {
    if (surface) SDL_FreeSurface(surface);
    if (surface = IMG_Load(image))//SDL_LoadBMP(image)
        return surface;
    end(5);
}
SDL_Texture * nouv_texture() {
    if (nb_textures==NB_TEXTURES_MAX) end(4);
    if (textures[nb_textures] = SDL_CreateTextureFromSurface(renderer, surface))
        return textures[nb_textures++];
    end(4);
}*/
extern SDL_Texture * nouv_texte(char * texte, int code, SDL_Color);
extern SDL_Texture * nouv_texture(char * chemin, int code);

typedef struct{
	int x,y;
}position;
extern bool click_in_rect(position, SDL_Rect *);

void aff_bit(SDL_Rect * rect, SDL_Texture * tex){
	SDL_RenderFillRect(renderer, rect);
	SDL_RenderCopy(renderer, tex, NULL, rect);
}

void aff_tab(SDL_Rect tab[8], SDL_Texture * bits[2], unsigned char compteur){
	for (int i=0; i<8; i++){
		aff_bit(tab+i, bits[(compteur>>i) & 1]);
	}
}

typedef struct{
	SDL_Rect rect;
	SDL_Texture * tex;
}bouton_t;

int main_compteur(int debut) {
	SDL_Texture * bits[2] = {
		nouv_texte("0", -2, COLOR_WHITE),
		nouv_texte("1", -2, COLOR_WHITE)
	};
	SDL_Rect tab[8];
	for (int i=7; i>=0; --i){
		tab[i] = (SDL_Rect){50*(8-i),50,24,24};
	}
	unsigned char compteur=debut;//8 bits

	bouton_t boutons[3]={
		{
			{100, 100, 50, 50},
			nouv_texture("boutonA.png", -2)
		},
		{
			{200, 100, 50, 50},
			nouv_texture("boutonB.png", -2)
		},
		{
			{300, 100, 50, 50},
			nouv_texture("boutonC.png", -2)
		}
	};

	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, boutons[0].tex, NULL, &boutons[0].rect);
	SDL_RenderCopy(renderer, boutons[1].tex, NULL, &boutons[1].rect);
	SDL_RenderCopy(renderer, boutons[2].tex, NULL, &boutons[2].rect);

	aff_tab(tab, bits, compteur);

	SDL_RenderPresent(renderer);

	Uint32 mouseState;
	position mouse_pos;
    SDL_Event event;
	bool running=1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type==SDL_KEYDOWN && (event.key.keysym.sym==SDLK_ESCAPE || event.key.keysym.sym==SDLK_m))) {
                running=0;
                break;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				mouseState=SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
				if (click_in_rect(mouse_pos, &boutons[0].rect))
					compteur++;
				else if (click_in_rect(mouse_pos, &boutons[1].rect))
					compteur--;
				else if (click_in_rect(mouse_pos, &boutons[2].rect)){
					running=0;
					break;
				}
				aff_tab(tab, bits, compteur);
				SDL_RenderPresent(renderer);
            }
        }

//		SDL_RenderCopy(renderer,textures[0],0,0);
//		SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
	SDL_DestroyTexture(bits[0]);
	SDL_DestroyTexture(bits[1]);

	SDL_DestroyTexture(boutons[0].tex);
	SDL_DestroyTexture(boutons[1].tex);
	SDL_DestroyTexture(boutons[2].tex);

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

    return compteur;
}
