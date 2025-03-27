#include "cli_jeu.h"

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

int main_client(char * ip, char * pseudo, classe_t classe) {
	//setup socket
	int error_code;
	if((error_code=setup_client(ip)) > 0){
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

	perso_t joueurs[nb_joueurs];
	SDL_Texture * textures_joueurs[nb_joueurs][4];
	sdl_struct sdl_objets[PERSO_OBJETS_MAX];

	init_sdl();
	init_joueurs_client(joueurs);
	charger_sdl_joueurs(joueurs, textures_joueurs);

	puts("Les joueurs sont :");
	for(int i=0; i<nb_joueurs; i++){
        printf("ind %d ; classe %d ; nom %s ; equipe %d ; position %d %d\n", joueurs[i].iperso, joueurs[i].classe, joueurs[i].nom, joueurs[i].equipe, joueurs[i].pos_map.x, joueurs[i].pos_map.y);
    }
	flush;
	perso_t * j = joueurs + indice;//pointeur sur le joueur, plus rapide
	char valide=1;
	int compteur=0;

	sleep(indice * 1);
	texture_tuile = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, W, H);
	init_jeu();
	tuile_t * tuile_courante = get_tuile_joueur(joueurs + indice);
	charger_tuile(tuile_courante);
	afficher_tuile();

    SDL_RenderCopy(renderer, textures_joueurs[indice][0], NULL, &j->rect);
	ecran();

	SDL_Event event;
    const Uint8* clavier;
	while(valide && client.online){//si le thread est fermé prématurément

		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.sym==SDLK_m){
                valide=0;
				break;
            }
        }

		clavier=SDL_GetKeyboardState(NULL);
        Uint8 mask=clavier[SDL_SCANCODE_RIGHT] << 3 | clavier[SDL_SCANCODE_LEFT] << 2 | clavier[SDL_SCANCODE_DOWN] << 1 | clavier[SDL_SCANCODE_UP];
		if(mask){
			dir_t dir=j->dir;
			changer_dir(j, mask);
			if(j->dir != dir)
				sendf("dd", JOUEUR_CHANGE_DIR, j->dir);
			avancer(j);
			//serv simule aussi de son côté
		}else{
			sendf("dd", JOUEUR_CHANGE_DIR, nulldir);
		}

		while(!fileVide(file_socket)){
			data=defiler(file_socket);
			printf("action '%s'\n", (char*)data);flush;
			int action;
			sscanf(data, "%d", &action);
			switch(action){
				case SPAWN_OBJET:{
					int ind_o;
					pos_t pos_tuile;
					sscanf(data_skip(data, 1), "%d %d %d", &ind_o, &pos_tuile.x, &pos_tuile.y);
					ajouter_objet_tuile(tuile_courante, ind_o, pos_tuile);
					//!! ajout dans sdl_objet
					break;
				}
				case JOUEUR_MV_TUILE:{
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
						ajout_fin_liste(tuile_courante->liste_joueurs, joueurs + ind, sizeof(perso_t*));
						//!!param ?
						skip+=3;
					}
				    charger_tuile(tuile_courante);
				}
			}
			free(data);
		}
		if(compteur > 10000)
			valide=0;
		else compteur += DELAY;

	//affichage
		//fond
		afficher_tuile();
		//joueurs
		for(tete_liste(tuile_courante->liste_joueurs); !hors_liste(tuile_courante->liste_joueurs); suivant_liste(tuile_courante->liste_joueurs)){
			perso_t * joueur_cour = get_liste(tuile_courante->liste_joueurs);
			SDL_RenderCopy(renderer, textures_joueurs[joueur_cour->iperso][joueur_cour->dir % 4], NULL, &joueur_cour->rect);
		}
		//objets

		ecran();
		SDL_Delay(DELAY);
	}
	send(client.socket, "!", 1, 0);

	while(client.online){
		puts("attente");
		sleep(1);//attend fin ecoute_thread
	}

    detruire_joueurs_client(joueurs, textures_joueurs);
	SDL_DestroyTexture(texture_tuile);
	end(0);
	fermeture_client(0);
    return 0;
}

int main(int argc, char *argv[]){
	return main_client("127.0.0.1", "boi", vampire);
}

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
			printf("Recu : '%s'\n", buffer);flush;
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
							enfiler(file_socket, debut, fin-debut);
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

int setup_client(char * ip){
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
	client.addr.sin_port = htons(PORT);//atoi(port)
	client.addr.sin_addr.s_addr = inet_addr(ip);

	if(connect(client.socket, (struct sockaddr *)&client.addr, sizeof(client.addr)) == -1)
		return 3;

	return 0;
}
