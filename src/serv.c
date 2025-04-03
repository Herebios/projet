/**
 * @file serv.c
 * @author Baptiste
 * @brief code principal du serveur
 */
#include "serv_socket.h"
#include "serv_jeu.h"

int main_server(int port, int nb_clients) {
	//setup socket
	int error_code;
	if ((error_code = setup_server(port, nb_clients)) > 0){
		//sortie avec libération adaptée
		fermeture_server(error_code);
		return error_code;
	}
	//le server est prêt, on va s'occuper des clients
	puts("setup server OK\n");
	printf("Nombre de clients : %d, pas de place libérée quand déconnexion\n", nb_clients);flush;
	clients = malloc(sizeof(socket_struct) * nb_clients);

	serv_file = newFile();

	server.nb_clients=0;
	server.server_struct.online=1;
	server.nb_on=0;

	pthread_create(&server.server_struct.thread, NULL, accept_thread, &nb_clients);
	//nouv clients thread

	char buffer[BUFFERLEN]="Il y a ";
	while(server.nb_clients < nb_clients){
		printf("%d", server.nb_clients);flush;
		sprintf(buffer + 7, "%d", server.nb_clients);
		strcat(buffer, " clients !;");
		broadcast(buffer, -1);
		sleep(1);
	}
	server.nb_on=nb_clients;
	//à partir d'ici on peut utiliser server.nb_clients (global)
	broadcast("start;", -1);

	srand(time(0));
	int random_seed = rand();
	//Chaque client reçoit son indice et la seed random
	for (int i=0; i<nb_clients; i++) {
		sprintf(buffer, "%d %d %d;", i, nb_clients, random_seed);
		send(clients[i].socket, buffer, strlen(buffer), 0);
	}

	init_jeu();

	perso_t joueurs[nb_clients];
	init_joueurs_server(joueurs, nb_clients);
	send_joueurs_server(joueurs, nb_clients);
	puts("Joueurs :");
	for(int i=0; i<nb_clients; i++){
		printf("ind %d , classe %d , nom %s , equipe %d\n", i, joueurs[i].classe, joueurs[i].nom, joueurs[i].equipe);
	}
	flush;
	//init les tuiles avec les joueurs
	for(int i=0; i<nb_clients; i++){
		tuile_t * t=get_tuile_joueur(joueurs + i);
		ajouter_joueur_tuile(t, i);
	}
	flush;

	for(int i=0; i<nb_clients; i++){
		maj_tuile(joueurs, i);
	}
	/*on[i] correspond à clients[i].online, pour mémoriser lequels sont off et ne les compter qu'une fois
	on décrémente nb_on, qui est incrémenté quand le thread accepte un nouveau client
	quand nb_on sera à 0 et premier_client à 1, le serveur s'arrêtera
	*/
	char * data;
	int ind_j;//ind du joueur qui envoie
	int action;
	int compteur=0;

	while (server.nb_on){
		while(!fileVide(serv_file)){
			data=defiler(serv_file);
			sscanf(data, "%d %d", &ind_j, &action);
			switch(action){
				case JOUEUR_CHANGE_DIR:
					sscanf(data_skip(data, 2), "%d", (int*)&joueurs[ind_j].dir);
					break;
				case ADD_OBJET_JOUEUR:{
					int ind_o;
					sscanf(data_skip(data, 2), "%d", &ind_o);
					ajouter_objet_joueur(joueurs + ind_j, ind_o);
					update_stats(joueurs + ind_j);
					break;
				}
				case RM_OBJET_JOUEUR:{
					int ind_inv, ind_o;
					sscanf(data_skip(data, 2), "%d", &ind_inv);
					ind_o = joueurs[ind_j].objets[ind_inv]->ind;
					retirer_objet_joueur(joueurs + ind_j, ind_inv);
					update_stats(joueurs + ind_j);

					//on ajoute l'objet sur la tuile
					pos_t pos_tuile;
					position_perso(joueurs + ind_j, &pos_tuile);
					spawn_objet((rarete_t)rand()%4, 1, ind_o, joueurs[ind_j].pos_map, pos_tuile);
					break;
				}
				case BASIC_ATTACK:{
					int ind_j;

					pos_t tilePos;
					perso_t *p = joueurs + ind_j;
					position_perso(p , &tilePos);
					tuile_t *tile = get_tuile_from_pos(tilePos);
					tilePos.x += 2 * deplacement[p->dir].x;
					tilePos.y += 2 * deplacement[p->dir].y;

					size_t listeTaille = taille_liste(tile->liste_joueurs);
					perso_t *victim;
					pos_t victim_tilePos;
					for (int i = 0; i < listeTaille; i++){
						victim = get_liste(tile->liste_joueurs);
						position_perso(victim, &victim_tilePos);
						if (victim_tilePos.x == tilePos.x && victim_tilePos.y == tilePos.y){
							printf("\nvictim!!!\n");
						}
						suivant_liste(tile->liste_joueurs);
					}
				}
			}
			free(data);
		}

		//gerer les deco
		server.nb_on=server.nb_clients;
		for (int i=0; i<nb_clients; i++){
			if(!clients[i].online){
				server.nb_on--;
			}
		}

		//bouger les joueurs
		for(int i=0; i<nb_clients; i++){
			if(joueurs[i].dir != nulldir){
				avancer(joueurs+i);
				check_sortie_tuile(joueurs, i);//fait l'envoi

				char buffer[16];
				sprintf(buffer, "%d %d %d %d %d;", JOUEUR_MV, i, joueurs[i].rect.x, joueurs[i].rect.y, joueurs[i].dir);
				//envoie aux joueurs la position des autres
				tuile_t * tuile = get_tuile_joueur(joueurs + i);
		        for(tete_liste(tuile->liste_joueurs); !hors_liste(tuile->liste_joueurs); suivant_liste(tuile->liste_joueurs)){
		            int ind = *(int*)get_liste(tuile->liste_joueurs);
					if(ind != i)
						send(clients[ind].socket, buffer, strlen(buffer), 0);
				}
			}
		}

		//evenements
		if(compteur % 1000 == 0){
			for(int i=0; i<nb_clients; i++){
				printf("J %d : tuile %d %d | position %d %d\n", i, joueurs[i].pos_map.x, joueurs[i].pos_map.y, joueurs[i].rect.x, joueurs[i].rect.y);
			}
		}
		if(compteur >= 5000){
			puts("Spawn obj\n");flush;
			//paramètres temporaires
			int ind; pos_t pos1, pos2;
			spawn_objet((rarete_t)rand()%4, 0, ind, pos1, pos2);
			compteur=0;
		}else
			compteur+=DELAY;

		SDL_Delay(DELAY);
	}
	puts("fin boucle");flush;

	detruire_joueurs_server(joueurs, nb_clients);
	end(0);
	//libération complète
	fermeture_server(0);
	return 0;
}

int main(int argc, char *argv[]){
	if(argc != 2){
		puts("pas de port");
		return 1;
	}
	if(atoi(argv[1]) > 1024)
		main_server(atoi(argv[1]), 2);
	return 0;
}
