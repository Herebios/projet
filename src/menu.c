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

/*
compilation :
gcc menu.c -o menu -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
*/

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *surface = NULL;
TTF_Font *police = NULL;
Mix_Music *musique = NULL;


typedef struct {
    SDL_Rect posBoutonFen;
    SDL_Texture * texture;
}img_t;

typedef struct {
    SDL_Rect posTexte;
    SDL_Texture * message;
}texte_t;

int nbCarJoueur = 0; //indice des lettres à ajouter lorsqu'on clique sur le clavier
int volume = 100; 
int nb_img = 0; //nombre de textures cliquables crées
int nb_texte = 0; //nombre de texture texte crées
int nb_perso_ajoutes = 0; //nombre de personnages ajoutés avec la fonction ajout_personnage()
int actuel = 0; //pour se déplacer avec les flèches dans la liste des personnages à choisir


char cheminPolice[] = "../include/Go-Regular.ttf"; 
char nomJoueur[NB_MAX_CAR_JOUEUR + 1] = ""; //nom saisi par l'utilisateur
char nomJeu[] = "BAD'DOS 4EVER";
char cheminMusique[] = "../include/musiqueMenu.ogg";
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
void creer_menu(void);
void maj_texte(int, char *);
void maj_perso_actuel();
void maj_affichage(SDL_Texture *);
void ajout_personnage(char *);
void suivant(void);
void precedent(void);
SDL_Texture * creer_texture(char *);
char * chemin_perso(void);
void detruit_tout(void);
void detruit_img(int);
void detruit_texte(int);
void creer_texte(texte_t *, char *);
void creer_image(img_t *, char *);
void afficher_texte(void);
void afficher_image(void);
void sauv_param(void);
void charge_param(void);
void modif_volume(void);
void inverse_img_vol(int);
void creer_toutes_images(char **, int);



void menu(void);



void end(int nb){
    //temporaire, existe déjà dans main.c
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

void init_sdl(){
    /*pareil que la fonction end()*/
    if (SDL_Init(SDL_INIT_VIDEO) || !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) end(1);
    
    window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1080, 1080, SDL_WINDOW_SHOWN);
    if (!window) end(2);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) end(3);
}

void creer_menu(){
/*
céée toutes les textures pour l'affichage de base du menu
*/
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
    //si le nom du joueur n'est pas chargé, on affiche "entrez votre nom"
    if(!strcmp(nomJoueur, ""))
        creer_texte(tab_texte + 5, "Entrez votre nom"); //texte nom du joueur
    else 
        creer_texte(tab_texte + 5, nomJoueur); //texte nom du joueur
}

void maj_texte(int indice, char * nouvTxt){
/*
met à jour une texture créée à base de texte
en détruisant la précédente et en recréant une nouvelle 
avec un texte différent

Fonction utilisée pour changer l'affichage du nom du
personnage sélectionné
*/
    SDL_DestroyTexture(tab_texte[indice].message);
    creer_texte(&tab_texte[indice], nouvTxt);
    nb_texte--;
}

