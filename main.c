#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL; // set both to NULL as pointers.
    bool done = false;
    SDL_Event event;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldnt intitialise sdl: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    window = SDL_CreateWindow("test window", 640, 480, 0); // Pass flags as fourth arg, or 0 for no flags. 0 for now
    renderer = SDL_CreateRenderer(window, NULL); // NULL to let sdl auto pick the rendering driver (idk what that is)


    if (window == NULL) {
            SDL_Log("Couldnt create widnow: %s\n", SDL_GetError());
            return 1;
        }

    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }

        // --- Rendering takes places all in loop ---

        // clear screen and create background color
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderClear(renderer);

        // set draw color for objects
        SDL_SetRenderDrawColor(renderer, 255,0,0,255); // should be red

        // define the rectangle and render it
        SDL_FRect rect = {200,150,100,50}; // read documentation on this 
        SDL_RenderFillRect(renderer, &rect);

        // finally update screen
        SDL_RenderPresent(renderer);

        // optional, delay can be added to control frame rate below this. bnot needed as static program for now
    }
    
    // ALWAYS REMEMBER TO CALL DESTROY AND QUIT FOR MEMORY SAFETY.
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}