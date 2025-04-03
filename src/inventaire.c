#include "inventaire.h"




SDL_Rect inventaire[5] = {(SDL_Rect){600, 990, 75, 75},
                    (SDL_Rect){800, 990, 75, 75},
                    (SDL_Rect){1000, 990, 75, 75},
                    (SDL_Rect){1200, 990, 75, 75},
                    (SDL_Rect){1400, 990, 75, 75}};

char * chemin_objet(objet_t * obj){
    char chaine[50] = "../img/Objets/";
    strcat(chaine, obj->nom);
    strcat(chaine, ".jpg");
    return strdup(chaine);
}



void show_inventaire(perso_t * perso, SDL_Renderer * renderer){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int j;
    SDL_Texture * texture1 = NULL,
                * texture2 = NULL,
                * texture3 = NULL,
                * texture4 = NULL,
                * texture5 = NULL;
                

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


    for(int i = 0 ; i < 5 ; i++){
        for(j = 0 ; j < 5 ; j++){
            //affichage des cases d'inventaire
            SDL_RenderDrawRect(renderer, &inventaire[i]);
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

    SDL_RenderPresent(renderer);


    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
    SDL_DestroyTexture(texture5);

}
                    
                    

