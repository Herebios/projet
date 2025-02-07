#define NB_OBJETS 34
#define NB_OBJETS_PAR_PERSO 5

typedef enum {commun, rare, epique, legendaire} t_raretee;

typedef struct {
    float valeur;
    int priority;
} t_objetPrio;

typedef struct {
    char * nom;
    t_raretee raretee;
    t_objetPrio magie;
    t_objetPrio force;
    t_objetPrio soin;
    t_objetPrio moveSpeed;
} t_objet;

typedef struct {
    char * nom;
    float magie;
    float force;
    int pv;
    int vitesse;
    t_objet listeObj[NB_OBJETS_PAR_PERSO]; 
} t_statsPerso;
