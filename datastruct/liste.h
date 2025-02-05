typedef struct element_s {
	void * ptr;
	struct element_s *prec;
	struct element_s *suiv;
} element;

typedef struct {
	element *drapeau;
	element *ec;
} liste;

liste * creer_liste();
void detruire_liste(liste **l);

int liste_vide(liste *l);
int hors_liste(liste *l);
void en_tete(liste *l);
void en_queue(liste *l);
void suivant(liste *l);
void precedent(liste *l);

void * get(liste *l);
void set(liste *l, void * data, size_t size);
void supprimer(liste *l);

void ajout_droit(liste *l, void * data, size_t size);
void ajout_gauche(liste *l, void * data, size_t size);
void ajout_debut(liste *l, void * data, size_t size);
void ajout_fin(liste *l, void * data, size_t size);

int taille_liste(liste *l);