void maj_perso_actuel(){
/*
met à jour l'affichage du menu lorsqu'une flèche est cliquée pour avoir le nom du personnage sélectionné ainsi qu'une 
image correspondantre d'affiché
*/
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

void maj_affichage(SDL_Texture * backgroundTexture){
/*
met à jour l'affichage à l'écran : affichage l'image de fond et tous les textes et images chargées
*/
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    afficher_image();
    afficher_texte();
    SDL_RenderPresent(renderer);
}

void ajout_personnage(char * nom){
/*
ajoute un personnage dans la liste des personnages
incrémente le nombre de personnages pour qu'il soit tout le temps à jour
incrémente l'indice courant pour ne pas écraser le nom des personnages déja ajoutés
*/
    tab_perso[nb_perso_ajoutes] = nom;
    nb_perso_ajoutes++;
}

void suivant(){
/*
change l'indice courant du tableau tab_perso pour aller au suivant
fonctionne circulairement : on revient au début si on dépasse la fin du tableau
Appelle ensuite la fonction qui met à jour l'affichage
*/
    if(actuel < nb_perso_ajoutes - 1) actuel++;
    else actuel = 0; 
    maj_perso_actuel();
}

void precedent(){
/*
change l'indice courant du tableau tab_perso pour aller au precedent
fonctionne circulairement : on revient à la fin si on arrive avant le début du tableau début
Appelle ensuite la fonction qui met à jour l'affichage
*/
    if (actuel > 0) actuel--;
    else actuel = nb_perso_ajoutes - 1;
    maj_perso_actuel();
}

SDL_Texture * creer_texture(char * chemin){
/*
créée une texture à partir du chemin vers une image
renvoie un pointeur sur cette texture
*/
	surface = IMG_Load(chemin);
	if(!surface) end(20);
    SDL_Texture * nouv_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(!nouv_texture) end(5);
	return nouv_texture;
}

char * chemin_perso(){
/*
renvoie le chemin du fichier correspondant au perso actuel choisi
*/
    switch(actuel){
        case 0:
            return "../img/Characters/mage/Face.png";
        case 1:
            return "../img/Characters/ninja/Face.png";
        case 2:
            return "../img/Characters/vampire/Face.png";
        default:
            end(12);
    }
}

void detruit_tout(){
/*
detruit tous les textes et images présentes sur l'écran
*/
    while(nb_texte > 0){
        detruit_texte(0);
    }
    while(nb_img > 0){
        detruit_img(0);
    }
}

void detruit_img(int indice){
/*
detruit une SDL_Texture dans la structure image passée en paramètre
*/
    if (tab_img[indice].texture) {
        SDL_DestroyTexture(tab_img[indice].texture);
        tab_img[indice].texture = NULL;   

        for(int i = indice ; i < nb_img ; i++){
            tab_img[i] = tab_img[i + 1];
        }    
        nb_img--;
    }
}

void detruit_texte(int indice){
/*
detruit une SDL_Texture dans la structure texte passée en paramètre
*/
    if(tab_texte[indice].message){
        SDL_DestroyTexture(tab_texte[indice].message);
        tab_texte[indice].message = NULL;

        for(int i = indice ; i < nb_texte ; i++){
            tab_texte[i] = tab_texte[i + 1];
        }
        nb_texte--;
    }
}

void creer_texte(texte_t * texte, char * txt){
/*
créée une texture de type texte avec la string passée en paramètre et la
stocke dans la structure texte_t dans le champ message
*/
    surface = TTF_RenderUTF8_Blended(police, txt, couleurBlanche);
    if(!surface) end(10);

    texte->message = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); 
    nb_texte++;
}

void creer_image(img_t * image, char * nomFich){
/*
créée une texture à partir du chemin vers une image, le stocke dans le champ texture de la structure img_t
*/
    image->texture = creer_texture(nomFich);
    if(!image->texture) end(5);
    nb_img++;
}

void afficher_texte(){
/*
affiche toutes les textures texte chargées
*/
    for(int i = 0 ; i < nb_texte ; i++){
        SDL_RenderCopy(renderer, tab_texte[i].message, NULL, &tab_texte[i].posTexte);
    }
}

void afficher_image(){
/*
affiche toutes les textures boutons chargées
*/
    for(int i = 0 ; i < nb_img ; i++){
        SDL_RenderCopy(renderer, tab_img[i].texture, NULL, &tab_img[i].posBoutonFen);  
    }
}

void sauv_param(){
/*
sauvegarde dans le fichier sauvegarde.txt (dans include) le volume et le personnage actuel choisi par l'utilisateur
*/
    FILE * fichier = fopen(cheminParamTxt, "w");
    fprintf(fichier, "%d\n%d\n%s", actuel, volume, nomJoueur);
    fclose(fichier);
}

void charge_param(){
/*
charge les paramètres sauvegardés dans le fichier sauvegarde.txt (dans include)
*/
    FILE * fichier = fopen(cheminParamTxt, "r");
    if(fichier){
        fscanf(fichier, "%d %d %s", &actuel, &volume, nomJoueur);
        fclose(fichier);
    }
    else printf("Fichier %s introuvable\n", cheminParamTxt);
    
}

