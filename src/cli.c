#include "cli.h"

file * file_socket;

//variables utilisées en global
socket_struct client;
int indice, nb_joueurs;

/* Utilise va_arg pour envoyer facilement ce qu'on veut
socket et ind en global*/
void sendf(char * format, ...){
	char buffer[BUFFERLEN], *pformat=format;
	sprintf(buffer, "%d ", indice);
	va_list va;
	va_start(va, format);
	while(*pformat)
		switch(*pformat++){
			case 'd':
				sprintf(buffer+strlen(buffer), "%d ", va_arg(va, int));
				break;
			case 's':
				sprintf(buffer+strlen(buffer), "%s ", va_arg(va, char*));
				break;
		}
	va_end(va);
	send(client.socket, buffer, strlen(buffer), 0);
}

/*Utilisé pour lire après nb espaces
Voir switch main_serv*/
char * data_skip(char * data, int nb){
    char * skip=data + 1;
    while(nb){
        if(*skip++ == ' ')
            nb--;
    }
    return skip;
}

int main_client(char * ip, int port, char * pseudo, classe_t classe) {
	//setup socket
	int error_code;
	if((error_code=setup_client(ip, port)) > 0){
		fermeture_client(error_code);
		return error_code;
	}
	puts("setup client OK\n");flush;

	file_socket = newFile();

	int buffer_size;
	char buffer[BUFFERLEN];

	pthread_create(&client.thread, NULL, ecoute_thread, NULL);

	//attente de lancement
	char * data;
	char endwhile=0;
	while(!endwhile){
		data=defiler(file_socket);
		if(data){
			puts(data);flush;
			if(strcmp(data, "start")==0)
				endwhile=1;
			free(data);
			data=NULL;
		}
		putchar('\n');
		sleep(1);
	}
	if(data){
		puts(data);
		free(data);
	}

	int seed;
	//Récupère son indice
	sleep(1);
	data=defiler(file_socket);
	sscanf(data, "%d %d %d", &indice, &nb_joueurs, &seed);
	free(data);
	printf("Je suis le client %d/%d !\n", indice, nb_joueurs);

	//serv init le perso
	sendf("ds", classe, pseudo);

	init_sdl();
	init_jeu();

	perso_t joueurs[nb_joueurs];
	SDL_Texture * textures_joueurs[nb_joueurs][4];
	SDL_Texture * textures_objets[NB_OBJETS];

	init_joueurs_client(joueurs);
	charger_sdl_joueurs(joueurs, textures_joueurs);
	charger_sdl_objets(textures_objets);

	
	perso_t * j = joueurs + indice;//pointeur sur le joueur, plus rapide
	char valide=1;
	int compteur=0;

	texture_tuile = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, W, H);
	tuile_t * tuile_courante = NULL;;

	SDL_Event event;
    const Uint8* clavier = NULL;
	char isSPACEPress = 0;
	char isEPress = 0;
	time_t t = 0;
	dir_t dir = nulldir;
	supp_t enlever_obj = NUL;
	while(valide && client.online){//si le thread est fermé prématurément

		
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.sym==SDLK_m){
                valide=0;
				break;
            }
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && !isSPACEPress && time(NULL) - t > 3){
				isSPACEPress = 1;
				t = time(NULL);
			}

			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e && !isEPress){
				isEPress = 1;

				sendf("d", GET_OBJET);
			}

			

			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_1 : enlever_obj = UN; break;
					case SDLK_2 : enlever_obj = DEUX; break; 
					case SDLK_3 : enlever_obj = TROIS; break; 
					case SDLK_4 : enlever_obj = QUATRE; break; 
					case SDLK_5 : enlever_obj = CINQ; break; 
					default : break;
				}
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE){
				isSPACEPress = 0;
			}else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_e){
				isEPress = 0;
			}
			else if(event.type == SDL_KEYUP && enlever_obj != NUL){
				enlever_obj = NUL;
			}
        }

		if (isSPACEPress){
			isSPACEPress = 0;
			if (dir != nulldir)
				attaqueBasique(j, dir);
		}

		else if(enlever_obj != NUL){
			lacher_objet(j, enlever_obj);
			enlever_obj = NUL;
		}
		clavier=SDL_GetKeyboardState(NULL);	
        Uint8 mask=clavier[SDL_SCANCODE_RIGHT] << 3 | clavier[SDL_SCANCODE_LEFT] << 2 | clavier[SDL_SCANCODE_DOWN] << 1 | clavier[SDL_SCANCODE_UP];
		if(mask){
			dir=j->dir;
			changer_dir(j, mask);
			if(j->dir != dir)
				sendf("dd", JOUEUR_CHANGE_DIR, j->dir);

			avancer(j);

			//serv simule aussi de son côté
		}else if(j->dir != nulldir){
			j->dir=nulldir;
			sendf("dd", JOUEUR_CHANGE_DIR, nulldir);
		}
		while(!fileVide(file_socket)){
			data=defiler(file_socket);
			int action;
			sscanf(data, "%d", &action);
			//printf("\naction : %d", action);
			switch(action){
				case SPAWN_OBJET:{
					int ind_o;
					pos_t pos_tuile;
					sscanf(data_skip(data, 1), "%d %d %d", &ind_o, &pos_tuile.x, &pos_tuile.y);
					ajouter_objet_tuile(tuile_courante, ind_o, pos_tuile);
					//!! ajout dans sdl_objet
					break;
				}
				case JOUEUR_MV:{
					int i;
					sscanf(data_skip(data, 1), "%d", &i);
					sscanf(data_skip(data, 2), "%d %d %d", &joueurs[i].rect.x, &joueurs[i].rect.y, (int*)&joueurs[i].dir);
					break;
				}
				case JOUEUR_MV_TUILE:{
					detruire_tuile(get_tuile_joueur(j), 1);

					int nb_o, nb_j;
					sscanf(data_skip(data, 1), "%d %d %d", &j->pos_map.x, &j->pos_map.y, &nb_o);
					tuile_courante = get_tuile_joueur(j);
					int skip=4;
					int ind;
					pos_t pos;
					for(int i=0; i<nb_o; i++){
						sscanf(data_skip(data, skip + 3*i), "%d %d %d", &ind, &pos.x, &pos.y);
					    ajouter_objet_tuile(tuile_courante, ind, pos);
					}
					skip=4+3*nb_o;
					sscanf(data_skip(data, skip++), "%d", &nb_j);
					for(int i=0; i<nb_j; i++){
						sscanf(data_skip(data, skip), "%d %d %d", &ind, &pos.x, &pos.y);
						joueurs[ind].rect.x = pos.x;
						joueurs[ind].rect.y = pos.y;
						ajouter_joueur_tuile(tuile_courante, ind);
						skip+=3;
					}
				    charger_tuile(tuile_courante);
					break;
				}
				case ADD_JOUEUR_TUILE:{
					int ind;
					sscanf(data_skip(data, 1), "%d", &ind);
					if (tuile_courante){
						ajouter_joueur_tuile(tuile_courante, ind);
					}
					break;
				}
				case RM_JOUEUR_TUILE:{
					int ind;
					sscanf(data_skip(data, 1), "%d", &ind);
					retirer_joueur_tuile(tuile_courante, ind);
					break;
				}
				case GET_OBJET:{
					int ind_o, ind_p;
					sscanf(data_skip(data, 1), "%d %d", &ind_o, &ind_p);
					tuile_t * tuile = get_tuile_from_pos(j->pos_map);
					if (j->iperso == ind_p){
						ajouter_objet_joueur(j, ind_o);
					}
					retirer_objet_tuile(tuile, ind_o);
				}
			}
			free(data);
		}
		compteur += DELAY;

	//affichage
		//fond
		afficher_tuile();
		
		//joueurs
		for(tete_liste(tuile_courante->liste_joueurs); !hors_liste(tuile_courante->liste_joueurs); suivant_liste(tuile_courante->liste_joueurs)){
			int ind = *(int*)get_liste(tuile_courante->liste_joueurs);
			SDL_RenderCopy(renderer, textures_joueurs[ind][((ind == indice) ? dir : joueurs[ind].dir) % 4], NULL, &joueurs[ind].rect);
			
		}
		//objets
		for(tete_liste(tuile_courante->liste_objets); !hors_liste(tuile_courante->liste_objets); suivant_liste(tuile_courante->liste_objets)){
			objet_tuile_t * obj = get_liste(tuile_courante->liste_objets);
			SDL_RenderCopy(renderer, textures_objets[obj->objet->ind], NULL, &(SDL_Rect){obj->pos.x * CARRE_W, obj->pos.y * CARRE_H, CARRE_W, CARRE_H});
		}
		show_inventaire(renderer, j);




		ecran();
		SDL_Delay(DELAY);
	}
	send(client.socket, "!", 1, 0);

	while(client.online){
		puts("attente");
		sleep(1);//attend fin ecoute_thread
	}

	detruire_objets_client(textures_objets);
    detruire_joueurs_client(joueurs, textures_joueurs);
	SDL_DestroyTexture(texture_tuile);
	end(0);
	fermeture_client(0);
    return 0;
}
/*int main(int argc, char *argv[]){
	if(argc == 5){
		return main_client(argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));
	}else{
		puts("ip port nom classe");
		return 1;
	}
}*/

