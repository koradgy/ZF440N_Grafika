#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define MAX_RECTANGLES 100

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL Rectangles on Mouse Click",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    int quit = 0;
    int num_rectangles = 0;
    SDL_Rect rectangles[MAX_RECTANGLES];

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (num_rectangles < MAX_RECTANGLES) {
                        int x = event.button.x;
                        int y = event.button.y;
                        SDL_Rect rect = {x, y, 50, 50};
                        rectangles[num_rectangles++] = rect;
                    }
                    break;
            }
        }

        // Draw the rectangles on the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        for (int i = 0; i < num_rectangles; i++) {
            SDL_RenderFillRect(renderer, &rectangles[i]);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
