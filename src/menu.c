
#include "menu.h"

/*
compilation :
gcc menu.c -o menu -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer  


PF : continuer fonction charger param
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
int nbcarIp = 0; //nombre de caractères lors de la saisie de l'ip par le joueur


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
    
    window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    if (!window) end(2);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

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

int saisie_touche_ip(SDL_Keycode touche){
    if(nbcarIp < NB_MAX_CAR_IP){
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
                default : return 0;
            }

        }
        saisieIp[nbcarIp++] = c;
        saisieIp[nbcarIp] = '\0';
        affiche_host_game();
        SDL_RenderPresent(renderer); 
        return 1;

    }
    
}

void affiche_host_game(){
    clear_ecran();              
    //bouton retour 
    SDL_RenderCopy(renderer, tab_img[6].texture, NULL, &tab_img[6].posBoutonFen);
    SDL_RenderCopy(renderer, tab_img[7].texture, NULL, &tab_img[7].posBoutonFen);  
    SDL_RenderCopy(renderer, tab_img[21].texture, NULL, &tab_img[21].posBoutonFen);  
    SDL_RenderCopy(renderer, tab_img[23].texture, NULL, &tab_img[23].posBoutonFen);  

    

    //bouton saisie ip 
    SDL_RenderCopy(renderer, tab_img[10].texture, NULL, &tab_img[10].posBoutonFen);   
    SDL_RenderCopy(renderer, tab_texte[15].message, NULL, &tab_texte[15].posTexte);
    SDL_RenderCopy(renderer, tab_texte[17].message, NULL, &tab_texte[17].posTexte);
    SDL_RenderCopy(renderer, tab_texte[20].message, NULL, &tab_texte[20].posTexte);


    

    if(nbcarIp > 0){
        //texte ip
        detruit_texte(16);
        creer_texte(tab_texte + 16, saisieIp);
        SDL_RenderCopy(renderer, tab_texte[16].message, NULL, &tab_texte[16].posTexte);
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

    int retour;

    //image de fond
	backgroundTexture = creer_texture("../img/imgMenu.png");

    //liste des personnages à sélectionner -> modifier si on ajoute des perso
    ajout_personnage("mage");
    ajout_personnage("ninja");
    ajout_personnage("vampire");
    ajout_personnage("archer");

    //initialisation de toutes les textures du menu
    

    //menu d'accueil 
    tab_img[0] = (img_t) {(SDL_Rect){IMG_X, 400, IMG_W, IMG_H}, NULL}; //bouton jouer
    tab_img[1] = (img_t) {(SDL_Rect){IMG_X, 600, IMG_W, IMG_H}, NULL};//bouton param
    tab_img[2] = (img_t) {(SDL_Rect){IMG_X, 800, IMG_W, IMG_H}, NULL};//bouton quitter
    tab_img[3] = (img_t) {(SDL_Rect){1350, H_FLECHE, IMG_W / 2, IMG_H }, NULL};//flèche gauche
    tab_img[4] = (img_t) {(SDL_Rect){1700, H_FLECHE, IMG_W / 2, IMG_H }, NULL};//flèche droite
    tab_img[5] = (img_t) {(SDL_Rect){1500, 660, 250, 250 }, NULL};//perso sélectionné

    //bouton retour
    tab_img[6] = (img_t) {(SDL_Rect){50, 50, 200, 200}, NULL};//arrière plan bouton retour
    tab_img[7] = (img_t) {(SDL_Rect){88, 88, 120, 120}, NULL};//img maison (retour)

    //bouton jouer
    tab_img[8] = (img_t) {(SDL_Rect){X_BOUTON_PARAM, 200, W_BOUTON_PARAM, H_BOUTON_PARAM}, NULL};//position bouton créer partie
    tab_img[9] = (img_t) {(SDL_Rect){X_BOUTON_PARAM, 500, W_BOUTON_PARAM, H_BOUTON_PARAM}, NULL}; //position bouton rejoindre partie

    //bouton créer partie
    tab_img[10] = (img_t) {(SDL_Rect){X_BOUTON_PARAM - 100, 200, W_BOUTON_PARAM + 200, H_BOUTON_PARAM * 1.5}, NULL}; //bouton saisie de l'ip

    //bouton param
    tab_img[11] = (img_t) {(SDL_Rect){X_BOUTON_PARAM, 200, W_BOUTON_PARAM, H_BOUTON_PARAM}, NULL};//bouton sauv param
    tab_img[12] = (img_t) {(SDL_Rect){X_BOUTON_PARAM, 500, W_BOUTON_PARAM, H_BOUTON_PARAM}, NULL};//bouton charger param
    tab_img[13] = (img_t) {(SDL_Rect){X_BOUTON_PARAM, 800, W_BOUTON_PARAM, H_BOUTON_PARAM}, NULL};//bouton volume
    tab_img[14] = (img_t) {(SDL_Rect){X_BOUTON_PARAM - 175, 825, H_BOUTON_PARAM - 50, H_BOUTON_PARAM - 50}, NULL};//img arriere plan volume +
    tab_img[15] = (img_t) {(SDL_Rect){X_BOUTON_PARAM - 152, 850, H_BOUTON_PARAM - 95, H_BOUTON_PARAM - 100}, NULL};//bouton volume +
    tab_img[16] = (img_t) {(SDL_Rect){X_BOUTON_PARAM + W_BOUTON_PARAM + 25, 825, H_BOUTON_PARAM - 50, H_BOUTON_PARAM - 50}, NULL};//img arriere plan volume -
    tab_img[17] = (img_t) {(SDL_Rect){X_BOUTON_PARAM + W_BOUTON_PARAM + 52, 885, H_BOUTON_PARAM - 102, H_BOUTON_PARAM - 175}, NULL};//bouton volume -
    tab_img[18] = (img_t) {(SDL_Rect){W_BOUTON_PARAM / 4 - 15, 825, H_BOUTON_PARAM - 15, H_BOUTON_PARAM - 15}, NULL};//arriere plan volume coupé
    tab_img[19] = (img_t) {(SDL_Rect){W_BOUTON_PARAM / 4 + 10, 845, H_BOUTON_PARAM - 70, H_BOUTON_PARAM - 60}, NULL};//bouton volume on
    tab_img[20] = (img_t) {(SDL_Rect){W_BOUTON_PARAM / 4 + 10, 845, H_BOUTON_PARAM - 70, H_BOUTON_PARAM - 60}, NULL};//bouton volume off
    tab_img[21] = (img_t) {(SDL_Rect){X_BOUTON_PARAM + 25, 550, W_BOUTON_PARAM - 25, H_BOUTON_PARAM / 1.25}, NULL};//bouton etre joueur et serveur 
    
    tab_img[22] = (img_t) {(SDL_Rect){1475, 200, 350, H_BOUTON_PARAM * 2}, NULL};//bouton ip invalide
    tab_img[23] = (img_t) {(SDL_Rect){X_BOUTON_PARAM + 25, 800, W_BOUTON_PARAM - 25, H_BOUTON_PARAM / 1.25}, NULL};//bouton être serveur





    //menu principal
    tab_texte[0] = (texte_t) {(SDL_Rect)(SDL_Rect){IMG_X + 50, 410, IMG_W - 100, IMG_H - 40}, NULL};//texte jouer
    tab_texte[1] = (texte_t) {(SDL_Rect){IMG_X + 50, 615, IMG_W - 100, IMG_H - 40}, NULL};//texte paramètre
    tab_texte[2] = (texte_t) {(SDL_Rect){IMG_X + 50, 810, IMG_W - 100, IMG_H - 40}, NULL};//texte quitter
    tab_texte[3] = (texte_t) {(SDL_Rect){1450, 550, 300, 100}, NULL};//texte nom perso actuel
    tab_texte[4] = (texte_t) {(SDL_Rect){250, 100, 650, 200}, NULL};//texte nom du jeu
    tab_texte[5] = (texte_t) {(SDL_Rect){1250, 100, 600, 250 }, NULL};//texte entrez votre nom
    tab_texte[6] = (texte_t) {(SDL_Rect){1250, 100, 600, 250 }, NULL};//texte nom du joueur

    //bouton jouer
    tab_texte[7] = (texte_t) {(SDL_Rect){X_BOUTON_PARAM + 100, 240, W_BOUTON_PARAM - 200, H_BOUTON_PARAM / 2}, NULL}; //texte créer partie
    tab_texte[8] = (texte_t) {(SDL_Rect){X_BOUTON_PARAM + 75, 540, W_BOUTON_PARAM - 150, H_BOUTON_PARAM / 2}, NULL}; //texte rejoindre partie

    //bouton param
    tab_texte[9] = (texte_t) {(SDL_Rect){X_BOUTON_PARAM + 70, 200, W_BOUTON_PARAM - 150, H_BOUTON_PARAM / 2}, NULL};//texte : sauvegarder                   
    tab_texte[10] = (texte_t) {(SDL_Rect){X_BOUTON_PARAM + 70, 300, W_BOUTON_PARAM - 150, H_BOUTON_PARAM / 2}, NULL};//texte :paramètre
    tab_texte[11] = (texte_t) {(SDL_Rect){X_BOUTON_PARAM + 70, 500, W_BOUTON_PARAM - 150, H_BOUTON_PARAM / 2}, NULL};//texte : charger
    tab_texte[12] = (texte_t) {(SDL_Rect){X_BOUTON_PARAM + 70, 600, W_BOUTON_PARAM - 150, H_BOUTON_PARAM / 2}, NULL};//texte :paramètre
    tab_texte[13] = (texte_t) {(SDL_Rect){X_BOUTON_PARAM + 70, 850, W_BOUTON_PARAM / 2, H_BOUTON_PARAM / 2}, NULL};//texte : volume     
    tab_texte[14] = (texte_t) {(SDL_Rect){X_BOUTON_PARAM + W_BOUTON_PARAM / 2 + 100, 850, 150, H_BOUTON_PARAM / 2}, NULL};//valeur du volume
    tab_texte[15] = (texte_t) {(SDL_Rect){X_BOUTON_PARAM + 275, 100, W_BOUTON_PARAM / 4, H_BOUTON_PARAM / 2}, NULL};// texte IP
    tab_texte[16] = (texte_t) {(SDL_Rect){X_BOUTON_PARAM - 50, 240, W_BOUTON_PARAM + 100, H_BOUTON_PARAM * 1.1}, NULL}; //texte ip saisie
    tab_texte[17] = (texte_t) {(SDL_Rect){X_BOUTON_PARAM + 50, 560, W_BOUTON_PARAM - 75, H_BOUTON_PARAM / 1.5}, NULL}; //texte être serveur
    tab_texte[20] = (texte_t) {(SDL_Rect){X_BOUTON_PARAM + 50, 805, W_BOUTON_PARAM - 75, H_BOUTON_PARAM / 1.5}, NULL}; //texte être Joueur (et serveur)

    //warning saisie ip
    tab_texte[18] = (texte_t) {(SDL_Rect){1500, 220, 300, H_BOUTON_PARAM}, NULL}; //texte ip saisie
    tab_texte[19] = (texte_t) {(SDL_Rect){1500, 420, 300, H_BOUTON_PARAM}, NULL}; //texte invalide




    
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



    affiche_menu();
              
    SDL_Event event;
    int dansEstServeur = 0; //a-t-on cliqué sur le bouton créer une partie 
    int dansParam = 0;
    int dansJouer = 0;
    int sortieMenu = 0;
    int ecriture = 0; //dans la fonction jouer

    while(!sortieMenu){
        while(SDL_PollEvent(&event)){
            //saisie du nom du joueur
            if(event.type == SDL_KEYDOWN){
                SDL_Keycode touche = event.key.keysym.sym;

                if(touche == SDLK_ESCAPE){
                    retour = -1;
                    sortieMenu = 1;
                }
                //si on est sur le menu d'accueil
                else if(!dansEstServeur && !dansJouer && !dansParam){

                    //si c'est a-z ou 1-9
                    if (nbCarJoueur < NB_MAX_CAR_JOUEUR && ((touche >= SDLK_a && touche <= SDLK_z) || (touche >= SDLK_0 && touche <= SDLK_9) || touche >= SDLK_KP_0 && touche <= SDLK_KP_9)) {
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
                
                else if(dansEstServeur){    
                    if(saisie_touche_ip(touche));
                    else if(touche == SDLK_BACKSPACE){
                        if(nbcarIp >= 1){
                            saisieIp[--nbcarIp] = 'a';
                            affiche_host_game();
                            SDL_RenderPresent(renderer); 

                        }
                    }
                }
            }
            
            else if(event.type == SDL_MOUSEBUTTONDOWN){
                SDL_Point point = {event.button.x, event.button.y};        

                //bouton quitter ?            
                if(SDL_PointInRect(&point, &tab_img[2].posBoutonFen) &&!dansJouer && !dansParam){
                    sortieMenu = 1;
                }

                //bouton jouer ?
                else if(SDL_PointInRect(&point, &tab_img[0].posBoutonFen) &&!dansJouer && !dansParam){
                   
                    if(strcmp(nomJoueur, " ") || strcmp(nomJoueur, "\0")){
                        dansJouer = 1;
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
                else if(SDL_PointInRect(&point, &tab_img[1].posBoutonFen) &&!dansJouer && !dansParam){
                    dansParam = 1;
                    affiche_param();
                                           
                }

                //flèche gauche ?
                else if(SDL_PointInRect(&point, &tab_img[3].posBoutonFen) && !dansJouer && !dansParam){
                    precedent();                     
                }

                //flèche droite ?
                else if(SDL_PointInRect(&point, &tab_img[4].posBoutonFen) && !dansJouer && !dansParam){
                    suivant();
                }
                
                //bouton retour
                else if(SDL_PointInRect(&point, &tab_img[6].posBoutonFen) && (dansJouer || dansParam || dansEstServeur)){
                    affiche_menu();
                    dansJouer = 0;
                    dansParam = 0;
                    dansEstServeur = 0;
                }

                //sauvegarde param
                else if(SDL_PointInRect(&point, &tab_img[11].posBoutonFen) && dansParam){
                    FILE * fichier = fopen(cheminParamTxt, "w");
                    if(!nbCarJoueur)nomJoueur[0] = '#';
                    if(!nbcarIp)saisieIp[0] = '@';

                    fprintf(fichier, "%d\n%d\n%s\n%s", actuel, volume, nomJoueur, saisieIp);
                    fclose(fichier);
                }

                //charger param
                else if(SDL_PointInRect(&point, &tab_img[12].posBoutonFen) && dansParam){
                    FILE * fichier = fopen(cheminParamTxt, "r");
                    char * joueur;
                    if(fichier){
                        fscanf(fichier, "%d %d %s %s", &actuel, &volume, joueur, saisieIp);
                        if(joueur == "#"){
                            printf("ok");
                            //strcpy(nomJoueur, joueur);
                        }
                        else{
                            nbCarJoueur = strlen(nomJoueur);
                        }
                        if(!strcmp(saisieIp, "@"))saisieIp[0] = ' ';


                        

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
                else if(SDL_PointInRect(&point, &tab_img[14].posBoutonFen) && dansParam){
                    if(volume < 100) {
                        volume += 10;
                        affiche_param();
                    }
                }

                //volume -
                else if(SDL_PointInRect(&point, &tab_img[16].posBoutonFen) && dansParam){
                    if(volume > 0) {
                        volume -= 10;
                        affiche_param();
                    }
                }

                //inverse l'image du son coupé ou non
                else if((SDL_PointInRect(&point, &tab_img[19].posBoutonFen) || SDL_PointInRect(&point, &tab_img[20].posBoutonFen)) && dansParam){
                    
                    if(volume)
                        volume = 0;
                    else
                        volume = 100;
                    
                    affiche_param();                  
                }

                //bouton rejondre ?
                else if(SDL_PointInRect(&point, &tab_img[9].posBoutonFen) && dansJouer){
                    printf("Rejoindre\n");
                    retour = JOUER;
                    sortieMenu = 1;
                }

                //bouton creer partie ?
                else if(SDL_PointInRect(&point, &tab_img[8].posBoutonFen) && dansJouer){                                  
                    dansJouer = 0;
                    dansEstServeur = 1;
                    affiche_host_game();
                    SDL_RenderPresent(renderer); 
                }

                //bouton lancer serveur ?
                else if(SDL_PointInRect(&point, &tab_img[21].posBoutonFen) || SDL_PointInRect(&point, &tab_img[23].posBoutonFen) && dansEstServeur){        
                    //affiche_host_game();   

                    if(valider_ip(saisieIp)){
                        if(SDL_PointInRect(&point, &tab_img[21].posBoutonFen)){
                            retour = JOUER_SERVEUR;
                        }
                        else{
                            retour = SERVEUR;
                        }
                        sortieMenu = 1;

                        
                    }                       
                    else{
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
   *ipAddress = saisieIp;
    detruit_tout();
    return retour;
}

void main(void){
    char * pseudo;
    char * ipAddress;
    char * classe;
    menu(&pseudo, classe, &ipAddress); 
    printf("%s %s %s\n", pseudo, classe, ipAddress);
    end(0);
}
