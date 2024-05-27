#include <iostream>

#include "../game_src/entities/bullet.h"
#include "../game_src/entities/character.h"
#include "../game_src/entities/enemy.h"
#include "../game_src/entities/item.h"
#include "../game_src/entities/player.h"
#include "../game_src/manager.h"
#include "SDL2/SDL.h"

#include "physical_map.h"

/*
FUERA DE ESTA CARPETA, EN LA PRINCIPAL:
    g++ -g -std=c++17 game_src/entities/*.cpp game_src/*.cpp physics_src/*.cpp -I. -o prog.o -lSDL2 -ldl
*/
bool running = true;

void handleEvents(Player& player) {
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
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "No se pudo inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Crea una ventana
    SDL_Window* window = SDL_CreateWindow("Juego", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          800, 800, SDL_WINDOW_SHOWN);
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

    int map[MAP_WIDTH * MAP_HEIGHT] = {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0,
            0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 0, 0,
            0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    PhysicalMap gameMap(map);
    Manager manager(gameMap);

    Player player(70, 2, gameMap);
    manager.add_player(&player);

    Enemy enemy(9, 9, gameMap);
    manager.add_enemy(&enemy);

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;


    while (running) {
        int frameTime;
        frameStart = SDL_GetTicks();

        // HANDLE EVENTS -> TECLADO
        handleEvents(player);
        // UPDATES -> TODOS LOS UPDATES DE LAS ENTIDADES
        manager.update();
        // RENDER
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Limpia la pantalla con color negro
        SDL_RenderClear(renderer);
        // ACA VAN TODOS LOS RENDER DE LAS ENTIDADES

        manager.render(renderer), SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
