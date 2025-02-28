/**
 * @file objets.h
 * @author nathan
 * @brief déclaration des types permettants de créer les objets equipables et de mettre a jour les stats des persos
 */

#define NB_OBJETS 34
#define PERSO_OBJETS_MAX 5

typedef enum {commun, rare, epique, legendaire} rarete_t;

typedef struct {
    float valeur;
    int priority;
} prio_t;

typedef struct {
    char * nom;//permet de trouver la texture
    rarete_t rarete;
	objetPrio_t vie;
	objetPrio_t force;
	objetPrio_t magie;
	objetPrio_t speed;
} objet_t;



/**
 * @brief Fonction qui permet de créer un nouvel objet
 * @param objet pointeur sur l'objet à créer
 * @param nomObjet nom de l'objet à créer
 * @param raretee raretée de l'objet à créer
 * @param structMagie structure contenant les modification de magie de l'objet
 * @param structForce structure contenant les modification de force de l'objet
 * @param structSoin structure contenant les modification de soin de l'objet
 * @param structmoveSpeed structure contenant les modification de vitesse de déplacement de l'objet
 */
void creer_objet(t_objet * objet, char * nomObjet, t_raretee raretee, t_objetPrio structMagie, t_objetPrio structForce, t_objetPrio structSoin, t_objetPrio structmoveSpeed);

/**
 * @brief Fonction qui permet d'afficher les champs d'un objet en console
 * @param objet pointeur sur l'objet à afficher
 */
void affiche_1_objet(t_objet * objet);

/**
 * @brief Fonction qui permet de créer les statistiques d'un perso
 * @param perso pointeur sur la structure à afficher
 * @param nom nom du personnage
 * @param magie magie de base du perso
 * @param force forcede base du perso
 * @param pv points de vie de base du perso
 * @param vitesse vitesse de base du perso
 */
void creer_stats_perso(t_statsPerso * perso, char * nom, float magie, float force, int pv, int vitesse);

/**
 * @brief Fonction qui met a jour les stats d'un personnage en fonction des ses objets
 * @param perso pointeur sur la structure à mettre à jour
 */
void udpdate_stats(t_statsPerso * perso);

/**
 * @brief Fonction qui ajoute un objet à l'inventaire d'un personnage
 * @param perso pointeur sur la structure à qui on ajoute un objet
 * @param objetAjoute l'objet que l'on veut ajouter
 */
void nouvel_objet(t_statsPerso * perso, t_objet objetAjoute);

/**
 * @brief Fonction qui retire un objet à l'inventaire, la fonction retire l'objet d'indice "positionInventaire" (le premier élément de l'inventaire est l'indice 1)
 * @param perso pointeur sur la structure à qui on retire un objet
 * @param positionInventaire l'indice de l'objet que l'on veut retirer (l'indexation commence par 1 et non 0)
 */
void retirer_objet(t_statsPerso * perso, int positionInventaire);

/**
 * @brief Fonction qui affiche tous les objets d'un joueur 
 * @param perso pointeur sur la structure à qui on retire un objet
 */
void afficher_objets_perso(t_statsPerso * perso);
