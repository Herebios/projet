
#include "menu.h"

#include "inventaire.c"


/*
compilation :
gcc menu.c -o menu -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer  


PF : doc, continuer gestion de boutons avec clic dans param etc
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


int bouton_select = 0;


char nomJoueur[NB_MAX_CAR_JOUEUR] = "#"; //nom saisi par l'utilisateur
char cheminMusique[] = "../include/musiqueMenu.ogg";
char cheminParamTxt[] = "../include/.sauvegarde.txt";
char valVolume[4] = "100"; //sert à convertir la valeur du volume pour l'afficher
char saisieIp[NB_MAX_CAR_IP] = "@";


char * tab_perso[NB_MAX_PERSO]; //liste des personnages disponibles à choisir
img_t tab_img[NB_IMG]; //tableau de textures images
texte_t tab_texte[NB_TEXTE];//tableau de textures texte


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
    
    window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1500, 800, SDL_WINDOW_SHOWN);
    if (!window) end(2);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) end(3);

    TTF_Init();

    police = TTF_OpenFont("../include/Go-Regular.ttf", 100);
	if (!police) end(6);

    SDL_Init(SDL_INIT_AUDIO);
}

void dessine_image(int i) {
    if (tab_img[i].texture)
        SDL_RenderCopy(renderer, tab_img[i].texture, NULL, &tab_img[i].posBoutonFen);
}

void dessine_texte(int i) {
    if (tab_texte[i].message)
        SDL_RenderCopy(renderer, tab_texte[i].message, NULL, &tab_texte[i].posTexte);
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
                case SDLK_KP_ENTER :
                case SDLK_RETURN : return;
                default : return;
            }

        }
        saisie[(*nbCar)++] = c;
        saisie[*nbCar] = '\0';
    }
}

void affiche_rejoindre(){
    clear_ecran();
    //bouton retour 
    dessine_img(6);
    dessine_img(7);
    dessine_img(10);
    SDL_SetTextureColorMod(tab_img[23].texture, 180, 120, 80); // survol clavier

    dessine_img(23);

    dessine_texte(15);
    dessine_texte(22);
    
    if(nbCarIp > 0){
        //texte ip
        maj_texte(tab_texte + 21, saisieIp);
        dessine_texte(21);
    }
}

void aff_menu(position_menu * pos, int tabBouton[], int bouton_choisi){
    switch(*pos){
        case MENU_PRINCIPAL: affiche_menu_accueil(tabBouton, bouton_choisi);
                            SDL_RenderPresent(renderer);
                            break;

        case DANS_PARAM : 
                            clear_ecran();
                            dessine_img(6);
                            dessine_img(7);

                            for(int i = 11 ; i < 19 ; i++){
                                if (i == tabBouton[bouton_choisi])
                                    SDL_SetTextureColorMod(tab_img[i].texture, 180, 120, 80); // survol clavier
                                else
                                    SDL_SetTextureColorMod(tab_img[i].texture, 255, 255, 255);
                                dessine_img(i);
                            } 
                            
                            for(int i = 9 ; i < 15 ; i++){
                                if(i != 14) dessine_texte(i);
                            } 
                                
                            snprintf(valVolume, sizeof(valVolume), "%d", volume);
                            Mix_VolumeMusic(volume);
                            maj_texte(tab_texte + 14, valVolume);
                            
                            dessine_texte(14);

                            if(volume)
                                dessine_img(19);    
                            else 
                                dessine_img(20);

                            SDL_RenderPresent(renderer);
                            break;

        case DANS_REJOINDRE : affiche_rejoindre(); SDL_RenderPresent(renderer); 
                            break;

        case DANS_JOUER : clear_ecran();
                        for(int i = 6 ; i < 10 ; i++){
                            if (i == tabBouton[bouton_choisi])
                                SDL_SetTextureColorMod(tab_img[i].texture, 180, 120, 80); // survol clavier
                            else
                                SDL_SetTextureColorMod(tab_img[i].texture, 255, 255, 255);
                            dessine_img(i);
                        }
                        
                        
                        dessine_texte(7);
                        dessine_texte(8);

                        SDL_RenderPresent(renderer);
                        break;

        case DANS_CREER : clear_ecran();              
                    //bouton retour 
                    dessine_img(6);
                    dessine_img(7);
                    

                    if(tabBouton[bouton_choisi] == 21)
                        SDL_SetTextureColorMod(tab_img[21].texture, 180, 120, 80); // survol clavier
                    else
                        SDL_SetTextureColorMod(tab_img[21].texture, 255, 255, 255);

                    if(tabBouton[bouton_choisi] == 23)
                        SDL_SetTextureColorMod(tab_img[23].texture, 180, 120, 80); // survol clavier
                    else
                        SDL_SetTextureColorMod(tab_img[23].texture, 255, 255, 255);

                    dessine_img(21);
                    dessine_img(22); 

                    dessine_texte(17);
                    dessine_texte(20);
                    SDL_RenderPresent(renderer); 
                    break;

        case BAD_IP : affiche_rejoindre();

                    dessine_texte(18);
                    dessine_texte(19);

                    SDL_RenderPresent(renderer);    
                    *pos = DANS_REJOINDRE;
                    break;

                        
        case BAD_NAME : affiche_menu_accueil(tabBouton, bouton_choisi);
                        dessine_texte(23);
                        *pos = MENU_PRINCIPAL;
                        SDL_RenderPresent(renderer);
                        break;

        case SORTIE_MENU : break;
    }
}

void affiche_menu_accueil(int tabBouton[], int bouton_choisi){
    clear_ecran();
    //chargement des boutons et textes du menu principal
    for(int i = 0 ; i < 5 ; i++){
        if (i == tabBouton[bouton_choisi])
            SDL_SetTextureColorMod(tab_img[i].texture, 180, 120, 80); // survol clavier
        
        else
            SDL_SetTextureColorMod(tab_img[i].texture, 255, 255, 255);
        dessine_img(i);
        if(i != 3) dessine_texte(i);
    }
    

    maj_texte(&tab_texte[3], tab_perso[actuel]);

    detruit_img(5);
    creer_image(tab_img + 5, chemin_perso());

    dessine_img(5);
    dessine_texte(3);

    
    //si le nom du joueur n'est pas chargé, on affiche "entrez votre nom"
    
    if(nbCarJoueur == 0)
        dessine_texte(5);
    else{
        maj_texte(&tab_texte[6], nomJoueur);
        dessine_texte(6);
    }    
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

void suivant(int * tab_bouton){
/*
change l'indice courant du tableau tab_perso pour aller au suivant
fonctionne circulairement : on revient au début si on dépasse la fin du tableau
Appelle ensuite la fonction qui met à jour l'affichage
*/
    
    if(actuel < nb_perso_ajoutes - 1) actuel++;
    else actuel = 0; 
    position_menu pos = MENU_PRINCIPAL;
    aff_menu(&pos, tab_bouton, bouton_select);
}

