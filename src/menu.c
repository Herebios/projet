#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>



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
#define MAX_CAR_JOUEUR 20



/*
compilation :
gcc menu.c -o menu -lSDL2 -lSDL2_image -lSDL2_ttf
*/


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *surface = NULL;
TTF_Font *police;

typedef struct {
    SDL_Rect posBoutonFen;
    SDL_Texture * texture;
}img_t;

typedef struct {
    SDL_Rect posTexte;
    SDL_Texture * message;
}texte_t;


int nbCarJoueur = 0;
int volume = 100; 
int nb_img = 0; //nombre de textures cliquables crées
int nb_texte = 0; //nombre de texture texte crées
int nb_perso_ajoutes = 0; //nombre de personnages ajoutés avec la fonction ajout_personnage()
int actuel = 0; //pour se déplacer avec les flèches dans la liste des personnages à choisir


char nomJoueur[MAX_CAR_JOUEUR + 1] = ""; //nom saisi par l'utilisateur
char nomJeu[] = "BAD'DOS 4EVER";
char cheminParamTxt[] = "../include/sauvegarde.txt";
char valVolume[4] = "100"; //sert à convertir la valeur du volume pour l'afficher

char * tab_perso[NB_MAX_PERSO]; //liste des personnages disponibles à choisir
img_t tab_img[NB_MAX_IMG]; //tableau de textures images
texte_t tab_texte[NB_MAX_TEXTE];//tableau de textures texte

//couleurs sdl
SDL_Color couleurBlanche = { 255, 255, 255, 255 };
SDL_Color couleurNoire = { 0, 0, 0, 255 };

//A METTRE DANS .h
void end(int);
void init_sdl(void);
void maj_texte(int, char *);
void maj_affichage(SDL_Texture *);
void maj_perso_actuel();
void suivant(void);
void precedent(void);
void ajout_personnage(char *);
void creer_texte(texte_t *, char *);
void creer_image(img_t *, char *);
void afficher_texte(void);
void afficher_image(void);
void detruit_img(int);
void detruit_texte(int);
void detruit_tout(void);
void creer_menu(void);
void sauv_param(void);
void charge_param(void);
void modif_volume();
SDL_Texture * creer_texture(char *);
char * chemin_perso();



//temporaire, existe déjà dans main.c
void end(int nb){
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    for(int i = 0 ; i < nb_img ; i++){
        SDL_DestroyTexture(tab_img[i].texture);
    }
    for(int i = 0 ; i < nb_texte ; i++){
        SDL_DestroyTexture(tab_texte[i].message);
    }
	if (police)
		TTF_CloseFont(police);

	TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    if(nb) exit(nb);
}

/*pareil que la fonction end()*/
void init_sdl(){
    if (SDL_Init(SDL_INIT_VIDEO) || !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) end(1);
    
    window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1080, 1080, SDL_WINDOW_SHOWN);
    if (!window) end(2);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) end(3);
}

