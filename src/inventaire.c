#include "inventaire.h"




SDL_Rect inventaire[5] = {(SDL_Rect){600, 990, 75, 75},
                    (SDL_Rect){800, 990, 75, 75},
                    (SDL_Rect){1000, 990, 75, 75},
                    (SDL_Rect){1200, 990, 75, 75},
                    (SDL_Rect){1400, 990, 75, 75}};

char * chemin_objet(objet_t * obj){
    if (!strcmp(obj->nom, "Baguette du magicien")) return "../img/Objets/Baguette du magicien.jpg";
    if (!strcmp(obj->nom, "Epee lourde")) return "../img/Objets/Epee lourde.jpg";
    if (!strcmp(obj->nom, "Bague du magicien")) return "../img/Objets/Bague du magicien.jpg";
    if (!strcmp(obj->nom, "Bottes du magicien")) return "../img/Objets/Bottes du magicien.jpg";
    if (!strcmp(obj->nom, "Bracelet du GOAT")) return "../img/Objets/Bracelet du GOAT.jpg";
    if (!strcmp(obj->nom, "Bague du mage noir")) return "../img/Objets/Bague du mage noir.jpg";
    if (!strcmp(obj->nom, "Baguette runique")) return "../img/Objets/Baguette runique.jpg";
    if (!strcmp(obj->nom, "Gants du combattant")) return "../img/Objets/Gants du combattant.jpg";
    if (!strcmp(obj->nom, "Gants en acier")) return "../img/Objets/Gants en acier.jpg";
    if (!strcmp(obj->nom, "Casque du gardien")) return "../img/Objets/Casque du gardien.jpg";
    if (!strcmp(obj->nom, "Gants renforces")) return "../img/Objets/Gants renforces.jpg";
    if (!strcmp(obj->nom, "Bottes du vent")) return "../img/Objets/Bottes du vent.jpg";
    if (!strcmp(obj->nom, "Charme du destin")) return "../img/Objets/Charme du destin.jpg";
    if (!strcmp(obj->nom, "Anneau du hasard")) return "../img/Objets/Anneau du hasard.jpg";

    if (!strcmp(obj->nom, "Talisman des arcanes")) return "../img/Objets/Talisman des arcanes.jpg";
    if (!strcmp(obj->nom, "Anneau de sagesse")) return "../img/Objets/Anneau de sagesse.jpg";
    if (!strcmp(obj->nom, "Epee des tempetes")) return "../img/Objets/Epee des tempetes.jpg";
    if (!strcmp(obj->nom, "Plastron du roc")) return "../img/Objets/Plastron du roc.jpg";
    if (!strcmp(obj->nom, "Bottes en acier")) return "../img/Objets/Bottes en acier.jpg";
    if (!strcmp(obj->nom, "Anneau de velocite")) return "../img/Objets/Anneau de velocite.jpg";
    if (!strcmp(obj->nom, "Bracelet d'agilité")) return "../img/Objets/Bracelet d'agilité.jpg";
    if (!strcmp(obj->nom, "Sacoche du vagabond")) return "../img/Objets/Sacoche du vagabond.jpg";

    if (!strcmp(obj->nom, "Tome des anciens")) return "../img/Objets/Tome des anciens.jpg";
    if (!strcmp(obj->nom, "Ceinture du colosse")) return "../img/Objets/Ceinture du colosse.jpg";
    if (!strcmp(obj->nom, "Cape du sprinteur")) return "../img/Objets/Cape du sprinteur.jpg";
    if (!strcmp(obj->nom, "Lance des cieux")) return "../img/Objets/Lance des cieux.jpg";
    if (!strcmp(obj->nom, "Epee du roi dechu")) return "../img/Objets/Epee du roi dechu.jpg";
    if (!strcmp(obj->nom, "Medaillon porte-bonheur")) return "../img/Objets/Medaillon porte-bonheur.jpg";

    if (!strcmp(obj->nom, "Marteau du titan")) return "../img/Objets/Marteau du titan.jpg";
    if (!strcmp(obj->nom, "Orbe divine")) return "../img/Objets/Orbe divine.jpg";
    if (!strcmp(obj->nom, "Bouclier du dragon")) return "../img/Objets/Bouclier du dragon.jpg";
    if (!strcmp(obj->nom, "Bottes celestes")) return "../img/Objets/Bottes celestes.jpg";
    if (!strcmp(obj->nom, "Talisman de la fortune")) return "../img/Objets/Talisman de la fortune.jpg";
    if (!strcmp(obj->nom, "Orbe mystique")) return "../img/Objets/Orbe mystique.jpg";
    if (!strcmp(obj->nom, "Baton du sorcier-roi")) return "../img/Objets/Baton du sorcier-roi.jpg";
    if (!strcmp(obj->nom, "Cuirasse du paladin")) return "../img/Objets/Cuirasse du paladin.jpg";
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
                    
                    

