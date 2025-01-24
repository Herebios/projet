/* Déclarations des fonctions
Les dépendances sont marquées par une tab. La fonction appelle les autres
*/

int main(int argc, char **argv);

//fin du programme
void end(int);

/* init les ressources du jeu */
void init_sdl(void);

void init_jeu(void);
	//void init_objets(void);
	void init_map(void);
		//génère une tuile en fonction du biome qu'on veut
		void generer_tuile(t_tuile*, nom_biome);

	void init_biomes(void);

/* Relatif aux joueurs */
void nouv_perso(char* nom);//le nom donne le chemin des textures
//indices de la position du joueur sur la tuile
void position_perso(t_perso*, t_pos*);
void avancer(t_perso*);//déplacement d'un joueur en fonction de sa direction
	bool inclus(SDL_Rect* a, SDL_Rect* b);//pour l'instant, vérifie si le joueur ne sort pas de l'écran
//modification des attributs
void changer_anim(t_perso*, t_anim);//modifier l'animation d'un joueur
void changer_dir(t_perso*, Uint8 mask);//modifie la dir d'un joueur selon le clavier (4 flèches)
//place la texture à l'écran
void effacer_joueur(t_perso*);
void afficher_perso(t_perso*);

//appel de surface puis de texture pour charger une image
void nouv_surface(char* path);
void nouv_texture(SDL_Texture** textures, unsigned char* nb);

//renvoie un pointeur sur la tuile du joueur
t_tuile* ptr_tuile_courante();
//charge jeu.tuile_courante dans jeu.texture_tuile (prêt à afficher)
void charger_tuile_courante(void);
void afficher_tuile_courante();

