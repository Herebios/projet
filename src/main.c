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

/*Renvoie un pointeur sur la tuile où est le perso p*/
tuile_t *ptr_tuile_joueur(perso_t * p){
	return map[p->pos_map.y] + perso->pos_map.x;
}
void afficher_tuile_courante(){
    SDL_RenderCopy(renderer, jeu.texture_tuile, 0, 0);
}
void charger_tuile_courante(){//jeu
	tuile_t* tuile = jeu.tuile_courante;
	SDL_SetRenderTarget(renderer, jeu.texture_tuile);
	for (int l=0,c; l<HAUTEUR_TUILE; l++)
		for (c=0; c<LARGEUR_TUILE; c++)
			SDL_RenderCopy(renderer, tuile->biome->textures[tuile->id_texture[l][c]], 0, &(SDL_Rect){c*CARRE_W,l*CARRE_H,CARRE_W,CARRE_H});
	SDL_SetRenderTarget(renderer, NULL);
}

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

void avancer(perso_t *p){//uniquement pour le joueur
//!!gérer collisions avec obstacles
//?? carrés de sortie même pour les tuiles sur un bord de map ?
//-si non, modifier un peu cette fonction, et adapter génération des tuiles
//?? si sauvegarde précédente tuile dans struct jeu, il faudra ajouter un peu de code

	if(!p)return;
	SDL_Rect rect_tuile={0,0,W,H};
	SDL_Rect rect = p->rect;//séparé
	int deltax=deplacement[p->dir].x * p->vit;
	int deltay=deplacement[p->dir].y * p->vit;
	bool sortie=0;
	pos_t pos;

	/*Ne pas dépasser les bords. Tests x et y séparés pour ne pas être bloqué
	si 2 touches sont appuyées et une des directions est un bord*/

	rect.x+=deltax;
	if(inclus(&rect, &rectuile_t))
		p->rect.x=rect.x;
	else{//bord tuile dépassé
		position_perso(p, &pos);
		printf("%d %d\n", pos.x, pos.y);flush;
		//tuile de sortie?
		if(jeu.tuile_courante->id_texture[pos.y][pos.x]==sortie){
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
}

void changer_dir(perso_t *p, Uint8 mask){
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

void position_perso(perso_t *p, pos_t* pos){
	int y=p->rect.y + (p->rect.h >> 1);//ajout de hauteur/2, ~milieu du perso
	pos->y = y/CARRE_H;
	int x=p->rect.x + (p->rect.w >> 1);
	pos->x = x/CARRE_W;
}
void effacer_joueur(perso_t *p){
}
    SDL_RenderCopy(renderer, jeu.texture_tuile, &p->rect, &p->rect);//ce qu'il y avait dessous, redessiné dessus

void afficher_joueur(perso_t *p){
    SDL_RenderCopy(renderer, p->texture_courante, &p->sprite, &p->rect);
}


//taille texture : SDL_QueryTexture(textures[0], NULL, NULL, &largeur_texture, &hauteur_texture);
int main(int argc, char *argv[]) {
	char *pseudo, classe, *ipAddress;
	int code = menu(pseudo, &classe, ipAddress);
	switch (code){
		case 0: // client
			code = main_client(ip, pseudo, (classe_t) classe);
			break;
		case 2: // server and client
			pthread_t thread;
			pthread_create(&thread, NULL, main_client_thread, NULL);
		case 1: // only server
			code = main_server();
			break;
	}
	end(code);
	return 0;

	/*window, renderer, jeu(map(textures, tuiles), texture_tuile, perso)*/
	init_sdl();
	init_jeu();

	charger_tuile_courante();
	afficher_tuile_courante();

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
