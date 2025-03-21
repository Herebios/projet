
#include "menu.h"

/*
compilation :
gcc menu.c -o menu -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer  


PF : adaptation coord, amelioration visuel bouton, doc 
*/


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *surface = NULL;
TTF_Font *police = NULL;
Mix_Music *musique = NULL;
SDL_Texture * backgroundTexture = NULL;

int nbCarJoueur = 0; //indice des lettres à ajouter lorsqu'on clique sur le clavier
int volume = 100; 
int nb_img = 0; //nombre de textures cliquables crées
int nb_texte = 0; //nombre de texture texte crées
int nb_perso_ajoutes = 0; //nombre de personnages ajoutés avec la fonction ajout_personnage()
int actuel = 0; //pour se déplacer avec les flèches dans la liste des personnages à choisir
int nbCarIp = 0; //nombre de caractères lors de la saisie de l'ip par le joueur



char cheminPolice[] = "../include/Go-Regular.ttf"; 
char nomJoueur[NB_MAX_CAR_JOUEUR] = " "; //nom saisi par l'utilisateur
char nomJeu[] = "BAD'DOS 4EVER";
char cheminMusique[] = "../include/musiqueMenu.ogg";
char cheminParamTxt[] = "../include/sauvegarde.txt";
char valVolume[4] = "100"; //sert à convertir la valeur du volume pour l'afficher
char saisieIp[NB_MAX_CAR_IP] = " ";



char * tab_perso[NB_MAX_PERSO]; //liste des personnages disponibles à choisir
img_t tab_img[NB_MAX_IMG]; //tableau de textures images
texte_t tab_texte[NB_MAX_TEXTE];//tableau de textures texte

//couleurs sdl
SDL_Color couleurBlanche = { 255, 255, 255, 255 };
SDL_Color couleurNoire = { 0, 0, 0, 255 };


void end(int nb){
    
    if (renderer){
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
        
    if (window)
        SDL_DestroyWindow(window);
    for(int i = 0 ; i < nb_img ; i++){
        SDL_DestroyTexture(tab_img[i].texture);
    }
    for(int i = 0 ; i < nb_texte ; i++){
        SDL_DestroyTexture(tab_texte[i].message);
    }
	if (police){
		TTF_CloseFont(police);
        police =  NULL;
    }
    if (musique) {
        Mix_FreeMusic(musique);
        musique = NULL;
    }

    Mix_CloseAudio();


	TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    if(nb) exit(nb);
}

void init_sdl(){
    
    if (SDL_Init(SDL_INIT_VIDEO) || !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) end(1);
    
    window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 500, SDL_WINDOW_SHOWN);
    if (!window) end(2);
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) end(3);

    TTF_Init();

    police = TTF_OpenFont(cheminPolice, 100);
	if (!police) end(6);

    SDL_Init(SDL_INIT_AUDIO);


}

int valider_ip(char *ip) {
    regex_t regex;
    int result;

    // Compilation de la regex
    if (regcomp(&regex, REGEXIP, REG_EXTENDED)) {
        fprintf(stderr, "Erreur de compilation de la regex\n");
        return 0;
    }

    result = regexec(&regex, ip, 0, NULL, 0);

    // Libération de la mémoire de la regex
    regfree(&regex);

    // Retourne 1 si l'IP est valide, 0 sinon
    return (result == 0);  
}

void saisie_touche_ip(SDL_Keycode touche, int * nbCar, char * saisie){
    if(*nbCar < NB_MAX_CAR_IP){
        char c = '\0';

        if(((touche >= SDLK_0 && touche <= SDLK_9))){
            c = (char)touche;
        }
        else{
            switch(touche){
                case SDLK_SEMICOLON :
                case SDLK_KP_PERIOD : c = '.'; break;
                case SDLK_KP_0 : c = '0'; break;
                case SDLK_KP_1 : c = '1'; break;
                case SDLK_KP_2 : c = '2'; break;
                case SDLK_KP_3 : c = '3'; break;
                case SDLK_KP_4 : c = '4'; break;
                case SDLK_KP_5 : c = '5'; break;
                case SDLK_KP_6 : c = '6'; break;
                case SDLK_KP_7 : c = '7'; break;
                case SDLK_KP_8 : c = '8'; break;
                case SDLK_KP_9 : c = '9'; break;            
                case SDLK_BACKSPACE : if(*nbCar >= 1) saisie[--(*nbCar)] = ' '; return;
                default : break;
            }

        }
        saisie[(*nbCar)++] = c;
        saisie[*nbCar] = '\0';
    }
}

