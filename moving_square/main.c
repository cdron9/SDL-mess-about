#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>

// Position struct for squares pixel co-ords. 
// can either update with helper function for creating effects such as gravity.
// or can iterate position x and y according to keyboard input
typedef struct {
    float x, y;
} Position;

Position pos = {0, 0};

void input_handling(SDL_Event event, Position* pos);

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
            switch (event.type) {
                case SDL_EVENT_QUIT: 
                        done = true; 
                        break;
                case SDL_EVENT_KEY_DOWN:
                    if (pos.x < 0) { 
                        pos.x = 0; 
                        break; }
                    else if (pos.y < 0) {
                        pos.y = 0;
                        break;
                    }                               
                    else {     
                        input_handling(event, &pos);
                    }
                    break;
            }
        }

        // --- Rendering takes places all in loop ---

        // clear screen and create background color
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderClear(renderer);

        // set draw color for objects
        SDL_SetRenderDrawColor(renderer, 255,0,0,255); // should be red

        // define the rectangle and render it
        SDL_FRect rect = {pos.x,pos.y,100,100}; // read documentation on this 
        SDL_RenderFillRect(renderer, &rect);

        // finally update screen
        SDL_RenderPresent(renderer);

        // optional, delay can be added to control frame rate. see how works without then maybe add 
    }
    
    // ALWAYS REMEMBER TO CALL DESTROY AND QUIT FOR MEMORY SAFETY.
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}





void input_handling(SDL_Event event, Position* pos) {

    if (event.key.key == SDLK_W) {              // W and S are inverse?
        pos->y--;                               
    }                                            
    else if (event.key.key == SDLK_S) {
        pos->y++;
    }
    else if (event.key.key == SDLK_D) {
        pos->x++;
    }
    else if (event.key.key == SDLK_A) {
        pos->x--;
    }
}