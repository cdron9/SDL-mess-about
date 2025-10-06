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

void handle_input (SDL_Event event, bool *w, bool *a, bool *s, bool *d);

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


    if (window == NULL || renderer == NULL) {
            SDL_Log("Couldnt create widnow: %s\n", SDL_GetError());
            return 1;
        }

    Position pos = {270, 190};
    float speed = 300.0f; // pixels per second for movement
    bool w = false, a = false, s = false, d = false;

    Uint64 lastTime = SDL_GetTicks();

    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                done = true;
            else if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP)
                handle_input(event, &w,&a,&s,&d);
        }

        // movement for each frame
        Uint64 currentTime = SDL_GetTicks();
        float delta = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        if (w) pos.y -= speed * delta;
        if (s) pos.y += speed * delta;
        if (a) pos.x -= speed * delta;
        if (d) pos.x += speed * delta;

        // bounds checking
        if (pos.x < 0) pos.x = 0;
        if (pos.y < 0) pos.y = 0;
        if (pos.x > 540) pos.x = 540;
        if (pos.y > 380) pos.y = 380;

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


void handle_input (SDL_Event event, bool *w, bool *a, bool *s, bool *d) {
    bool pressed = (event.type == SDL_EVENT_KEY_DOWN);

    switch (event.key.key) {
        case SDLK_W: *w = pressed; break;
        case SDLK_A: *a = pressed; break;
        case SDLK_S: *s = pressed; break;
        case SDLK_D: *d = pressed; break;
        default: break;
    }
}


