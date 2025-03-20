/**
\file liste.h
\brief Fonctions de manipulation de listes
*/
typedef struct element_s {
	void * ptr;
	struct element_s *prec;
	struct element_s *suiv;
} element;
/**
\brief structure liste
*/
typedef struct {
	element *drapeau;
	element *ec;
} liste;

/**
\brief créer une liste
\return pointeur sur nouvelle liste
*/
liste * creer_liste();

/**
\brief détruire une liste et tous ses éléments
\param pointeur sur pointeur sur la liste
*/
void detruire_liste(liste **l);

int liste_vide(liste *l);
int hors_liste(liste *l);
void tete_liste(liste *l);
void queue_liste(liste *l);
void suivant_liste(liste *l);
void precedent_liste(liste *l);

void * get_liste(liste *l);
void set_liste(liste *l, void * data, size_t size);

void supprimer_liste(liste *l);
void ajout_droit_liste(liste *l, void * data, size_t size);
void ajout_gauche_liste(liste *l, void * data, size_t size);
void ajout_debut_liste(liste *l, void * data, size_t size);
void ajout_fin_liste(liste *l, void * data, size_t size);

int taille_liste(liste *l);