void affiche_rejoindre(){
    clear_ecran();
    //bouton retour 
    SDL_RenderCopy(renderer, tab_img[6].texture, NULL, &tab_img[6].posBoutonFen);
    SDL_RenderCopy(renderer, tab_img[7].texture, NULL, &tab_img[7].posBoutonFen);  



    SDL_RenderCopy(renderer, tab_img[10].texture, NULL, &tab_img[10].posBoutonFen);   
    SDL_RenderCopy(renderer, tab_img[24].texture, NULL, &tab_img[24].posBoutonFen);   

    SDL_RenderCopy(renderer, tab_texte[15].message, NULL, &tab_texte[15].posTexte);
    SDL_RenderCopy(renderer, tab_texte[22].message, NULL, &tab_texte[22].posTexte);

    
    if(nbCarIp > 0){
        //texte ip
        detruit_texte(21);
        creer_texte(tab_texte + 21, saisieIp);
        SDL_RenderCopy(renderer, tab_texte[21].message, NULL, &tab_texte[21].posTexte);
    }

}

void affiche_menu(){
    clear_ecran();
    //chargement des boutons et textes du menu principal
    for(int i = 0 ; i < 5 ; i++){
        SDL_RenderCopy(renderer, tab_img[i].texture, NULL, &tab_img[i].posBoutonFen);

        if(i != 3) SDL_RenderCopy(renderer, tab_texte[i].message, NULL, &tab_texte[i].posTexte);
    }
    
    maj_perso_actuel();

    
    //si le nom du joueur n'est pas chargé, on affiche "entrez votre nom"
    
    if(nbCarJoueur == 0)
        SDL_RenderCopy(renderer, tab_texte[5].message, NULL, &tab_texte[5].posTexte);
    else{
        detruit_texte(6);
        creer_texte(tab_texte + 6, nomJoueur);
        SDL_RenderCopy(renderer, tab_texte[6].message, NULL, &tab_texte[6].posTexte);
    }
    
    SDL_RenderPresent(renderer);
}

void affiche_param(){
    clear_ecran();
    SDL_RenderCopy(renderer, tab_img[6].texture, NULL, &tab_img[6].posBoutonFen);
    SDL_RenderCopy(renderer, tab_img[7].texture, NULL, &tab_img[7].posBoutonFen);

    for(int i = 11 ; i < 19 ; i++){
        SDL_RenderCopy(renderer, tab_img[i].texture, NULL, &tab_img[i].posBoutonFen);
    } 
    
    for(int i = 9 ; i < 15 ; i++){
        if(i != 14) SDL_RenderCopy(renderer, tab_texte[i].message, NULL, &tab_texte[i].posTexte);
    } 
        
    snprintf(valVolume, sizeof(valVolume), "%d", volume);
    Mix_VolumeMusic(volume);
    detruit_texte(14);
    creer_texte(tab_texte + 14, valVolume);
    SDL_RenderCopy(renderer, tab_texte[14].message, NULL, &tab_texte[14].posTexte);

    if(volume)
        SDL_RenderCopy(renderer, tab_img[19].texture, NULL, &tab_img[19].posBoutonFen);    
    else 
        SDL_RenderCopy(renderer, tab_img[20].texture, NULL, &tab_img[20].posBoutonFen);

    SDL_RenderPresent(renderer);
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
    detruit_img(5);
    detruit_texte(3);
    creer_texte(tab_texte + 3, tab_perso[actuel]);
    creer_image(tab_img + 5, chemin_perso());
    
    SDL_RenderCopy(renderer, tab_img[5].texture, NULL, &tab_img[5].posBoutonFen);
    SDL_RenderCopy(renderer, tab_texte[3].message, NULL, &tab_texte[3].posTexte);
    
}

void clear_ecran(){
/*
met à jour l'affichage à l'écran : affichage l'image de fond et supprime toutes les textures qui étaient affichées à l'écran
*/
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    
}

void ajout_personnage(char * nom){
/*
ajoute un personnage dans la liste des personnages
*/
    tab_perso[nb_perso_ajoutes] = strdup(nom);
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
    affiche_menu();
}

