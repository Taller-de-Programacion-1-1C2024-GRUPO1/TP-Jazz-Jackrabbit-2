#include <chrono>
#include <iostream>
#include <thread>

#include "../game_src/entities/bullet.h"
#include "../game_src/entities/character.h"
#include "../game_src/entities/enemy.h"
#include "../game_src/entities/item.h"
#include "../game_src/entities/rabbit.h"
#include "../game_src/manager.h"
#include "SDL2/SDL.h"

#include "physical_map.h"

#define FPS 60
#define FRAME_DELAY (1000 / FPS)

/*
FUERA DE ESTA CARPETA, EN LA PRINCIPAL:
    g++ -g -std=c++17 game_src/entities/*.cpp game_src/*.cpp physics_src/*.cpp -I. -o prog.o -lSDL2 -ldl
*/
bool running = true;

void handleEvents(Rabbit& player) {
    SDL_Event event;
    const Uint8* state = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
    if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_RIGHT]) {
        player.run_fast_right();
    } else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_LEFT]) {
        player.run_fast_left();
    } else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) {
        player.add_run_left();
        player.add_jump();
    } else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) {
        player.add_jump();
        player.add_run_right();
    } else if (state[SDL_SCANCODE_RIGHT]) {
        player.add_run_right();
    } else if (state[SDL_SCANCODE_LEFT]) {
        player.add_run_left();
    } else if (state[SDL_SCANCODE_UP]) {
        player.add_jump();
    } else if (state[SDL_SCANCODE_ESCAPE]) {
        running = false;
    } else if (state[SDL_SCANCODE_SPACE]) {
        player.add_shoot();
    }
}



int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "No se pudo inicializar SDL: " << SDL_GetError() << std::endl;
        return 4;
    }

    // Crea una ventana
    SDL_Window* window = SDL_CreateWindow("Juego", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          800, 800, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "No se pudo crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 4;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -4, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "No se pudo crear el renderizador: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 4;
    }

    int map[MAP_WIDTH * MAP_HEIGHT] = {
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
            4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 2, 4, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2,
            4, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 4, 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 4, 4, 0, 0, 0,
            0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    PhysicalMap gameMap(map);
    Manager manager(gameMap);

    Rabbit player(70, 2, gameMap);
    manager.add_player(&player);

    Enemy enemy(70, 9, gameMap);
    manager.add_enemy(&enemy);

    Uint32 frameStart;

    // GameloopTests gameloop(manager, gameMap, renderer, player, &running);
    // gameloop.run();
    
    while (running) {
        auto start = std::chrono::high_resolution_clock::now();

        // HANDLE EVENTS -> TECLADO
        handleEvents(player);
        // UPDATES -> TODOS LOS UPDATES DE LAS ENTIDADES
        manager.update();
        // RENDER
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Limpia la pantalla con color negro
        SDL_RenderClear(renderer);
        // ACA VAN TODOS LOS RENDER DE LAS ENTIDADES

        manager.render(renderer), SDL_RenderPresent(renderer);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);


        if (FRAME_DELAY > duration.count()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY - duration.count()));
        }
    }  
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
