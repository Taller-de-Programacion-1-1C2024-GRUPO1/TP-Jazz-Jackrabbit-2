#include "bullet.h"
#include "character.h"
#include "item.h"
#include "physical_map.h"
#include "SDL2/SDL.h"
#include <iostream>

//COMPILACION:
// g++ -g -std=c++17 *.cpp -I.include -o prog -lSDL2 -ldl
//-L/path/to/sdl/library -lSDL2_image -L/path/to/sdl_image/library -lSDL2_mixer 

bool running = true;

void handleEvents(Player player) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_RIGHT:
                player.run_right();
                break;
            case SDLK_LEFT:
                player.run_left();
                break;
            case SDLK_UP:
                player.jump();
                break;
            case SDLK_DOWN:

                break;
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_SPACE:
                player.run_fast_right();
                break;
            }
        }
        if (event.type == SDL_KEYUP) {
            //No se está presionando ninguna tecla (Stand)
        }
    }
}

int main(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "No se pudo inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Crea una ventana
    SDL_Window* window = SDL_CreateWindow("Juego", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "No se pudo crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "No se pudo crear el renderizador: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int map[10*10] = {
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,1,1,1,2,0,0,0,0,1,
        1,0,0,0,0,2,0,0,0,1,
        1,0,0,0,0,0,2,1,1,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1
    };
    PhysicalMap gameMap;
    gameMap.load_map(map);
    Player player(2, 2, gameMap);
    Enemy enemy(9, 9, gameMap);

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while (running) {
        frameStart = SDL_GetTicks();

        //HANDLE EVENTS -> TECLADO
        handleEvents(player);
        //UPDATES -> TODOS LOS UPDATES DE LAS ENTIDADES
        player.update();
        //RENDER
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Limpia la pantalla con color negro
        SDL_RenderClear(renderer);
        //ACA VAN TODOS LOS RENDER DE LAS ENTIDADES
        player.render(renderer);
        enemy.render(renderer),
        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