void precedent(){
/*
change l'indice courant du tableau tab_perso pour aller au precedent
fonctionne circulairement : on revient à la fin si on arrive avant le début du tableau début
Appelle ensuite la fonction qui met à jour l'affichage
*/
    if (actuel > 0) actuel--;
    else actuel = nb_perso_ajoutes - 1;
    affiche_menu();
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

//modifier si on ajoute des perso
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
        case 3:
            return "../img/Characters/archer/Face.png";
        default:
            end(12);
    }
}

void detruit_tout(){
/*
detruit tous les textes et images présentes sur l'écran
*/

    for(int i = 0 ; i < nb_texte ; i++){
        detruit_texte(i);
    } 
    for(int i = 0 ; i < nb_img ; i++){
        detruit_img(i);
    } 
    for(int i = 0 ; i < nb_perso_ajoutes ; i++){
        free(tab_perso[i]);
    }
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
    }
}

void detruit_img(int indice){
/*
detruit une SDL_Texture dans la structure image passée en paramètre
*/
    if (tab_img[indice].texture) {
        SDL_DestroyTexture(tab_img[indice].texture);
        tab_img[indice].texture = NULL;   
  
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

int menu(char **pseudo, char *classe, char ** ipAddress){
    int retour;
    int WINDOW_WIDTH, WINDOW_HEIGHT;
    position_menu pos_actuelle = MENU_PRINCIPAL;
    SDL_Event event;

    
    init_sdl();
    
    //lance la musique dans le menu
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    musique = Mix_LoadMUS(cheminMusique);

    if(!musique){
        printf("Impossible d'ouvrir la musique %s\n", cheminMusique);
        end(100);
    }
    Mix_VolumeMusic(volume);
    Mix_PlayMusic(musique, -1);

    //récupère la taille de la fenêtre
    SDL_GetRendererOutputSize(renderer, &WINDOW_WIDTH, &WINDOW_HEIGHT);


    //image de fond
	backgroundTexture = creer_texture("../img/imgMenu.png");

    //liste des personnages à sélectionner -> modifier si on ajoute des perso
    ajout_personnage("mage");
    ajout_personnage("ninja");
    ajout_personnage("vampire");
    ajout_personnage("archer");


    //menu d'accueil 
    tab_img[0] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.37, WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.14}, NULL}; //bouton jouer
    tab_img[1] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.55, WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.14}, NULL};//bouton param
    tab_img[2] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.74, WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.14}, NULL};//bouton quitter
    tab_img[3] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.7, WINDOW_HEIGHT * 0.85, WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.14}, NULL};//flèche gauche
    tab_img[4] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.88, WINDOW_HEIGHT * 0.85, WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.14}, NULL};//flèche droite
    tab_img[5] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.78, WINDOW_HEIGHT * 0.61, WINDOW_WIDTH * 0.13, WINDOW_HEIGHT * 0.23}, NULL};//perso sélectionné

    //bouton retour
    tab_img[6] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.026, WINDOW_HEIGHT * 0.046, WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.18}, NULL};//arrière plan bouton retour
    tab_img[7] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.046, WINDOW_HEIGHT * 0.08, WINDOW_WIDTH * 0.06, WINDOW_HEIGHT * 0.11}, NULL};//img maison (retour)

    //bouton jouer
    tab_img[8] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.18, WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.18}, NULL};//position bouton créer partie
    tab_img[9] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.45, WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.18}, NULL}; //position bouton rejoindre partie

    //bouton créer partie
    tab_img[10] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.25, WINDOW_WIDTH * 0.45, WINDOW_HEIGHT * 0.27}, NULL}; //bouton saisie de l'ip

    // bouton param
    tab_img[11] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.18, WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.18}, NULL}; // bouton sauvegarder
    tab_img[12] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.45, WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.18}, NULL}; // bouton charger
    tab_img[13] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.74, WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.18}, NULL}; // bouton volume
    tab_img[14] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.77, WINDOW_WIDTH * 0.06, WINDOW_HEIGHT * 0.10}, NULL}; // arrière-plan volume +
    tab_img[15] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.19, WINDOW_HEIGHT * 0.79, WINDOW_WIDTH * 0.04, WINDOW_HEIGHT * 0.07}, NULL}; // bouton volume +
    tab_img[16] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.68, WINDOW_HEIGHT * 0.77, WINDOW_WIDTH * 0.06, WINDOW_HEIGHT * 0.10}, NULL}; // arrière-plan volume -
    tab_img[17] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.69, WINDOW_HEIGHT * 0.82, WINDOW_WIDTH * 0.04, WINDOW_HEIGHT * 0.05}, NULL}; // bouton volume -
    tab_img[18] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.08, WINDOW_HEIGHT * 0.77, WINDOW_WIDTH * 0.08, WINDOW_HEIGHT * 0.10}, NULL}; // arrière-plan volume coupé
    tab_img[19] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.09, WINDOW_HEIGHT * 0.79, WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.08}, NULL}; // bouton volume on
    tab_img[20] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.09, WINDOW_HEIGHT * 0.79, WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.08}, NULL}; // bouton volume off

    // menu serveur
    tab_img[21] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.31, WINDOW_HEIGHT * 0.51, WINDOW_WIDTH * 0.32, WINDOW_HEIGHT * 0.14}, NULL}; // bouton joueur + serveur
    tab_img[22] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.77, WINDOW_HEIGHT * 0.18, WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.27}, NULL}; // ip invalide
    tab_img[23] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.31, WINDOW_HEIGHT * 0.74, WINDOW_WIDTH * 0.32, WINDOW_HEIGHT * 0.14}, NULL}; // bouton serveur uniquement
    tab_img[24] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.6, WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.18}, NULL}; // bouton rejoindre (après saisie IP)



    //textes

    // Menu principal
    tab_texte[0] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.42, WINDOW_HEIGHT * 0.38, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.06}, NULL}; // texte jouer
    tab_texte[1] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.42, WINDOW_HEIGHT * 0.57, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.06}, NULL}; // texte paramètres
    tab_texte[2] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.42, WINDOW_HEIGHT * 0.75, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.06}, NULL}; // texte quitter
    tab_texte[3] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.76, WINDOW_HEIGHT * 0.51, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.06}, NULL}; // nom perso actuel
    tab_texte[4] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.13, WINDOW_HEIGHT * 0.09, WINDOW_WIDTH * 0.34, WINDOW_HEIGHT * 0.18}, NULL}; // nom du jeu
    tab_texte[5] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.65, WINDOW_HEIGHT * 0.09, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.18}, NULL}; // entrez votre nom
    tab_texte[6] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.65, WINDOW_HEIGHT * 0.09, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.18}, NULL}; // nom du joueur

    // Menu jouer
    tab_texte[7] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.42, WINDOW_HEIGHT * 0.22, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.05}, NULL}; // créer partie
    tab_texte[8] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.41, WINDOW_HEIGHT * 0.53, WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.05}, NULL}; // rejoindre partie

    // Menu param
    tab_texte[9]  = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.41, WINDOW_HEIGHT * 0.18, WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.05}, NULL}; // sauvegarder
    tab_texte[10] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.41, WINDOW_HEIGHT * 0.28, WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.05}, NULL}; // paramètres
    tab_texte[11] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.41, WINDOW_HEIGHT * 0.45, WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.05}, NULL}; // charger
    tab_texte[12] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.41, WINDOW_HEIGHT * 0.55, WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.05}, NULL}; // paramètres
    tab_texte[13] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.41, WINDOW_HEIGHT * 0.79, WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.05}, NULL}; // volume
    tab_texte[14] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.55, WINDOW_HEIGHT * 0.79, WINDOW_WIDTH * 0.08, WINDOW_HEIGHT * 0.05}, NULL}; // valeur volume

    // Menu serveur & rejoindre
    tab_texte[15] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.48, WINDOW_HEIGHT * 0.09, WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.05}, NULL}; // IP
    tab_texte[16] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.27, WINDOW_HEIGHT * 0.22, WINDOW_WIDTH * 0.46, WINDOW_HEIGHT * 0.11}, NULL}; // IP saisie (host)
    tab_texte[17] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.41, WINDOW_HEIGHT * 0.52, WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.07}, NULL}; // Être serveur
    tab_texte[18] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.78, WINDOW_HEIGHT * 0.20, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.06}, NULL}; // IP saisie (invalide)
    tab_texte[19] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.78, WINDOW_HEIGHT * 0.39, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.06}, NULL}; // invalide
    tab_texte[20] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.41, WINDOW_HEIGHT * 0.75, WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.07}, NULL}; // Être joueur
    tab_texte[21] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.27, WINDOW_HEIGHT * 0.22, WINDOW_WIDTH * 0.46, WINDOW_HEIGHT * 0.11}, NULL}; // IP saisie (rejoindre)
    tab_texte[22] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.41, WINDOW_HEIGHT * 0.61, WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.07}, NULL}; // Rejoindre


    
    //creation des images
    creer_image(tab_img, "../img/Boutons/boutonMenuLarge.png");
    creer_image(tab_img + 1, "../img/Boutons/boutonMenuLarge.png");
    creer_image(tab_img + 2, "../img/Boutons/boutonMenuLarge.png");
    creer_image(tab_img + 3, "../img/Boutons/flecheGauche.png");
    creer_image(tab_img + 4, "../img/Boutons/flecheDroite.png");
    creer_image(tab_img + 5, chemin_perso());
    creer_image(tab_img + 6, "../img/Boutons/boutonMenuRond.png");
    creer_image(tab_img + 7, "../img/Boutons/boutonRetour.png");
    creer_image(tab_img + 8, "../img/Boutons/boutonMenuLargeCarre.png");
    creer_image(tab_img + 9, "../img/Boutons/boutonMenuLargeCarre.png");
    creer_image(tab_img + 10, "../img/Boutons/boutonMenuLargeCarre.png");
    creer_image(tab_img + 11, "../img/Boutons/boutonMenuLargeCarre.png");
    creer_image(tab_img + 12, "../img/Boutons/boutonMenuLargeCarre.png");
    creer_image(tab_img + 13, "../img/Boutons/boutonMenuLargeCarre.png");
    creer_image(tab_img + 14, "../img/Boutons/boutonMenuCarre.png");
    creer_image(tab_img + 15, "../img/Boutons/boutonPlus.png");
    creer_image(tab_img + 16, "../img/Boutons/boutonMenuCarre.png");
    creer_image(tab_img + 17, "../img/Boutons/boutonMoins.png");
    creer_image(tab_img + 18, "../img/Boutons/boutonMenuRond.png");//arriere plan bouton volume on/off
    creer_image(tab_img + 19, "../img/Boutons/boutonVolumeOn.png");
    creer_image(tab_img + 20, "../img/Boutons/boutonVolumeOff.png");
    creer_image(tab_img + 21, "../img/Boutons/boutonMenuLargeCarre.png");
    creer_image(tab_img + 22, "../img/Boutons/boutonMenuLargeCarre.png");
    creer_image(tab_img + 23, "../img/Boutons/boutonMenuLargeCarre.png");
    creer_image(tab_img + 24, "../img/Boutons/boutonMenuLargeCarre.png");



    //creation des textes 
    creer_texte(tab_texte, "Jouer");
    creer_texte(tab_texte + 1, "Paramètres");
    creer_texte(tab_texte + 2, "Quitter");
    creer_texte(tab_texte + 3, tab_perso[actuel]);
    creer_texte(tab_texte + 4, nomJeu);
    creer_texte(tab_texte + 5, "Entrez votre nom");
    creer_texte(tab_texte + 6, nomJoueur);
    creer_texte(tab_texte + 7, "Créer partie");
    creer_texte(tab_texte + 8, "Rejoindre partie");
    creer_texte(tab_texte + 9, "Sauvegarder");
    creer_texte(tab_texte + 10, "Paramètres");
    creer_texte(tab_texte + 11, "Charger");
    creer_texte(tab_texte + 12, "Paramètres");
    creer_texte(tab_texte + 13, "Volume");
    creer_texte(tab_texte + 14, valVolume);
    creer_texte(tab_texte + 15, "IP");
    creer_texte(tab_texte + 17, "Etre serveur");
    creer_texte(tab_texte + 18, "Ip saisie");
    creer_texte(tab_texte + 19, " invalide");
    creer_texte(tab_texte + 20, " Etre joueur");
    creer_texte(tab_texte + 22, " Rejoindre");


    affiche_menu();
              
    while(pos_actuelle != SORTIE_MENU){
        while(SDL_PollEvent(&event)){
            //saisie du nom du joueur
            if(event.type == SDL_KEYDOWN){
                SDL_Keycode touche = event.key.keysym.sym;

                if(touche == SDLK_ESCAPE){
                    retour = -1;
                    pos_actuelle = SORTIE_MENU;
                }
                //si on est sur le menu d'accueil
                else if(pos_actuelle == MENU_PRINCIPAL){

                    //si c'est a-z ou 1-9
                    if (nbCarJoueur < NB_MAX_CAR_JOUEUR && ((touche >= SDLK_a && touche <= SDLK_z) || (touche >= SDLK_0 && touche <= SDLK_9))) {
                        nomJoueur[nbCarJoueur++] = (char)touche;
                        nomJoueur[nbCarJoueur] = '\0';
                        affiche_menu();                    
                    }
                    //suppression d'un caractère
                    else if(touche == SDLK_BACKSPACE){
                        if(nbCarJoueur >= 1){
                            nomJoueur[--nbCarJoueur] = '\0';
                            affiche_menu();
                        }     
                    }              
                }
                
                else if(pos_actuelle == DANS_REJOINDRE){
                    saisie_touche_ip(touche, &nbCarIp, saisieIp);
                    affiche_rejoindre();
                    SDL_RenderPresent(renderer);         
                }
            }
            
            else if(event.type == SDL_MOUSEBUTTONDOWN){
                SDL_Point point = {event.button.x, event.button.y};        

                //bouton quitter ?            
                if(SDL_PointInRect(&point, &tab_img[2].posBoutonFen) && pos_actuelle == MENU_PRINCIPAL){
                    retour = -1;
                    pos_actuelle = SORTIE_MENU;
                }

                //bouton jouer ?
                else if(SDL_PointInRect(&point, &tab_img[0].posBoutonFen) && pos_actuelle == MENU_PRINCIPAL){
                   
                    if(nbCarJoueur != 0){
                        pos_actuelle = DANS_JOUER;
                        //affichage des boutons du menu jouer
                        clear_ecran();
                        for(int i = 6 ; i < 10 ; i++){
                            SDL_RenderCopy(renderer, tab_img[i].texture, NULL, &tab_img[i].posBoutonFen);

                        }
                        //bouton retour
                        SDL_RenderCopy(renderer, tab_texte[7].message, NULL, &tab_texte[7].posTexte);
                        SDL_RenderCopy(renderer, tab_texte[8].message, NULL, &tab_texte[8].posTexte);
                        SDL_RenderPresent(renderer);
                    }
                }

                //bouton paramètre ?
                else if(SDL_PointInRect(&point, &tab_img[1].posBoutonFen) && pos_actuelle == MENU_PRINCIPAL){
                    pos_actuelle = DANS_PARAM;
                    affiche_param();
                                           
                }

                //flèche gauche ?
                else if(SDL_PointInRect(&point, &tab_img[3].posBoutonFen) && pos_actuelle == MENU_PRINCIPAL){
                    precedent();                     
                }

                //flèche droite ?
                else if(SDL_PointInRect(&point, &tab_img[4].posBoutonFen) && pos_actuelle == MENU_PRINCIPAL){
                    suivant();
                }
                
                //bouton retour
                else if(SDL_PointInRect(&point, &tab_img[6].posBoutonFen) && pos_actuelle != MENU_PRINCIPAL){
                    affiche_menu();
                    pos_actuelle = MENU_PRINCIPAL;
                }

                //sauvegarde param
                else if(SDL_PointInRect(&point, &tab_img[11].posBoutonFen) && pos_actuelle == DANS_PARAM){
                    FILE * fichier = fopen(cheminParamTxt, "w");
                    if(!nbCarJoueur)nomJoueur[0] = '#';
                    if(!nbCarIp)saisieIp[0] = '@';

                    fprintf(fichier, "%d\n%d\n%s\n%s", actuel, volume, nomJoueur, saisieIp);
                    fclose(fichier);
                }

                //charger param
                else if(SDL_PointInRect(&point, &tab_img[12].posBoutonFen) && pos_actuelle == DANS_PARAM){
                    FILE * fichier = fopen(cheminParamTxt, "r");
                    char joueur[NB_MAX_CAR_JOUEUR];

                    if(fichier){
                        fscanf(fichier, "%d %d %s %s", &actuel, &volume, joueur, saisieIp);
                        
                        if (!strcmp(joueur, "#")){
                            
                            nomJoueur[0] = ' ';
                            nbCarJoueur = 0;
                        } 

                        else{
                            strcpy(nomJoueur, joueur);
                            nbCarJoueur = strlen(nomJoueur);
                        }
                            

                        if (strcmp(saisieIp, "@") == 0) {
                            saisieIp[0] = ' ';
                            nbCarIp = 0;
                        } 

                        else{
                            nbCarIp = strlen(saisieIp);
                        }

                        

                        detruit_texte(6);
                        detruit_texte(16);

                        creer_texte(tab_texte + 6, nomJoueur);
                        creer_texte(tab_texte + 16, saisieIp);
                        fclose(fichier);
                    }
                    else printf("Fichier %s introuvable\n", cheminParamTxt);
                    affiche_param();
                    
                }
                

                //volume +
                else if(SDL_PointInRect(&point, &tab_img[14].posBoutonFen) && pos_actuelle == DANS_PARAM){
                    if(volume < 100) {
                        volume += 10;
                        affiche_param();
                    }
                }

                //volume -
                else if(SDL_PointInRect(&point, &tab_img[16].posBoutonFen) && pos_actuelle == DANS_PARAM){
                    if(volume > 0) {
                        volume -= 10;
                        affiche_param();
                    }
                }

                //inverse l'image du son coupé ou non
                else if((SDL_PointInRect(&point, &tab_img[19].posBoutonFen) || SDL_PointInRect(&point, &tab_img[20].posBoutonFen)) && pos_actuelle == DANS_PARAM){
                    
                    if(volume)
                        volume = 0;
                    else
                        volume = 100;
                    
                    affiche_param();                  
                }

                //bouton rejondre ?
                else if(SDL_PointInRect(&point, &tab_img[9].posBoutonFen) && pos_actuelle == DANS_JOUER){
                    affiche_rejoindre();       
                    SDL_RenderPresent(renderer);            
                    pos_actuelle = DANS_REJOINDRE;
                }

                //bouton creer partie ?
                else if(SDL_PointInRect(&point, &tab_img[8].posBoutonFen) && pos_actuelle == DANS_JOUER){                                  
                    pos_actuelle = DANS_CREER;

                    clear_ecran();              
                    //bouton retour 
                    SDL_RenderCopy(renderer, tab_img[6].texture, NULL, &tab_img[6].posBoutonFen);
                    SDL_RenderCopy(renderer, tab_img[7].texture, NULL, &tab_img[7].posBoutonFen);  


                    SDL_RenderCopy(renderer, tab_img[21].texture, NULL, &tab_img[21].posBoutonFen);  
                    SDL_RenderCopy(renderer, tab_img[23].texture, NULL, &tab_img[23].posBoutonFen);  

                    SDL_RenderCopy(renderer, tab_texte[17].message, NULL, &tab_texte[17].posTexte);
                    SDL_RenderCopy(renderer, tab_texte[20].message, NULL, &tab_texte[20].posTexte);
                    SDL_RenderPresent(renderer); 
                }

                //bouton lancer serveur ?
                else if((SDL_PointInRect(&point, &tab_img[21].posBoutonFen) || SDL_PointInRect(&point, &tab_img[23].posBoutonFen)) && pos_actuelle == DANS_CREER){          
                    //etre serveur et joueur
                    if(SDL_PointInRect(&point, &tab_img[21].posBoutonFen)){
                        retour = JOUER_SERVEUR;
                    }
                    else{
                        retour = SERVEUR;
                    }
                    *ipAddress = saisieIp;
                    pos_actuelle = SORTIE_MENU;                                  
                } 
                
                //bouton rejoindre partie (après saisie de l'ip)
                else if(SDL_PointInRect(&point, &tab_img[24].posBoutonFen) && pos_actuelle == DANS_REJOINDRE){
                    if(valider_ip(saisieIp)){
                        *ipAddress = saisieIp;
                        retour = JOUER;
                        pos_actuelle = SORTIE_MENU;
                    }

                    else{
                        affiche_rejoindre();
                        SDL_RenderCopy(renderer, tab_img[22].texture, NULL, &tab_img[22].posBoutonFen);  

                        SDL_RenderCopy(renderer, tab_texte[18].message, NULL, &tab_texte[18].posTexte);
                        SDL_RenderCopy(renderer, tab_texte[19].message, NULL, &tab_texte[19].posTexte);
                    }
                    SDL_RenderPresent(renderer);

                }
            }
        }
        SDL_Delay(10);
    }
    strcpy(classe, tab_perso[actuel]);
    *pseudo = nomJoueur;
    detruit_tout();
    return retour;
}

void main(void){
    char * pseudo;
    char * ipAddress;
    char * classe;
    printf("\nRetrour menu : %d | ", menu(&pseudo, classe, &ipAddress)); 
    printf("Pseudo :  %s | Classe : %s | Ip : %s\n", pseudo, classe, ipAddress);
    end(0);
}
