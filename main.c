#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]) {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldnt intitialise sdl: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Quit();
return 0;
}