/*
céée toutes les textures pour l'affichage de base du menu
*/
void creer_menu(){
    detruit_tout();
    
    //boutons Jouer, Paramètres et Quitter
    tab_img[0] = (img_t) {(SDL_Rect){IMG_X, 400, IMG_W, IMG_H}, NULL};
    tab_img[1] = (img_t) {(SDL_Rect){IMG_X, 600, IMG_W, IMG_H}, NULL};
    tab_img[2] = (img_t) {(SDL_Rect){IMG_X, 800, IMG_W, IMG_H}, NULL};
    //fleches de selection des personnages
    tab_img[3] = (img_t) {(SDL_Rect){1350, H_FLECHE, IMG_W / 2, IMG_H }, NULL};
    tab_img[4] = (img_t) {(SDL_Rect){1700, H_FLECHE, IMG_W / 2, IMG_H }, NULL};
    //perso sélectionné
    tab_img[5] = (img_t) {(SDL_Rect){1500, 660, 250, 250 }, NULL};


    tab_texte[0] = (texte_t) {(SDL_Rect)(SDL_Rect){IMG_X + 50, 410, IMG_W - 100, IMG_H - 40}, NULL};
    tab_texte[1] = (texte_t) {(SDL_Rect){IMG_X + 50, 615, IMG_W - 100, IMG_H - 40}, NULL};
    tab_texte[2] = (texte_t) {(SDL_Rect){IMG_X + 50, 810, IMG_W - 100, IMG_H - 40}, NULL};
    tab_texte[3] = (texte_t) {(SDL_Rect){1450, 550, 300, 100}, NULL};
    tab_texte[4] = (texte_t) {(SDL_Rect){250, 100, 650, 200}, NULL};
    tab_texte[5] = (texte_t) {(SDL_Rect){1250, 100, 600, 250 }, NULL};

    //créations de tous les boutons
    creer_image(tab_img, "../img/Boutons/boutonMenuLarge.png"); //bouton jouer
    creer_image(tab_img + 1, "../img/Boutons/boutonMenuLarge.png"); //bouton paramètres
    creer_image(tab_img + 2, "../img/Boutons/boutonMenuLarge.png"); //bouton quitter
    creer_image(tab_img + 3, "../img/Boutons/flecheGauche.png"); //bouton fleche gauche
    creer_image(tab_img + 4, "../img/Boutons/flecheDroite.png"); //bouton fleche droite
    creer_image(tab_img + 5, chemin_perso()); //image du personnage choisi

    //création de toutes les zones de texte
    creer_texte(tab_texte, "Jouer"); //texte bouton jouer
    creer_texte(tab_texte + 1, "Paramètres"); //texte bouton paramètres
    creer_texte(tab_texte + 2, "Quitter"); //texte bouton quitter
    creer_texte(tab_texte + 3, tab_perso[actuel]); //texte nom du perso actuel
    creer_texte(tab_texte + 4, nomJeu); //texte nom du jeu
    if(!strcmp(nomJoueur, ""))
        creer_texte(tab_texte + 5, "Entrez votre nom"); //texte nom du joueur
    else 
        creer_texte(tab_texte + 5, "test"); //texte nom du joueur

}

/*
met à jour une texture créée à base de texte
en détruisant la précédente et en recréant une nouvelle 
avec un texte différent

Fonction utilisée pour changer l'affichage du nom du
personnage sélectionné
*/
void maj_texte(int indice, char * nouvTxt){
    SDL_DestroyTexture(tab_texte[indice].message);
    creer_texte(&tab_texte[indice], nouvTxt);
    nb_texte--;
}

/*
met à jour l'affichage du menu lorsqu'une flèche est cliquée pour avoir le nom du personnage sélectionné ainsi qu'une 
image correspondantre d'affiché
*/
void maj_perso_actuel(){
    maj_texte(3, tab_perso[actuel]);
    if(tab_img[5].texture){
        SDL_DestroyTexture(tab_img[5].texture);
        tab_img[5].texture = NULL;
    }
    tab_img[5].texture = creer_texture(chemin_perso());
    if (!tab_img[5].texture) {
        end(13);
    }
}

/*
met à jour l'affichage à l'écran : affichage l'image de fond et tous les textes et images chargées
*/
void maj_affichage(SDL_Texture * backgroundTexture){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    afficher_image();
    afficher_texte();
    SDL_RenderPresent(renderer);
}

/*
ajoute un personnage dans la liste des personnages
incrémente le nombre de personnages pour qu'il soit tout le temps à jour
incrémente l'indice courant pour ne pas écraser le nom des personnages déja ajoutés
*/
void ajout_personnage(char * nom){
    tab_perso[nb_perso_ajoutes] = nom;
    nb_perso_ajoutes++;
}

/*
change l'indice courant du tableau tab_perso pour aller au suivant
fonctionne circulairement : on revient au début si on dépasse la fin du tableau
Appelle ensuite la fonction qui met à jour l'affichage
*/
void suivant(){
    if(actuel < nb_perso_ajoutes - 1) actuel++;
    else actuel = 0; 
    maj_perso_actuel();
}

/*
change l'indice courant du tableau tab_perso pour aller au precedent
fonctionne circulairement : on revient à la fin si on arrive avant le début du tableau début
Appelle ensuite la fonction qui met à jour l'affichage
*/
void precedent(){
    if (actuel > 0) actuel--;
    else actuel = nb_perso_ajoutes - 1;
    maj_perso_actuel();
}

/*
créée une texture à partir du chemin vers une image
renvoie un pointeur sur cette texture
*/
SDL_Texture * creer_texture(char * chemin){
	surface = IMG_Load(chemin);
	if(!surface) end(20);
    SDL_Texture * nouv_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(!nouv_texture) end(5);
	return nouv_texture;
}

