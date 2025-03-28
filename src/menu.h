/**
 * @file menu.h
 * @author Ilann
 * @brief Création du menu principal du jeu
 */



 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <SDL2/SDL.h>
 #include <SDL2/SDL_image.h>
 #include <SDL2/SDL_ttf.h>
 #include <SDL2/SDL_mixer.h>
 #include <regex.h>

 
 
 #define IMG_X 400
 #define IMG_H 150
 #define IMG_W 400
 #define X_BOUTON_PARAM 600
 #define W_BOUTON_PARAM 700
 #define H_BOUTON_PARAM 200
 #define H_FLECHE 920
 #define NB_IMG 24 //nombre d'images générés par le menu !!! a changer si le nb d'images change
 #define NB_TEXTE 24 //nombre de textes générés par le menu !!! a changer si le nb de texte change
 #define NB_MAX_PERSO 10
 #define NB_MAX_CAR_JOUEUR 20
 #define NB_MAX_CAR_IP 16
 #define JOUER 0
 #define SERVEUR 1
 #define JOUER_SERVEUR 2


/**
 * @brief Correspondant à la position du joueur dans le menu
 */
typedef enum {
    MENU_PRINCIPAL, ///<le joueur se trouve dans la page d'accueil du menu
    DANS_PARAM, ///<le joueur se trouve dans les paramètres du menu
    DANS_JOUER, ///<le joueur se trouve dans l'option jouer
    DANS_CREER, ///<le joueur se trouve dans l'option créer
    DANS_REJOINDRE, ///<le joueur se trouve dans l'option rejoindre
    BAD_IP, ///<le joueur a tenté de valider une adresse ip invalide
    BAD_NAME, ///<le joueur veut jouer sans avoir saisi de nom
    SORTIE_MENU ///<le joueur quitte le menu
}position_menu; 

 
/**
 * @brief Permet de stocker la position et la texture d'un élément image du menu
 */
typedef struct {
     SDL_Rect posBoutonFen; ///<Coordonnées x, y et hauteur et largeur de l'image dans la fenêtre
     SDL_Texture * texture; ///<Texture de l'image
}img_t;
 

/**
 * @brief Permet de stocker la position, la texture et le texte d'un élément texte du menu
 */
typedef struct {
     SDL_Rect posTexte; ///<Coordonnées x, y et hauteur et largeur du texte dans la fenêtre
     SDL_Texture * message; ///<Texture du texte
     char contenu[NB_MAX_CAR_JOUEUR + 1]; ///<le texte sous forme de chaîne de caractères
}texte_t;
 
 
 /*
 enlever les 2 premières fonctions quand ce sera avec le main. 
 end : rajouter 
     for(int i = 0 ; i < nb_img ; i++){
         SDL_DestroyTexture(tab_img[i].texture);
     }
     for(int i = 0 ; i < nb_texte ; i++){
         SDL_DestroyTexture(tab_texte[i].message);
     }
     if (police)
         TTF_CloseFont(police);
 
     TTF_Quit();
 
     init_sdl :rajouter
     SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
 */
 


void end(int nb);
void init_sdl(void);
 

/**
 * @brief Utile pour la lisibilité du code, remplace une ligne de SDL_RenderCopy pour les images
 */
void dessine_img(int i);

/**
 * @brief Utile pour la lisibilité du code, remplace une ligne de SDL_RenderCopy pour les textes
 */
void dessine_texte(int i);

/**
 * @brief Permet de mettre à jour l'adresse ip saisie avec les touches du keypad et du clavier normal
 * @param touche La dernière touche pressée
 * @param nbCar Le nombre de caractères que contient l'ip 
 * @param saisie L'ip qui va être modifiée
 */
void saisie_touche_ip(SDL_Keycode touche, int * nbCar, char * saisie);

/**
 * @brief Affiche le menu correspondant à l'endroit où l'on se trouve
 * @param pos L'endroit où l'on se trouve dans le menu
 * @param tabBouton Un tableau d'entier contenant les indices correspondant aux boutons de la page du menu sélectionné
 * @param bouton_choisi Un entier. En faisant tabBouton[bouton_choisi], on obtient l'indice du bouton qui est actuellement sélectionné
 */
