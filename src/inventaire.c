#include "inventaire.h"
//#define RECT_INVENTAIRE (W - H) * 0.2
#define RECT_INVENTAIRE 50


SDL_Rect inventaire[5] = {(SDL_Rect){W * 0.31, H * 0.91, RECT_INVENTAIRE, RECT_INVENTAIRE},
                    (SDL_Rect){W * 0.41, H * 0.91, RECT_INVENTAIRE, RECT_INVENTAIRE},
                    (SDL_Rect){W * 0.52, H * 0.91, RECT_INVENTAIRE, RECT_INVENTAIRE},
                    (SDL_Rect){W * 0.62, H * 0.91, RECT_INVENTAIRE, RECT_INVENTAIRE},
                    (SDL_Rect){W * 0.73, H * 0.91, RECT_INVENTAIRE, RECT_INVENTAIRE}};

char * chemin_objet(objet_t * obj){
    char * chaine = malloc(strlen("img/Objets/") + strlen(obj->nom) + strlen(".jpg") + 1);
    strcpy(chaine, "img/Objets/");
    strcat(chaine, obj->nom);
    strcat(chaine, ".jpg");
    return chaine;
}



void show_inventaire(SDL_Renderer * renderer, perso_t * perso){
    //W et H sont des constantes de prepro.h
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Texture * texture1 = NULL,
                * texture2 = NULL,
                * texture3 = NULL,
                * texture4 = NULL,
                * texture5 = NULL;
                
    //printf("%d %d %d %d\n\n", inventaire[0].x, inventaire[0].y, inventaire[0].w, inventaire[0].h);
    if(perso->objets[0] != NULL){
        texture1 = IMG_LoadTexture(renderer, chemin_objet(perso->objets[0]));
    }

    if(perso->objets[1] != NULL){
        texture2 = IMG_LoadTexture(renderer, chemin_objet(perso->objets[1]));
    }

    if(perso->objets[2] != NULL){
        texture3 = IMG_LoadTexture(renderer, chemin_objet(perso->objets[2]));
    }

    if(perso->objets[3] != NULL){
        texture4 = IMG_LoadTexture(renderer, chemin_objet(perso->objets[3]));
    }

    if(perso->objets[4] != NULL){
        texture5 = IMG_LoadTexture(renderer, chemin_objet(perso->objets[4]));
    }

    int j;
    for(int i = 0 ; i < 5 ; i++){
        for(j = 0 ; j < 5 ; j++){
            //affichage des cases d'inventaire
            SDL_RenderDrawRect(renderer, &inventaire[i]);
            //on réduit la taille des rectangles pour que l'image soit à l'intérieur de la case d'inventaire
            inventaire[i].x += 1;
            inventaire[i].y += 1;
        }
        inventaire[i].w -= j;
        inventaire[i].h -= j;

    }
    //affichage de l'objet
    
    SDL_RenderCopy(renderer, texture1, NULL, &inventaire[0]);
    SDL_RenderCopy(renderer, texture2, NULL, &inventaire[1]);
    SDL_RenderCopy(renderer, texture3, NULL, &inventaire[2]);
    SDL_RenderCopy(renderer, texture4, NULL, &inventaire[3]);
    SDL_RenderCopy(renderer, texture5, NULL, &inventaire[4]);

    //on remet à la valeur initiale les coordonnées des rectangles
    for(int i = 0 ; i < 5 ; i++){
        for(j = 0 ; j < 5 ; j++){
            inventaire[i].x -= 1;
            inventaire[i].y -= 1;
        }
        inventaire[i].w += j;
        inventaire[i].h += j;
    }


    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
    SDL_DestroyTexture(texture5);

}
                    
                    