/*
renvoie le chemin du fichier correspondant au perso actuel choisi
*/
char * chemin_perso(){
    switch(actuel){
        case 0:
            return "../img/Characters/mage/Face.png";
        case 1:
            return "../img/Characters/ninja/ninjaFace.png";
        case 2:
            return "../img/Characters/vampire.png";
        default:
            end(12);
    }
}

/*
detruit tous les textes et images présentes sur l'écran
*/
void detruit_tout(){
    while(nb_texte > 0){
        detruit_texte(0);
    }
    while(nb_img > 0){
        detruit_img(0);
    }
}

/*
detruit une SDL_Texture dans la structure image passée en paramètre
*/
void detruit_img(int indice){
    if (tab_img[indice].texture) {
        SDL_DestroyTexture(tab_img[indice].texture);
        tab_img[indice].texture = NULL;   

        for(int i = indice ; i < nb_img ; i++){
            tab_img[i] = tab_img[i + 1];
        }    
        nb_img--;
    }
}

/*
detruit une SDL_Texture dans la structure texte passée en paramètre
*/
void detruit_texte(int indice){
    if(tab_texte[indice].message){
        SDL_DestroyTexture(tab_texte[indice].message);
        tab_texte[indice].message = NULL;

        for(int i = indice ; i < nb_texte ; i++){
            tab_texte[i] = tab_texte[i + 1];
        }
        nb_texte--;
    }
}

/*
créée une texture de type texte avec la string passée en paramètre et la
stocke dans la structure texte_t dans le champ message
*/
void creer_texte(texte_t * texte, char * txt){
    surface = TTF_RenderUTF8_Blended(police, txt, couleurBlanche);
    if(!surface) end(10);

    texte->message = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); 
    nb_texte++;
}

/*
créée une texture à partir du chemin vers une image, le stocke dans le champ texture de la structure img_t
*/
void creer_image(img_t * image, char * nomFich){
    image->texture = creer_texture(nomFich);
    if(!image->texture) end(5);
    nb_img++;
}

/*
affiche toutes les textures texte chargées
*/
void afficher_texte(){
    for(int i = 0 ; i < nb_texte ; i++){
        SDL_RenderCopy(renderer, tab_texte[i].message, NULL, &tab_texte[i].posTexte);
    }
}

/*
affiche toutes les textures boutons chargées
*/
void afficher_image(){
    for(int i = 0 ; i < nb_img ; i++){
        SDL_RenderCopy(renderer, tab_img[i].texture, NULL, &tab_img[i].posBoutonFen);  
    }
}

/*
sauvegarde dans le fichier sauvegarde.txt (dans include) le volume et le personnage actuel choisi par l'utilisateur
*/
void sauv_param(){
    FILE * fichier = fopen(cheminParamTxt, "w");
    fprintf(fichier, "%d\n%d\n%s", actuel, volume, nomJoueur);
    fclose(fichier);
}

/*
charge les paramètres sauvegardés dans le fichier sauvegarde.txt (dans include)
*/
void charge_param(){
    FILE * fichier = fopen(cheminParamTxt, "r");
    if(fichier){
        fscanf(fichier, "%d %d %s", &actuel, &volume, nomJoueur);
        fclose(fichier);
    }
    else printf("Fichier %s introuvable\n", cheminParamTxt);
    
}

/*
modifie l'affichage de la valeur du volume lorsque l'on clique sur le bouton + ou -
*/
void modif_volume(){
    snprintf(valVolume, sizeof(valVolume), "%d", volume);
    detruit_texte(5);
    tab_texte[5] = (texte_t) {(SDL_Rect)(SDL_Rect){X_BOUTON_PARAM + W_BOUTON_PARAM / 2 + 100, 850, 150, H_BOUTON_PARAM / 2}, NULL};                        

    creer_texte(tab_texte + 5, valVolume);
}

/*
met à jour le nom du joueur saisi
*/

/*
marche pas :/
void gestion_saisie(SDL_Event event){
    if(event.type == SDL_TEXTINPUT){
        if(nbCarJoueur < MAX_CAR_JOUEUR){
            strcat(nomJoueur, event.text.text);
            nbCarJoueur++;
            maj_nom_joueur();
        }
        else if(event.type == SDL_KEYDOWN){
            if (event.key.keysym.sym == SDLK_BACKSPACE && nbCarJoueur > 0) {
                nomJoueur[--nbCarJoueur] = '\0';
                maj_nom_joueur();
            } else if (event.key.keysym.sym == SDLK_RETURN) {
                printf("Nom du joueur validé : %s\n", nomJoueur);
            }
        }
    }
}
*/

