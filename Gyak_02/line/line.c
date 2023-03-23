#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define MAX_LINE_COUNT 10

typedef struct {
    int x1, y1;
    int x2, y2;
    SDL_Color color;
} Line;

SDL_Window *window;
SDL_Renderer *renderer;
Line lines[MAX_LINE_COUNT];
int line_count = 0;

void draw_line(Line line)
{
    SDL_SetRenderDrawColor(renderer, line.color.r, line.color.g, line.color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, line.x1, line.y1, line.x2, line.y2);
}

void draw_lines()
{
    for (int i = 0; i < line_count; i++) {
        draw_line(lines[i]);
    }
}


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Line Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Event event;
    int quit = 0;

    while (!quit) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Rajzoljuk meg a korábbi vonalakat
        draw_rect();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (line_count < MAX_LINE_COUNT) {
                        lines[line_count].x1 = event.button.x;
                        lines[line_count].y1 = event.button.y;
                        lines[line_count].x2 = event.button.x + 100;
                        lines[line_count].y2 = event.button.y + 100;
                        lines[line_count].color = (SDL_Color){rand()%256, rand()%256, rand()%256, SDL_ALPHA_OPAQUE};
                        line_count++;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    printf("Mouse position: %d, %d\n", event.motion.x, event.motion.y);
                    break;
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