void modif_volume(){
/*
modifie l'affichage de la valeur du volume lorsque l'on clique sur le bouton + ou -
*/
    snprintf(valVolume, sizeof(valVolume), "%d", volume);
    detruit_texte(5);
    tab_texte[5] = (texte_t) {(SDL_Rect)(SDL_Rect){X_BOUTON_PARAM + W_BOUTON_PARAM / 2 + 100, 850, 150, H_BOUTON_PARAM / 2}, NULL};                        
    Mix_VolumeMusic(volume);
    creer_texte(tab_texte + 5, valVolume);
    detruit_img(10);
    tab_img[10] = (img_t) {(SDL_Rect){W_BOUTON_PARAM / 4 + 10, 845, H_BOUTON_PARAM - 70, H_BOUTON_PARAM - 60}, NULL};
    if(volume)
        creer_image(tab_img + 10, "../img/Boutons/boutonVolumeOn.png");
    
    else 
        creer_image(tab_img + 10, "../img/Boutons/boutonVolumeOff.png");
}

void inverse_img_vol(int volumeOn){
    detruit_img(10);
    tab_img[10] = (img_t) {(SDL_Rect){W_BOUTON_PARAM / 4 + 10, 845, H_BOUTON_PARAM - 70, H_BOUTON_PARAM - 60}, NULL};
    if(volumeOn){
        creer_image(tab_img + 10, "../img/Boutons/boutonVolumeOff.png");
        volume = 0;
    }
    else{
        creer_image(tab_img + 10, "../img/Boutons/boutonVolumeOn.png");
        volume = 100;
    }
}

void creer_toutes_images(char * tab[], int nbElm){
    for(int i = 0 ; i < nbElm ; i++){
        creer_image(tab_img + i, tab[i]);
    }
}

void creer_tous_textes(char * tab[], int nbElm){
    for(int i = 0 ; i < nbElm ; i++){
        creer_texte(tab_texte + 1, tab[i]);
    }
}