void *ecoute_thread(void *arg){
/*
S'arrête quand le serveur envoie '!'
Signal par pointeur qui arrête le main
*/
	int buffer_size;
    char buffer[BUFFERLEN];
    char valide=1;
	client.online=1;
	while(valide){
		buffer_size = recv(client.socket, buffer, BUFFERLEN, 0);
		if(buffer_size > 0){
            buffer[buffer_size] = '\0';
            switch(*buffer){
                case '!':
					valide=0;
					break;
                default:{
					//on sépare les messages et on les met dans la file
					char * debut, * fin;
					debut=fin=buffer;
					while(*fin)
						if(*fin == ';'){
							*fin=0;
							enfiler(file_socket, debut, fin-debut+1);
							fin++;
							debut=fin;
						}else fin++;
				}
            }
        }else{
			valide=0;
			puts("Le serveur est mort, je crois.");
		}
	}
	puts("fin ecoute thread\n");flush;
	client.online=0;
	return NULL;
}
void fermeture_client(int error_code){
/*
Libération correspondant au code renvoyé par le setup en cas d'échec,
tout à la fin du programme, avec le code 0.
*/
	printf("fermeture\n");
	if(file_socket)fileFree(&file_socket, free);
	switch(error_code){
case 0:
case 3:
	#ifdef _WIN32
    closesocket
    #else
    close
    #endif
    (client.socket);
case 2:
    #ifdef _WIN32
    WSACleanup();
    #endif
case 1:
	break;
	}
}

int setup_client(char * ip, int port){
	int error_code;
	#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa))
		return 1;
	#endif

/* Si input de la forme ip:port
	char ip[16];
	char port[6];
	char *p=strchr(argv[1], ':');
	*p++='\0';
	strcpy(ip,argv[1]);
	strcpy(port,p);
*/
	if ((client.socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return 2;

	client.addr.sin_family = AF_INET;
	client.addr.sin_port = htons(port);
	client.addr.sin_addr.s_addr = inet_addr(ip);

	if(connect(client.socket, (struct sockaddr *)&client.addr, sizeof(client.addr)) == -1)
		return 3;

	return 0;
}
