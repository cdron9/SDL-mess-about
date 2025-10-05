#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    bool done = false;
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldnt intitialise sdl: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("test window", 640, 480, SDL_WINDOW_BORDERLESS);

    
        if (window == NULL) {
            SDL_Log("Couldnt create widnow: %s\n", SDL_GetError());
            return 1;
        }

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}