void precedent(int * tab_bouton){
/*
change l'indice courant du tableau tab_perso pour aller au precedent
fonctionne circulairement : on revient à la fin si on arrive avant le début du tableau début
Appelle ensuite la fonction qui met à jour l'affichage
*/
    if (actuel > 0) actuel--;
    else actuel = nb_perso_ajoutes - 1;
    position_menu pos = MENU_PRINCIPAL;
    aff_menu(&pos, tab_bouton, bouton_select);
}

SDL_Texture * creer_texture(char * chemin){
/*
créée une texture à partir du chemin vers une image
renvoie un pointeur sur cette texture
*/
    SDL_Texture * texture = IMG_LoadTexture(renderer, chemin);
    if(!texture) end(200);
    return texture;
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
    return "null";
}

void detruit_image(int indice){
/*
detruit une SDL_Texture dans la structure image passée en paramètre
*/
    if (tab_img[indice].texture) {
        SDL_DestroyTexture(tab_img[indice].texture);
        tab_img[indice].texture = NULL;   
    }
}

void maj_texte(texte_t *texte, char *nouveau) {
    if (strcmp(texte->contenu, nouveau) != 0) {
        SDL_DestroyTexture(texte->message);
        texte->message = NULL;
        creer_texte(texte, nouveau);
    }
}

