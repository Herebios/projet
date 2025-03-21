/**
 * @file main.c
 * @author Baptiste
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "SDL_def.h"

#include "prepro.h"
#include "def.h"
#include "fonctions.h"

#include "menu.h"
#include "cli.c"
#include "serv.c"

void nouv_perso(char *s){//jeu, perso
//?? parametre classe
	if (jeu.nb_perso==NB_PERS_MAX) end(7);
	perso = jeu.perso + jeu.nb_perso;//pointeur sur nouv perso
	//valeurs par defaut
	classe_t classe=administrateur;
	*perso = (perso_t){
		0,0,0,
		VITESSE_BASE,NIVEAU_BASE,VIE_BASE,ATTAQUE_BASE,DEFENSE_BASE,MAGIE_BASE,MANA_BASE,
		classe,
		{0,0}//!!position : map.tuiles[y][x]
	};
	perso->sprite = (SDL_Rect){0, 0, jw, jh};
	perso->rect = (SDL_Rect){xdep, ydep, jw, jh};//position sur tuile

	//!!au lieu de char *s, on utilisera l'attribut classe du joueur
	//charger textures perso
	char chemin[50];
	strcpy(chemin, "img/Characters/");
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

//taille texture : SDL_QueryTexture(textures[0], NULL, NULL, &largeur_texture, &hauteur_texture);
int main(int argc, char *argv[]) {
	char *pseudo, classe, *ipAddress;
	int code = menu(pseudo, &classe, ipAddress);
	switch (code){
	case 0: // client
		return main_client(ip, pseudo, (classe_t) classe);
	case 2: // server + client
		pthread_t thread;
		pthread_create(&thread, NULL, main_client_thread, NULL);
	case 1: // server
		return main_server();
	}
	/*
	!! Pas de code après !!
	*/

	/*window, renderer, jeu(map(textures, tuiles), texture_tuile, perso)*/
	init_sdl();
	init_jeu();

	charger_tuile_courante();
	afficher_tuile_courante();

	perso_t *j=jeu.perso;//perso 0 = joueur
	afficher_perso(j);

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
		dir_t dir=j->dir;
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

/*
void changer_anim(perso_t *p, anim_t anim){
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
*/