void menu(){
    init_sdl();
    TTF_Init();
    SDL_StartTextInput();

    police = TTF_OpenFont("../include/Go-Regular.ttf", 100);
	if (!police) end(6);

    //image de fond
	SDL_Texture * backgroundTexture = creer_texture("../img/imgMenu.png");

    //liste des personnages à sélectionner
    ajout_personnage("mage");
    ajout_personnage("ninja");
    ajout_personnage("vampire");

    //créer les textures du menu
    creer_menu();

    //affiche à l'écran l'image de fond, le nom du jeu, les images et les textes chargés
    maj_affichage(backgroundTexture);                

    SDL_Event event;

    int dansParam = 0;
    int sortieMenu = 0;
    int clic = 0;

    while(!sortieMenu){
        while(SDL_PollEvent(&event)){
            //saisie du nom du joueur
            //gestion_saisie(event);
			
            if(event.type == SDL_MOUSEBUTTONDOWN){
                clic = 1;
                SDL_Point point = {event.button.x, event.button.y};

                                
                //a-t-on cliqué sur paramètre ?
                if(dansParam){
                    //retour menu d'accueil
                    if(SDL_PointInRect(&point, &tab_img[0].posBoutonFen)){
                        creer_menu();
                        dansParam = 0;
                    }
                    //sauvegarder paramètres
                    else if(SDL_PointInRect(&point, &tab_img[2].posBoutonFen)){
                        sauv_param();
                    }   
                    //charger paramètres
                    else if(SDL_PointInRect(&point, &tab_img[3].posBoutonFen)){
                        charge_param();
                        modif_volume();
                        

                    }
                    //volume +
                    else if(SDL_PointInRect(&point, &tab_img[5].posBoutonFen)){
                        if(volume < 100) {
                            volume++;
                            modif_volume();
                        }
                    }
                    //volume -
                    else if(SDL_PointInRect(&point, &tab_img[7].posBoutonFen)){
                        if(volume > 0) {
                            volume--;
                            modif_volume();
                        }
                    }
                }
                else{
                    //bouton quitter ?            
                    if(SDL_PointInRect(&point, &tab_img[2].posBoutonFen)){
                        sortieMenu = 1;
                    }

                    //bouton paramètre ?
                    else if(SDL_PointInRect(&point, &tab_img[1].posBoutonFen)){
                        dansParam = 1;
                        detruit_tout();
                        
                        //ajout bouton retour (img bois + img retour)
                        tab_img[0] = (img_t) {(SDL_Rect){50, 50, 200, 200}, NULL};
                        tab_img[1] = (img_t) {(SDL_Rect){88, 88, 120, 120}, NULL};
                        //boutons de charge et de sauvegarde des paramètres
                        tab_img[2] = (img_t) {(SDL_Rect){X_BOUTON_PARAM, 200, W_BOUTON_PARAM, H_BOUTON_PARAM}, NULL};
                        tab_img[3] = (img_t) {(SDL_Rect){X_BOUTON_PARAM, 500, W_BOUTON_PARAM, H_BOUTON_PARAM}, NULL};
                        tab_img[4] = (img_t) {(SDL_Rect){X_BOUTON_PARAM, 800, W_BOUTON_PARAM, H_BOUTON_PARAM}, NULL};
                        //bouton volume plus
                        tab_img[5] = (img_t) {(SDL_Rect){X_BOUTON_PARAM - 175, 825, H_BOUTON_PARAM - 50, H_BOUTON_PARAM - 50}, NULL};
                        tab_img[6] = (img_t) {(SDL_Rect){X_BOUTON_PARAM - 152, 850, H_BOUTON_PARAM - 95, H_BOUTON_PARAM - 100}, NULL};
                        //bouton volume moins
                        tab_img[7] = (img_t) {(SDL_Rect){X_BOUTON_PARAM + W_BOUTON_PARAM + 25, 825, H_BOUTON_PARAM - 50, H_BOUTON_PARAM - 50}, NULL};
                        tab_img[8] = (img_t) {(SDL_Rect){X_BOUTON_PARAM + W_BOUTON_PARAM + 52, 885, H_BOUTON_PARAM - 102, H_BOUTON_PARAM - 175}, NULL};
                        //bouton volume coupé
                        /*
                        tab_img[9] = (img_t) {(SDL_Rect){W_BOUTON_PARAM * 2, 850, H_BOUTON_PARAM - 15, H_BOUTON_PARAM - 15}, NULL};
                        tab_img[10] = (img_t) {(SDL_Rect){W_BOUTON_PARAM * 2 + 10, 860, H_BOUTON_PARAM - 70, H_BOUTON_PARAM - 60}, NULL};
                        */
                        //texte : sauvegarder
                        tab_texte[0] = (texte_t) {(SDL_Rect)(SDL_Rect){X_BOUTON_PARAM + 70, 200, W_BOUTON_PARAM - 150, H_BOUTON_PARAM / 2}, NULL};
                        //texte :paramètre
                        tab_texte[1] = (texte_t) {(SDL_Rect)(SDL_Rect){X_BOUTON_PARAM + 70, 300, W_BOUTON_PARAM - 150, H_BOUTON_PARAM / 2}, NULL};
                        //texte : charger
                        tab_texte[2] = (texte_t) {(SDL_Rect)(SDL_Rect){X_BOUTON_PARAM + 70, 500, W_BOUTON_PARAM - 150, H_BOUTON_PARAM / 2}, NULL};
                        //texte :paramètre
                        tab_texte[3] = (texte_t) {(SDL_Rect)(SDL_Rect){X_BOUTON_PARAM + 70, 600, W_BOUTON_PARAM - 150, H_BOUTON_PARAM / 2}, NULL};
                        //texte : volume
                        tab_texte[4] = (texte_t) {(SDL_Rect)(SDL_Rect){X_BOUTON_PARAM + 70, 850, W_BOUTON_PARAM / 2, H_BOUTON_PARAM / 2}, NULL};     
                        //valeur du volume
                        tab_texte[5] = (texte_t) {(SDL_Rect)(SDL_Rect){X_BOUTON_PARAM + W_BOUTON_PARAM / 2 + 100, 850, 150, H_BOUTON_PARAM / 2}, NULL};                        

                        creer_image(tab_img, "../img/Boutons/boutonMenuRond.png"); 
                        creer_image(tab_img + 1, "../img/Boutons/boutonRetour.png");
                        creer_image(tab_img + 2, "../img/Boutons/boutonMenuLargeCarre.png");  
                        creer_image(tab_img + 3, "../img/Boutons/boutonMenuLargeCarre.png"); 
                        creer_image(tab_img + 4, "../img/Boutons/boutonMenuLargeCarre.png"); 
                        creer_image(tab_img + 5, "../img/Boutons/boutonMenuCarre.png"); 
                        creer_image(tab_img + 6, "../img/Boutons/boutonPlus.png"); 
                        creer_image(tab_img + 7, "../img/Boutons/boutonMenuCarre.png"); 
                        creer_image(tab_img + 8, "../img/Boutons/boutonMoins.png"); 
                        /*
                        creer_image(tab_img + 9, "../img/Boutons/boutonMenuRond.png"); 
                        creer_image(tab_img + 10, "../img/Boutons/boutonVolumeOn.png"); 
                        */

                             
                        creer_texte(tab_texte, "Sauvegarder");
                        creer_texte(tab_texte + 1, "Paramètres");
                        creer_texte(tab_texte + 2, "Charger");
                        creer_texte(tab_texte + 3, "Paramètres");
                        creer_texte(tab_texte + 4, "Volume");
                        creer_texte(tab_texte + 5, valVolume);
                    }
                    //flèche gauche ?
                    else if(SDL_PointInRect(&point, &tab_img[3].posBoutonFen) && !dansParam){
                        precedent();                     
                    }

                    //flèche droite ?
                    else if(SDL_PointInRect(&point, &tab_img[4].posBoutonFen) && !dansParam){
                        suivant();
                    }
                }                
                maj_affichage(backgroundTexture);                   
            }
            else{
                clic = 0;
            }
        }
        SDL_Delay(10);
    }
    SDL_StopTextInput();
    SDL_DestroyTexture(backgroundTexture);
}

int main(void){
    menu();
    end(0);
    return 0;
}
