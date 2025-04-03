/**
 * @file inventaire.h
 * @author Ilann
 * @brief fonctions d'affichage de l'inventaire d'un joueur
 */


/**
 * @brief Renvoie le chemin vers le fichier de l'image correspondant à l'objet
 * @param obj Le pointeur sur objet
 * @return Une chaîne de caractères
 */
char * chemin_objet(objet_t * obj);

/**
 * @brief Affiche l'inventaire d'un joueur en bas de son écran
 * @param perso Un personnage
 * @param renderer Pour l'affichage SDL
 */
void show_inventaire(SDL_Renderer * renderer, perso_t * perso);