void creer_texte(texte_t * texte, char * txt){
/*
créée une texture de type texte avec la string passée en paramètre et la
stocke dans la structure texte_t dans le champ message
*/

    //texte existe déjà ?
    if(texte->message && !strcmp(texte->contenu, txt)) return;

    surface = TTF_RenderUTF8_Blended(police, txt, (SDL_Color){ 255, 255, 255, 255 });
    if(!surface) end(10);

    texte->message = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); 

    strcpy(texte->contenu, txt); 
}

void creer_texte_rouge(texte_t * texte, char * txt){
    /*
    créée une texture de type texte avec la string passée en paramètre et la
    stocke dans la structure texte_t dans le champ message
    */
    
        //texte existe déjà ?
        if(texte->message && !strcmp(texte->contenu, txt)) return;
    
        surface = TTF_RenderUTF8_Blended(police, txt, (SDL_Color){255, 0, 0, 255 });
        if(!surface) end(11);
    
        texte->message = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface); 
    
        strcpy(texte->contenu, txt); 
    }

void creer_image(img_t * image, char * nomFich){
/*
créée une texture à partir du chemin vers une image, le stocke dans le champ texture de la structure img_t
*/
    image->texture = creer_texture(nomFich);
    if(!image->texture) end(5);
}

int menu(char *classe){
    
    int retour;
    int modifications = 0;
    int WINDOW_WIDTH, WINDOW_HEIGHT;
    position_menu pos_actuelle = MENU_PRINCIPAL;
    SDL_Event event;
    Uint32 start = SDL_GetTicks();
    Uint32 frame;
    int tabBoutonsMenu[] = {0, 1, 2, 3, 4};
    int tabBoutonsParam[] = {11, 12, 15, 17};
    int tabBoutonsJouer[] = {8, 9};
    int tabBoutonsCreer[] = {22, 21};
    int tabBoutonsRejoi[] = {23};

    


    //tab de chaque elm pouvant être sélectionné selon l'etat actuel du menu. tabBoutonsCreer y est 2 fois car il ya 
    //l'etat BAD_IP où on affiche la même chose que REJOINDRE mais avec un message d'erreur
    int * tabBoutons[] = {tabBoutonsMenu, tabBoutonsParam, tabBoutonsJouer, tabBoutonsCreer, tabBoutonsRejoi, tabBoutonsCreer, tabBoutonsMenu}; 
    
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
    tab_img[9] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.60, WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.18}, NULL}; //position bouton rejoindre partie

    //bouton créer partie
    tab_img[10] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.25, WINDOW_WIDTH * 0.45, WINDOW_HEIGHT * 0.27}, NULL}; //bouton saisie de l'ip

    // bouton param
    tab_img[11] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.18, WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.18}, NULL}; // bouton sauvegarder
    tab_img[12] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.45, WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.18}, NULL}; // bouton charger
    tab_img[13] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.74, WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.18}, NULL}; // bouton volume
    tab_img[14] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.22, WINDOW_HEIGHT * 0.77, WINDOW_WIDTH * 0.06, WINDOW_HEIGHT * 0.10}, NULL}; // arrière-plan volume +
    tab_img[15] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.23, WINDOW_HEIGHT * 0.785, WINDOW_WIDTH * 0.04, WINDOW_HEIGHT * 0.07}, NULL}; // bouton volume +
    tab_img[16] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.68, WINDOW_HEIGHT * 0.77, WINDOW_WIDTH * 0.06, WINDOW_HEIGHT * 0.10}, NULL}; // arrière-plan volume -
    tab_img[17] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.692, WINDOW_HEIGHT * 0.81, WINDOW_WIDTH * 0.038, WINDOW_HEIGHT * 0.02}, NULL}; // bouton volume -
    tab_img[18] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.075, WINDOW_HEIGHT * 0.77, WINDOW_WIDTH * 0.08, WINDOW_HEIGHT * 0.12}, NULL}; // arrière-plan volume coupé
    tab_img[19] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.09, WINDOW_HEIGHT * 0.79, WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.08}, NULL}; // bouton volume on
    tab_img[20] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.09, WINDOW_HEIGHT * 0.79, WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.08}, NULL}; // bouton volume off

    // menu serveur
    tab_img[21] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.2, WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.2}, NULL}; // bouton joueur + serveur
    tab_img[22] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.7, WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.2}, NULL}; // bouton serveur uniquement
    tab_img[23] = (img_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.75, WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.18}, NULL}; // bouton rejoindre (après saisie IP)



    //textes

    // Menu principal
    tab_texte[0] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.22, WINDOW_HEIGHT * 0.4, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.07}, NULL}; // texte jouer
    tab_texte[1] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.22, WINDOW_HEIGHT * 0.58, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.08}, NULL}; // texte paramètres
    tab_texte[2] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.22, WINDOW_HEIGHT * 0.77, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.07}, NULL}; // texte quitter
    tab_texte[3] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.76, WINDOW_HEIGHT * 0.50, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.08}, NULL}; // nom perso actuel
    tab_texte[4] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.13, WINDOW_HEIGHT * 0.09, WINDOW_WIDTH * 0.34, WINDOW_HEIGHT * 0.18}, NULL}; // nom du jeu
    tab_texte[5] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.65, WINDOW_HEIGHT * 0.09, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.18}, NULL}; // entrez votre nom
    tab_texte[6] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.65, WINDOW_HEIGHT * 0.09, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.18}, NULL}; // nom du joueur

    // Menu jouer
    tab_texte[7] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.33, WINDOW_HEIGHT * 0.22, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.1}, NULL}; // créer partie
    tab_texte[8] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.33, WINDOW_HEIGHT * 0.63, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.1}, NULL}; // rejoindre partie

    // Menu param
    tab_texte[9]  = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.19, WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.07}, NULL}; // sauvegarder
    tab_texte[10] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.27, WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.07}, NULL}; // paramètres
    tab_texte[11] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.46, WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.07}, NULL}; // charger
    tab_texte[12] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.54, WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.07}, NULL}; // paramètres
    tab_texte[13] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.79, WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.07}, NULL}; // volume
    tab_texte[14] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.55, WINDOW_HEIGHT * 0.79, WINDOW_WIDTH * 0.08, WINDOW_HEIGHT * 0.07}, NULL}; // valeur volume

    // Menu serveur & rejoindre
    tab_texte[15] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.45, WINDOW_HEIGHT * 0.09, WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1}, NULL}; // IP
    tab_texte[16] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.25, WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.1}, NULL}; // IP saisie (host)
    tab_texte[17] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.34, WINDOW_HEIGHT * 0.245, WINDOW_WIDTH * 0.27, WINDOW_HEIGHT * 0.1}, NULL}; // Être serveur
    tab_texte[18] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.55, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.06}, NULL}; // IP saisie (invalide)
    tab_texte[19] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.48, WINDOW_HEIGHT * 0.55, WINDOW_WIDTH * 0.16, WINDOW_HEIGHT * 0.06}, NULL}; // invalide
    tab_texte[20] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.325, WINDOW_HEIGHT * 0.745, WINDOW_WIDTH * 0.28, WINDOW_HEIGHT * 0.1}, NULL}; // Être joueur
    tab_texte[21] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.285, WINDOW_HEIGHT * 0.342, WINDOW_WIDTH * 0.375, WINDOW_HEIGHT * 0.1}, NULL}; // IP saisie (rejoindre)
    tab_texte[22] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.33, WINDOW_HEIGHT * 0.79, WINDOW_WIDTH * 0.28, WINDOW_HEIGHT * 0.1}, NULL}; // Rejoindre

    //pas de nom saisi
    tab_texte[23] = (texte_t) {(SDL_Rect){WINDOW_WIDTH * 0.7, WINDOW_HEIGHT * 0.3, WINDOW_WIDTH * 0.23, WINDOW_HEIGHT * 0.1}, NULL}; // nom invalide



    
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
    creer_image(tab_img + 18, "../img/Boutons/boutonMenuRond.png");
    creer_image(tab_img + 19, "../img/Boutons/boutonVolumeOn.png");
    creer_image(tab_img + 20, "../img/Boutons/boutonVolumeOff.png");    
    creer_image(tab_img + 21, "../img/Boutons/boutonMenuLargeCarre.png");
    //creer_image(tab_img + 22, "../img/Boutons/boutonMenuLargeCarre.png");
    creer_image(tab_img + 22, "../img/Boutons/boutonMenuLargeCarre.png");
    creer_image(tab_img + 23, "../img/Boutons/boutonMenuLargeCarre.png");

    
    
    
    //creation des textes 
    creer_texte(tab_texte, "Jouer");
    creer_texte(tab_texte + 1, "Paramètres");
    creer_texte(tab_texte + 2, "Quitter");
    creer_texte(tab_texte + 3, tab_perso[actuel]);
    creer_texte(tab_texte + 4, "BAD'DOS 4EVER");//nom du jeu
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
    creer_texte_rouge(tab_texte + 18, "Ip saisie");
    creer_texte_rouge(tab_texte + 19, "invalide");
    creer_texte(tab_texte + 20, "Etre joueur");
    
    creer_texte(tab_texte + 22, "Rejoindre");

    creer_texte_rouge(tab_texte + 23, "Nom invalide");

    aff_menu(&pos_actuelle, tabBoutonsMenu, bouton_select);

    while(pos_actuelle != SORTIE_MENU){
        while(SDL_PollEvent(&event)){
            //saisie du nom du joueur
            if(event.type == SDL_KEYDOWN){
                SDL_Keycode touche = event.key.keysym.sym;
                SDL_Point p = {tab_img[tabBoutons[pos_actuelle][bouton_select]].posBoutonFen.x + 1,
                               tab_img[tabBoutons[pos_actuelle][bouton_select]].posBoutonFen.y + 1};

                //sortie forcée par echap
                if(touche == SDLK_ESCAPE){
                    if(pos_actuelle != MENU_PRINCIPAL){
                        pos_actuelle = MENU_PRINCIPAL;
                        modifications = 1;
                    } 
                    else{
                        retour = -1;
                        pos_actuelle = SORTIE_MENU;
                    }
                }

                //gestion du deplacement avec flèche dans le menu d'accueil
                else if(pos_actuelle == MENU_PRINCIPAL){
                    modifications = 1;
                    if (touche == SDLK_DOWN) {
                        bouton_select = (bouton_select + 1) % 3;
                    }
                    else if (touche == SDLK_UP) {
                        bouton_select = (bouton_select - 1 + 3) % 3;
                    }
                    else if(touche == SDLK_LEFT) {
                        precedent(tabBoutonsMenu);
                    }
                    else if(touche == SDLK_RIGHT) {
                        suivant(tabBoutonsMenu);
                    }

                    //modifications nom du joueur saisi
                    //si c'est a-z ou 1-9
                    if (nbCarJoueur < NB_MAX_CAR_JOUEUR && ((touche >= SDLK_a && touche <= SDLK_z) || (touche >= SDLK_0 && touche <= SDLK_9))) {
                        nomJoueur[nbCarJoueur++] = (char)touche;
                        nomJoueur[nbCarJoueur] = '\0';
                    }
                    //suppression d'un caractère
                    else if(touche == SDLK_BACKSPACE){
                        if(nbCarJoueur >= 1){
                            nomJoueur[--nbCarJoueur] = '\0';
                        }     
                    }              
                }
                
                //gestion du deplacement avec flèche dans les paramètres
                else if(pos_actuelle == DANS_PARAM){
                    modifications = 1;
                    if (touche == SDLK_DOWN)
                        bouton_select = (bouton_select + 1) % 4;
                    
                    else if(touche == SDLK_UP)
                        bouton_select = (bouton_select - 1 + 4) % 4;
                }

                //gestion du deplacement avec flèche dans jouer
                else if(pos_actuelle == DANS_JOUER){
                    modifications = 1;
                    if(touche == SDLK_DOWN || touche == SDLK_UP)
                        bouton_select = (bouton_select + 1) % 2; 
                }

                //gestion du deplacement avec flèche dans créer partie
                else if(pos_actuelle == DANS_CREER){
                    modifications = 1;
                    if(touche == SDLK_DOWN || touche == SDLK_UP)
                        bouton_select = (bouton_select + 1) % 2;
                }
                
                //gestion du deplacement avec flèche dans rejoindre partie
                else if(pos_actuelle == DANS_REJOINDRE){
                    saisie_touche_ip(touche, &nbCarIp, saisieIp);
                    modifications = 1;
                }

                //simulation d'un clic 
                if ((touche == SDLK_KP_ENTER || touche == SDLK_RETURN) && modifications){
                    SDL_Event clic;
                    clic.type = SDL_MOUSEBUTTONDOWN;
                    clic.button.x = p.x;
                    clic.button.y = p.y;
                    clic.button.button = SDL_BUTTON_LEFT;
                    SDL_PushEvent(&clic);
                }                
            }

            else if(event.type == SDL_QUIT){
                retour = -1;
                pos_actuelle = SORTIE_MENU;
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
                    bouton_select = 0;
                    modifications = 1;                     

                    if(nbCarJoueur != 0){
                        pos_actuelle = DANS_JOUER;
                    }
                    else{
                        pos_actuelle = BAD_NAME;
                    }
                }

                //bouton paramètre ?
                else if(SDL_PointInRect(&point, &tab_img[1].posBoutonFen) && pos_actuelle == MENU_PRINCIPAL){
                    bouton_select = 0;
                    pos_actuelle = DANS_PARAM;
                    modifications = 1;                                           
                }

                //flèche gauche ?
                else if(SDL_PointInRect(&point, &tab_img[3].posBoutonFen) && pos_actuelle == MENU_PRINCIPAL){
                    precedent(tabBoutonsMenu); 
                }

                //flèche droite ?
                else if(SDL_PointInRect(&point, &tab_img[4].posBoutonFen) && pos_actuelle == MENU_PRINCIPAL){
                    suivant(tabBoutonsMenu);
                }
                
                //bouton retour
                else if(SDL_PointInRect(&point, &tab_img[6].posBoutonFen) && pos_actuelle != MENU_PRINCIPAL){
                    pos_actuelle = MENU_PRINCIPAL;
                    modifications = 1;

                }

                //sauvegarde param
                else if(SDL_PointInRect(&point, &tab_img[11].posBoutonFen) && pos_actuelle == DANS_PARAM){
                    FILE * fichier = fopen(cheminParamTxt, "w");
                    if(!nbCarJoueur) nomJoueur[0] = '#';
                    if(!nbCarIp) saisieIp[0] = '@';
                    if(fichier){
                        fprintf(fichier, "%d\n%d\n%s\n%s", actuel, volume, nomJoueur, saisieIp);
                        fclose(fichier);
                    }
                    else{
                        perror("Erreur lors de la sauvegarde des paramètres.\n");
                    }
                }

                //charger param
                else if(SDL_PointInRect(&point, &tab_img[12].posBoutonFen) && pos_actuelle == DANS_PARAM){
                    FILE * fichier = fopen(cheminParamTxt, "r");
                    char joueur[NB_MAX_CAR_JOUEUR];

                    if(fichier){
                        fscanf(fichier, "%d %d %s %s", &actuel, &volume, joueur, saisieIp);
                        
                        if (!strcmp(joueur, "#")){
                            
                            nomJoueur[0] = '#';
                            nbCarJoueur = 0;
                        } 

                        else{
                            strcpy(nomJoueur, joueur);
                            nbCarJoueur = strlen(nomJoueur);
                        }
                            

                        if (strcmp(saisieIp, "@") == 0) {
                            saisieIp[0] = '@';
                            nbCarIp = 0;
                        } 

                        else{
                            nbCarIp = strlen(saisieIp);
                        }
                        maj_texte(tab_texte + 6, nomJoueur);
                        maj_texte(tab_texte + 16, saisieIp);
                        fclose(fichier);
                        modifications = 1;

                    }
                    else{
                        printf("\nFichier %s introuvable. Veuillez sauvegarder vos paramètres avant de les charger.\n", cheminParamTxt);
                        end(111);
                    }
                }

                //volume +
                else if(SDL_PointInRect(&point, &tab_img[14].posBoutonFen) && pos_actuelle == DANS_PARAM){
                    if(volume < 100) {
                        modifications = 1;
                        volume += 10;
                    }
                }

                //volume -
                else if(SDL_PointInRect(&point, &tab_img[16].posBoutonFen) && pos_actuelle == DANS_PARAM){
                    if(volume > 0) {
                        modifications = 1;
                        volume -= 10;
                    }
                }

                //inverse l'image du son coupé ou non
                else if((SDL_PointInRect(&point, &tab_img[19].posBoutonFen) || SDL_PointInRect(&point, &tab_img[20].posBoutonFen)) && pos_actuelle == DANS_PARAM){
                    if(volume)
                        volume = 0;
                    else
                        volume = 100;
                    modifications = 1;
                }

                //bouton rejondre ?
                else if(SDL_PointInRect(&point, &tab_img[9].posBoutonFen) && pos_actuelle == DANS_JOUER){
                    bouton_select = 0;
                    pos_actuelle = DANS_REJOINDRE;
                    modifications = 1;
                }

                //bouton creer partie ?
                else if(SDL_PointInRect(&point, &tab_img[8].posBoutonFen) && pos_actuelle == DANS_JOUER){     
                    bouton_select = 0;                             
                    pos_actuelle = DANS_CREER;
                    modifications = 1;
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
                    pos_actuelle = SORTIE_MENU;                                  
                } 
                
                //bouton rejoindre partie (après saisie de l'ip)
                else if(SDL_PointInRect(&point, &tab_img[23].posBoutonFen) && pos_actuelle == DANS_REJOINDRE){

                    //application d'une regex sur l'ip saisie 
                    regex_t regex;
                    int resultRegex = 0;

                    // Compilation de la regex
                    if (regcomp(&regex, "^((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$", REG_EXTENDED)) {
                        fprintf(stderr, "Erreur de compilation de la regex\n");
                        return 0;
                    }

                    resultRegex = regexec(&regex, saisieIp, 0, NULL, 0);

                    // Libération de la mémoire de la regex
                    regfree(&regex);
                    
                    if(!resultRegex){
                        retour = JOUER;
                        pos_actuelle = SORTIE_MENU;
                    }

                    else{
                        pos_actuelle = BAD_IP;
                        modifications = 1;   
                    }
                }
            }
        }
        
        if(modifications){
            modifications = 0;
            aff_menu(&pos_actuelle, tabBoutons[pos_actuelle], bouton_select);
        }
        frame = SDL_GetTicks() - start;
        if (frame < 16) SDL_Delay(16 - frame);
    }
    strcpy(classe, tab_perso[actuel]);  

    //libération des textures, images et textes
    for(int i = 0 ; i < NB_TEXTE ; i++){
        if(tab_texte[i].message){
            SDL_DestroyTexture(tab_texte[i].message);
            tab_texte[i].message = NULL;        
        }
    } 
    for(int i = 0 ; i < NB_IMG ; i++){
        detruit_img(i);
    } 
    for(int i = 0 ; i < nb_perso_ajoutes ; i++){
        free(tab_perso[i]);
    }
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
    }
    
    return retour;
}





int main(void){
    char classe[50];

    printf("\nRetrour menu : %d | ", menu(classe)); 
    printf("Pseudo : %s | Classe : %s | Ip : %s|\n", nomJoueur, classe, saisieIp);
    
    end(0);
    return 0;
}
    

/*pour tester l'affichage de l'inventaire
int main(void){
    init_sdl();

    perso_t perso;
    creer_perso(&perso, tank, "nom", 0, 0);

    ajouter_objet_joueur(&perso, 1);
    ajouter_objet_joueur(&perso, 3);

    show_inventaire(&perso, renderer);
    SDL_Delay(1000);
    return 0;
}
*/