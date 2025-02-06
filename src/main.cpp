#include <SDL2/SDL.h>
#include <iostream>

#include "renderer.h"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

int main(int argc, char* argv[]) {
    Renderer renderer(SCREEN_WIDTH , SCREEN_HEIGHT);

    // Create an array of pixels (RGBA format)
    Uint32 pixels[SCREEN_WIDTH * SCREEN_HEIGHT];

    // Fill pixel array with colors (Example: Gradient effect)
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            Uint8 red = (x * 255) / SCREEN_WIDTH;
            Uint8 green = (y * 255) / SCREEN_HEIGHT;
            Uint8 blue = 128;
            Uint8 alpha = 255; // Fully opaque
            pixels[y * SCREEN_WIDTH + x] = (alpha << 24) | (red << 16) | (green << 8) | blue;
        }
    }

    // Main loop
    bool running = true;
    SDL_Event event;
    while (running) {
        renderer.pollEvents();

        if(renderer.shouldQuit())
        {
            running = 0;
        }

        renderer.render(pixels,SCREEN_WIDTH * sizeof(Uint32));
    }

    return 0;
}
