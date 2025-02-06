#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Renderer
{
public:
    Renderer(int w,int h):width(w),height(h)
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            exit(1);
        }

        // Create window
        window = SDL_CreateWindow("Pixel Display", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                            width, height, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(1);
        }

        // Create renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
        
        if (!renderer || !texture) {
            std::cerr << "Renderer or Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(1);
        }

    }

    ~Renderer()
    {
        // Cleanup
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void pollEvents()
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                should_quit = 1;
            }
        }
    }

    void render(Uint32* pixels, size_t pixels_size)
    {
        // Update texture with new pixel data
        SDL_UpdateTexture(texture, nullptr, pixels, pixels_size);

        // Render
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

// Event Functions

    bool shouldQuit()
    {
        return should_quit;
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event event;

    int width,height;

    bool should_quit = 0;
};