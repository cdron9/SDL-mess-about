#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>
#include <math.h>

// based on midpoint circle algorithm
// Video explaining the algorithm...
// https://youtu.be/hpiILbMkF9w 

void DrawCircle(SDL_Renderer *renderer, int cx, int cy, int radius);
void DrawFilledCircle(SDL_Renderer *renderer, int cx, int cy, int radius);

int main(int argc, char* argv[]) {

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    bool quit = false;
    SDL_Event e;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldnt initialise SDL: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("circles window", 640,480,0); // 0 for no flags
    renderer = SDL_CreateRenderer(window,NULL); //null let adl autopick rendering driver

    if (window == NULL || renderer == NULL) {
        SDL_Log("Failed to open window or renderer: %s\n", SDL_GetError());
        return 1;
    }

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,0,0,255);

        DrawCircle(renderer, 400, 300, 40);
        DrawFilledCircle(renderer,100, 100, 40);

        SDL_RenderPresent(renderer);
        
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void DrawCircle(SDL_Renderer *renderer, int cx, int cy, int radius) {
    int x = radius;
    int y = 0;
    int decision = 1 - x;

    while (y<= x) {
        SDL_RenderPoint(renderer,  cx + x, cy + y);
        SDL_RenderPoint(renderer,  cx + y, cy + x);
        SDL_RenderPoint(renderer,  cx - y, cy + x);
        SDL_RenderPoint(renderer,  cx - x, cy + y);
        SDL_RenderPoint(renderer,  cx - x, cy - y);
        SDL_RenderPoint(renderer,  cx - y, cy - x);
        SDL_RenderPoint(renderer,  cx + y, cy - x);
        SDL_RenderPoint(renderer,  cx + x, cy - y);

        y++;

        if (decision <= 0)
            decision += 2 * y + 1;
        else {
            x--;
            decision += 2 * (y-x) + 1;
        }
    }
}

void DrawFilledCircle(SDL_Renderer *renderer, int cx, int cy, int radius) {
    int x = radius;
    int y = 0;
    int decision = 1 - x;

    while (y <= x ) {
        SDL_RenderLine(renderer, cx - x, cy + y, cx + x, cy + y);
        SDL_RenderLine(renderer, cx - x, cy - y, cx + x, cy - y);
        SDL_RenderLine(renderer, cx - y, cy + x, cx + y, cy + x);
        SDL_RenderLine(renderer, cx - y, cy - x, cx + y, cy - x);

        y++;

        if (decision <= 0)
            decision += 2 * y + 1;
        else {
            x--;
            decision += 2 * (y-x) + 1;
        }
    }
}
    