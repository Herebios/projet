

SDL_Rect inventaire[5] = {(SDL_Rect){600, 970, 100, 100},
                    (SDL_Rect){800, 970, 100, 100},
                    (SDL_Rect){1000, 970, 100, 100},
                    (SDL_Rect){1200, 970, 100, 100},
                    (SDL_Rect){1400, 970, 100, 100}};



void show_inventaire(SDL_Rect * inv){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int i = 0 ; i < 5 ; i++){
        for(int i = 0 ; i < 5 ; i++){
            SDL_RenderDrawRect(renderer, &inv[i]);
            inv[i].x += 1;
            inv[i].y += 1;
        }
    }
    SDL_RenderPresent(renderer);
}

