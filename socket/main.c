#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

/*
#include <pthread.h>

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif
*/

#define W 600
#define H 300
#define TEXTE_MAX 16
#define NB_TEXTURES_MAX 3//carre vert, carre rouge, texture texte
#define IND_TEXTURE_TEXTE 2

#define COLOR_WHITE (SDL_Color){255,255,255,255}
#define COLOR_BLACK (SDL_Color){0,0,0,255}
#define endl putchar('\n')
#define flush fflush(stdout)

typedef struct{
	int x,y;
}position;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *textures[NB_TEXTURES_MAX]; int nb_textures;
SDL_Surface *surface = NULL;
TTF_Font *font=NULL;

void end(int);
void init_textures();
SDL_Surface * nouv_surface(char *);
SDL_Texture * nouv_texture();
void nouv_texte(char *, int, SDL_Color);
bool click_in_rect(position, SDL_Rect *);
int main_server();
int main_client(char *);

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) || !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) || TTF_Init()) end(1);
    window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
    if (!window) end(2);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) end(3);
	font = TTF_OpenFont("arial.ttf", 24);
	if(!font) end(99);

	init_textures();
	nouv_surface("boutonA.png");
	nouv_texture();
	nouv_surface("boutonB.png");
	nouv_texture();

	SDL_Rect fond_texte={10,10,16*24,34};//rectangle de fond
	SDL_Rect rect_texte={15,15,0,24};//zone du texte au moment de l'écriture
	SDL_Rect boutonA={(W-32) >> 1, 50,32,32};
	SDL_Rect boutonB={(W-32) >> 1, 150,32,32};

	//fond noir
	SDL_SetRenderDrawColor(renderer,50,50,50,255);
	SDL_RenderClear(renderer);

	//boutons
	SDL_RenderCopy(renderer, textures[0], 0, &boutonA);
	SDL_RenderCopy(renderer, textures[1], 0, &boutonB);

	//zone texte en blanc
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
	SDL_RenderFillRect(renderer, &fond_texte);

    SDL_RenderPresent(renderer);

	Uint32 mouseState;
	position mouse_pos;
    SDL_Event event;
	bool running=1, update=0, ecriture=0;

	char texte[TEXTE_MAX+1]="";
	unsigned int len=0;
    while (running) {
        while (SDL_PollEvent(&event)) {
			switch(event.type){
				case SDL_QUIT:
					running=0;
					break;
				case SDL_TEXTINPUT:
					if(ecriture && len<TEXTE_MAX){
						texte[len++]=event.text.text[0];
						update=1;
					}
					break;
				case SDL_KEYDOWN:
					if(ecriture){
						if (event.key.keysym.sym == SDLK_BACKSPACE && len) {
					        texte[--len] = '\0';
					    } else if (event.key.keysym.sym == SDLK_RETURN) {
					        printf("Texte final : %s\n", texte);flush;
							//détruire la chaîne
							for (int i=len-1; i>0; i--)
						        texte[i] = '\0';
							len=0;
					    }
						update=1;
					}
				    break;
				case SDL_MOUSEBUTTONDOWN:
					mouseState = SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
				//	if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) printf("Bouton gauche de la souris est enfoncé.\n");
					if(click_in_rect(mouse_pos, &fond_texte) && !ecriture){
						SDL_StartTextInput();
						ecriture=1;
						SDL_SetRenderDrawColor(renderer,0,0,255,255);
						update=1;
					}else{
						if(ecriture){
							SDL_StopTextInput();
							ecriture=0;
							SDL_SetRenderDrawColor(renderer,255,255,255,255);
							update=1;
						}

						if(click_in_rect(mouse_pos, &boutonA)){
							printf("Démarrage server\n");flush;
							printf("fin main server avec code %d\n",
								main_server());
							printf("%d %d '%s'\n", update, len, texte);flush;
						}else if(click_in_rect(mouse_pos, &boutonB)){
							printf("Démarrage client\n");flush;
							printf("fin main client avec code %d\n",
								main_client(texte[0] == '\0' ? "127.0.0.1" : texte));flush;
						}
	        		}
					break;
			}
		}

		if(update){
			SDL_RenderFillRect(renderer, &fond_texte);
			if(len){
				printf("'%s'\n", texte);flush;
				nouv_texte(texte, 1, ecriture ? COLOR_WHITE : COLOR_BLACK);
				rect_texte.w=24*len;
				SDL_RenderCopy(renderer, textures[IND_TEXTURE_TEXTE], 0, &rect_texte);
			}
			SDL_RenderPresent(renderer);
			update=0;
		}
        SDL_Delay(100);
    }

	if(ecriture)
		SDL_StopTextInput();

	end(0);
    return 0;
}

bool click_in_rect(position mouse_pos, SDL_Rect * r){
	return mouse_pos.x >= r->x && mouse_pos.x <= r->x + r->w && mouse_pos.y >= r->y && mouse_pos.y <= r->y + r->h;
}

void end(int code) {
	if (surface) SDL_FreeSurface(surface);
    if (nb_textures) for (int i=0; i<nb_textures; i++) SDL_DestroyTexture(textures[i]);
	if (font) TTF_CloseFont(font);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
	TTF_Quit();
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
}
void nouv_texte(char * texte, int remplace, SDL_Color coul){
	if(surface)	SDL_FreeSurface(surface);
	surface = TTF_RenderText_Solid(font, texte, coul);
	if (remplace) {
		if(textures[IND_TEXTURE_TEXTE]) SDL_DestroyTexture(textures[IND_TEXTURE_TEXTE]);
		int temp=nb_textures;
		nb_textures=IND_TEXTURE_TEXTE;
		nouv_texture();
		nb_textures=temp;
	}else{
		nouv_texture();
	}
}