void menu(){
    init_sdl();
    TTF_Init();
    SDL_Init(SDL_INIT_AUDIO);
    //lance la musique dans le menu
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    musique = Mix_LoadMUS(cheminMusique);

    if(!musique){
        printf("Impossible d'ouvrir la musique %s\n", cheminMusique);
        end(100);
    }
    Mix_VolumeMusic(volume);
    Mix_PlayMusic(musique, -1);
    

    police = TTF_OpenFont(cheminPolice, 100);
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
    int dansJouer = 0;
    int sortieMenu = 0;
    int volumeOn = 1;
    int modifNom;

    while(!sortieMenu){
        while(SDL_PollEvent(&event)){
            modifNom = 0; //vaut 1 lorsqu'une touche alphanumérique est appuyée
            //saisie du nom du joueur
            if(event.type == SDL_KEYDOWN){
                SDL_Keycode touche = event.key.keysym.sym;
                //si c'est a-z ou 1-9
                if (nbCarJoueur < NB_MAX_CAR_JOUEUR && ((touche >= SDLK_a && touche <= SDLK_z) || (touche >= SDLK_0 && touche <= SDLK_9))) {
                    nomJoueur[nbCarJoueur++] = (char)touche;
                    nomJoueur[nbCarJoueur] = '\0';
                    modifNom = 1;
                }
                //suppression d'un caractère
                else if(touche == SDLK_BACKSPACE){
                    if(nbCarJoueur >= 1){
                        nomJoueur[--nbCarJoueur] = '\0';
                        modifNom = 1;
                    }
                    else if(nbCarJoueur == 1){
                        nomJoueur[--nbCarJoueur] = '\0';
                        modifNom = 1;
                    }                    
                }
                //maj du nom affiché à l'écran
                if(modifNom){
                    tab_texte[5] = (texte_t) {(SDL_Rect){1250, 100, 600, 250 }, NULL};
                    detruit_texte(5);
                    if(nbCarJoueur != 0)
                        creer_texte(tab_texte + 5, nomJoueur);
                        nb_texte--;
                    maj_affichage(backgroundTexture);
                }
            }
            
            else if(event.type == SDL_MOUSEBUTTONDOWN){
                SDL_Point point = {event.button.x, event.button.y};        

                //
                if(dansJouer){
                    if(SDL_PointInRect(&point, &tab_img[0].posBoutonFen)){
                        dansJouer = 0;
                        sortieMenu = 1;
                    }

                }


                //est-on dans l'option paramètre ?
                else if(dansParam){
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
                            volume += 10;
                            modif_volume();
                        }
                    }
                    //volume -
                    else if(SDL_PointInRect(&point, &tab_img[7].posBoutonFen)){
                        if(volume > 0) {
                            volume -= 10;
                            modif_volume();
                        }
                    }
                    //inverse le son en fonction en cliquant l'image de son coupé ou non
                    else if(SDL_PointInRect(&point, &tab_img[9].posBoutonFen)){
                        inverse_img_vol(volumeOn);
                        volumeOn = !volumeOn;
                        modif_volume();                  
                    }
                }
                else{
                    //bouton quitter ?            
                    if(SDL_PointInRect(&point, &tab_img[2].posBoutonFen)){
                        sortieMenu = 1;
                    }
                    //bouton jouer ?
                    if(SDL_PointInRect(&point, &tab_img[0].posBoutonFen)){
                        printf("jouer\n");
                        dansJouer = 1;
                        detruit_tout();               

                        tab_img[0] = (img_t) {(SDL_Rect){X_BOUTON_PARAM, 200, W_BOUTON_PARAM, H_BOUTON_PARAM}, NULL};
                        tab_img[1] = (img_t) {(SDL_Rect){X_BOUTON_PARAM, 500, W_BOUTON_PARAM, H_BOUTON_PARAM}, NULL};

                        creer_image(tab_img, "../img/Boutons/boutonMenuLargeCarre.png");  
                        creer_image(tab_img  + 1, "../img/Boutons/boutonMenuLargeCarre.png");  

                               
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
                        tab_img[9] = (img_t) {(SDL_Rect){W_BOUTON_PARAM / 4 - 15, 825, H_BOUTON_PARAM - 15, H_BOUTON_PARAM - 15}, NULL};
                        tab_img[10] = (img_t) {(SDL_Rect){W_BOUTON_PARAM / 4 + 10, 845, H_BOUTON_PARAM - 70, H_BOUTON_PARAM - 60}, NULL};
                        
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
                        
                        
                        char * cheminTexte[] = {"Sauvegarder", "Charger", "Paramètres", "Volume", valVolume};
                        char * cheminImg[] = {"../img/Boutons/boutonMenuRond.png",
                                            "../img/Boutons/boutonRetour.png",
                                            "../img/Boutons/boutonMenuLargeCarre.png",
                                            "../img/Boutons/boutonMenuLargeCarre.png",
                                            "../img/Boutons/boutonMenuLargeCarre.png",
                                            "../img/Boutons/boutonMenuCarre.png",
                                            "../img/Boutons/boutonPlus.png",
                                            "../img/Boutons/boutonMenuCarre.png",
                                            "../img/Boutons/boutonMoins.png",
                                            "../img/Boutons/boutonMenuRond.png"};
                        
                        creer_toutes_images(cheminImg, 10);
                        if(volume) 
                            creer_image(tab_img + 10, "../img/Boutons/boutonVolumeOn.png"); 
                        else
                            creer_image(tab_img + 10, "../img/Boutons/boutonVolumeOff.png"); 
                        
                        /*
                        creer_texte(tab_texte, "Sauvegarder");
                        creer_texte(tab_texte + 1, "Paramètres");
                        creer_texte(tab_texte + 2, "Charger");
                        creer_texte(tab_texte + 3, "Paramètres");
                        creer_texte(tab_texte + 4, "Volume");
                        creer_texte(tab_texte + 5, valVolume);
                        */
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
        }
        SDL_Delay(10);
    }
    SDL_DestroyTexture(backgroundTexture);
    Mix_FreeMusic(musique);
    Mix_CloseAudio();
}

int main(void){
    menu();
    end(0);
    return 0;
}
