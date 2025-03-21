/**
 * @file menu.h
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
 #define NB_MAX_IMG 25
 #define NB_MAX_TEXTE 30
 #define NB_MAX_PERSO 10
 #define NB_MAX_CAR_JOUEUR 20
 #define NB_MAX_CAR_IP 16
 #define REGEXIP "^((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$"
 #define JOUER 0
 #define SERVEUR 1
 #define JOUER_SERVEUR 2



typedef enum {
    MENU_PRINCIPAL, DANS_JOUER, DANS_PARAM, DANS_CREER, DANS_REJOINDRE, SORTIE_MENU
}position_menu;
 
typedef struct {
     SDL_Rect posBoutonFen; ///<Coordonnées x, y et hauteur et largeur de l'image dans la fenêtre
     SDL_Texture * texture; ///<Texture de l'image
}img_t;
 
typedef struct {
     SDL_Rect posTexte; ///<Coordonnées x, y et hauteur et largeur du texte dans la fenêtre
     SDL_Texture * message; ///<Texture du texte
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
 


/**
 * @brief Renvoie un entier 1 ou 0 pour savoir si l'adresse ip rentrée en paramètre est valide
 * @return Un entier
 */

int valider_ip(char *ip);

void end(int nb);
void init_sdl(void);
 
 /**
  * @brief Créée le menu de base avec toutes les textures nécessaires
  */
 void creer_menu(void);
 
 /**
  * @brief Met à jour une texture de texte en détruisant la précédente et en recréant une nouvelle avec un texte différent
  * @param indice L'indice de la texture du tableau de texte que l'on veut détruire
  * @param nouvtxt La nouvelle chaîne de caractères qui remplacera celle d'avant
  */
 void maj_texte(int indice, char * nouvTxt);
 
  /**
   * @brief Met à jour l'affichage du menu lorsqu'une flèche est cliquée pour avoir le nom du personnage sélectionné ainsi qu'une image correspondantre d'affiché
   */
 void maj_perso_actuel(void);
 
 /**
    @brief met à jour l'affichage à l'écran : affichage l'image de fond et supprime toutes les textures qui étaient affichées à l'écran
  * 
*/
 void clear_ecran(void);
 
 /**
  * @brief Ajoute un personnage dans la liste des personnages à sélectionner
  * @param nom Le nom du personnage qu'on veut ajouter
  */
 void ajout_personnage(char * nom);
 
 /**
  * @brief Passe au personnage suivant en changeant l'indice courange du tableau de personnages. Fonctionne circulairement 
  */
 void suivant(void);
 
 /**
  * @brief Passe au personnage précédent en changeant l'indice courange du tableau de personnages. Fonctionne circulairement 
  */
 void precedent(void);
 
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
 char * chemin_perso(void);
 
 /**
  * @brief Détruit une texture correspondant à une image 
  * @param indice L'indice de la texture du tableau d'images que l'on veut détruire
  */
 void detruit_img(int indice);
 
 /**
  * @brief Détruit une texture correspondant à du texte 
  * @param indice L'indice de la texture du tableau de textes que l'on veut détruire
  */
 void detruit_texte(int indice);
 
 /**
  * @brief Détruit tous les textes et les images présentes dans le menu
  */
 void detruit_tout(void);
 
 /**
  * @brief Créée une SDL_Texture de type texte avec le texte passé en paramètre et la stocke dans le tableau de texte_t
  * @param texte Le tableau de texte_t où sont stockées toutes les textures de type texte
  * @param txt Le texte que l'on veut créer
  */
 void creer_texte(texte_t * texte, char * txt);
 
 /**
  * @brief Créée une SDL_Texture avec le chemin vers l'image passé en paramètre et la stocke dans le tableau de img_t
  * @param image Le tableau de texte_t où sont stockées toutes les textures de type texte
  * @param nomfich Le chemin vers l'image que l'on veut créer
  */
 void creer_image(img_t * image, char * nomfich);
 
 /**
  * @brief Affiche toutes les textures texte chargées dans le tableau de texte_t
 */
 void afficher_texte(void);
 
 /**
  * @brief Affiche toutes les textures images chargées dans le tableau de img_t
 */
 void afficher_image(void);
 
 /**
  * @brief Met à jour l'affichage du nom du joueur à chaque caractère saisi par l'utilisateur en détruisant et recréant la texture de texte
  */
 void modif_nom(void);
 
 /**
  * @brief Fonction qui appelle toutes les précédentes pour créer le menu fonctionnel. Boucle principale de gestion d'événements SDL pour gérer les interractions avec l'utilisateur
  * @return Renvoie -1 si on quitte le menu avec echap ; 0 si on joue au jeu ; 1 si on est juste serveur ; 2 si on est serveur et joueur en même temps
  */
int menu(char **pseudo, char *classe, char** ipAddress);

/**
 * @brief Permet de mettre à jour l'adresse ip saisie avec les touches du keypad et du clavier normal
 */
void saisie_touche_ip(SDL_Keycode touche, int * nbCar, char * saisie);


void affiche_rejoindre(void);
