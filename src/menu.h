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


#define IMG_X 400
#define IMG_H 150
#define IMG_W 400
#define X_BOUTON_PARAM 600
#define W_BOUTON_PARAM 700
#define H_BOUTON_PARAM 200
#define H_FLECHE 920
#define NB_MAX_IMG 15
#define NB_MAX_TEXTE 10
#define NB_MAX_PERSO 10
#define NB_MAX_CAR_JOUEUR 20




typedef struct {
    SDL_Rect posBoutonFen; ///<coordonnées x, y et hauteur et largeur de l'image dans la fenêtre
    SDL_Texture * texture; ///<texture de l'image
}img_t;

typedef struct {
    SDL_Rect posTexte; ///<coordonnées x, y et hauteur et largeur du texte dans la fenêtre
    SDL_Texture * message; ///<texture du texte
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
 * @brief Créer le menu de base avec toutes les textures nécessaires
 */
void creer_menu(void);

/**
 * @brief met à jour une texture de texte en détruisant la précédente et en recréant une nouvelle avec un texte différent
 * @param indice L'indice de la texture du tableau de texte que l'on veut détruire
 * @param nouvtxt La nouvelle chaîne de caractères qui remplacera celle d'avant
 */
void maj_texte(int indice, char * nouvTxt);

 /**
  * @brief met à jour l'affichage du menu lorsqu'une flèche est cliquée pour avoir le nom du personnage sélectionné ainsi qu'une image correspondantre d'affiché
  */
void maj_perso_actuel(void);

/**
 * @brief met à jour l'affichage à l'écran : affichage l'image de fond et tous les textes et images chargées 
 */
void maj_affichage(void);

/**
 * @brief ajoute un personnage dans la liste des personnages à sélectionner
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
 * @brief renvoie le chemin du fichier en fonctiondu personnage choisi par l'utilisateur
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
 * @brief créée une SDL_Texture de type texte avec le texte passé en paramètre et la stocke dans le tableau de texte_t
 * @param texte Le tableau de texte_t où sont stockées toutes les textures de type texte
 * @param txt Le texte que l'on veut créer
 */
void creer_texte(texte_t * texte, char * txt);

/**
 * @brief créée une SDL_Texture avec le chemin vers l'image passé en paramètre et la stocke dans le tableau de img_t
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
 * @brief Sauvegarde dans le fichier sauvegarde.txt (dans le dossier include) le volume, le personnage et le nom choisi par l'utilisateur
 */
void sauv_param(void);

/**
 * @brief Charge les paramètres sauvegardés dans sauvegarde.txt (dans le dossier include)
 */
void charge_param(void);

/**
 * @brief Modifie l'affichage de la valeur du volume lorsque l'on clique sur le bouton + ou -
 */
void modif_volume(void);

/**
 * @brief Met la valeur du volume soit à 0 soit à 100 en fonction de la valeur passée en paramètre
 * @param volumeOn La valeur du volume lorsque l'utilisateur clique sur le bouton couper le son dans les paramètres
 */
void inverse_img_vol(int volumeOn);

/**
 * @brief Créer toutes les images à partir d'un tableau où sont stockés tous les chemins vers les images
 * @param tab Le tableau de char * qui contient les chemins vers les images que l'on veut créer
 * @param nbElm le nombre d'images que l'on veut créer (doit être égal au nombre de chemins dans tab)
 */
void creer_toutes_images(char * tab[], int nbElm);

/**
 * @brief Créer tous les textes à partir d'un tableau où sont stockés tous les textes que l'on veut afficher
 * @param tab Le tableau de char * qui contient les textes que l'on doit afficher
 * @param nbElm le nombre de textes que l'on veut créer (doit être égal au nombre de texte dans tab)
 */
void creer_tous_textes(char * tab[], int nbElm);

/**
 * @brief Met à jour l'affichage du nom du joueur à chaque caractère saisi par l'utilisateur en détruisant et recréant la texture de texte
 */
void modif_nom(void);

/**
 * @brief Fonction qui appelle toutes les précédentes pour créer le menu fonctionnel. Boucle principale de gestion d'événements SDL pour gérer les interractions avecv l'utilisateur
 */
void menu(void);