void aff_menu(position_menu * pos, int tabBouton[], int bouton_choisi);

/**
 * @brief Affiche la page d'accueil du menu en mettant le bouton sélectionné en couleur
 * @param tabBouton Un tableau d'entier contenant les indices correspondant aux boutons de la page d'accueil du menu
 * @param bouton_choisi Un entier. En faisant tabBouton[bouton_choisi], on obtient l'indice du bouton qui est actuellement sélectionné 
 */
void affiche_menu_accueil(int tabBouton[], int bouton_choisi);

/**
 * @brief Affiche la partie rejoindre du menu
 */
void affiche_rejoindre(void);

/**
    @brief Enlève toutes les textures présentes sur l'écran et met l'arrière plan du menu en fond
  * 
*/
void clear_ecran();


/**
  * @brief Ajoute un personnage dans la liste des personnages à sélectionner
  * @param nom Le nom du personnage qu'on veut ajouter
  */
void ajout_personnage(char * nom);


/**
  * @brief Passe au personnage suivant en changeant l'indice courange du tableau de personnages. Fonctionne circulairement 
  */
void suivant(int * tab_bouton);

/**
  * @brief Passe au personnage précédent en changeant l'indice courange du tableau de personnages. Fonctionne circulairement 
  */
void precedent(int * tab_bouton);

/**
  * @brief Créée une SDL_Texture à partir du chemin vers une image
  * @param chemin Le chemin vers l'image que l'on veut créer
  * @return Renvoie une SDL_Texture correspondant à l'image passée en paramètre
  */
SDL_Texture * creer_texture(char * chemin);

/**
  * @brief Renvoie le chemin du fichier en fonctiondu personnage choisi par l'utilisateur
  * @return Renvoie une chaîne de caractères correspondant au chemin vers le bon fichier 
  */
char * chemin_perso();
 
/**
  * @brief Détruit une texture correspondant à une image 
  * @param indice L'indice de la texture du tableau d'images que l'on veut détruire
  */
void detruit_img(int indice);


/**
 * @brief Met à jour le texte_t en paramètre pour que sa nouvelle chaîne de caractère soit le deuxième paramètre
 * @param texte Un pointeur sur texte_t qui va être modifié si le nouveau texte est différent de l'actuel
 * @param nouveau Une chaîne de caractère qui sera affichée à la place de l'ancienne 
 */
void maj_texte(texte_t *texte, char *nouveau);

/**
  * @brief Créée une SDL_Texture de type texte en blanc avec le texte passé en paramètre et la stocke dans le tableau de texte_t
  * @param texte Le tableau de texte_t où sont stockées toutes les textures de type texte
  * @param txt Le texte que l'on veut créer
  */
void creer_texte(texte_t * texte, char * txt);

/**
  * @brief Créée une SDL_Texture de type texte en rouge avec le texte passé en paramètre et la stocke dans le tableau de texte_t
  * @param texte Le tableau de texte_t où sont stockées toutes les textures de type texte
  * @param txt Le texte que l'on veut créer
  */
void creer_texte_rouge(texte_t * texte, char * txt);

/**
  * @brief Créée une SDL_Texture avec le chemin vers l'image passé en paramètre et la stocke dans le tableau de img_t
  * @param image Le tableau de texte_t où sont stockées toutes les textures de type texte
  * @param nomfich Le chemin vers l'image que l'on veut créer
  */
void creer_image(img_t * image, char * nomFich);

 /**
  * @brief Fonction qui appelle toutes les précédentes pour créer le menu fonctionnel. Boucle principale de gestion d'événements SDL pour gérer les interractions avec l'utilisateur
  * @param classe Sert à renvoyer la classe choisie par le joueur
  * @return Renvoie -1 si on quitte le menu avec echap ; 0 si on joue au jeu ; 1 si on est juste serveur ; 2 si on est serveur et joueur en même temps
  */
int menu(char *classe);