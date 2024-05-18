#include "client_drawer.h"

ClientDrawer::ClientDrawer(ClientProtocol& protocol):
        protocol(protocol), keep_talking(true), is_alive(true) {}

void ClientDrawer::run() {

            SDL_Window* window = SDL_CreateWindow("Ventana SDL con fondo rojo",
                                                SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                800, 600,
                                                SDL_WINDOW_SHOWN);
            if (!window) {
                std::cerr << "No se pudo crear la ventana: " << SDL_GetError() << std::endl;
                SDL_Quit();
                
            }


        
    while (keep_talking) {
        try {
            SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer) {
                std::cerr << "No se pudo crear el renderer: " << SDL_GetError() << std::endl;
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
               //std::cout << "Dibujando" << std::endl;

                // Establece el color de fondo (rojo)
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);

                // Mantén la ventana abierta durante 5 segundos
                SDL_Delay(5000);

                // Limpia los recursos y cierra SDL
                SDL_DestroyRenderer(renderer);



        }
        catch (const std::exception& e) {
            std::cerr << "SENDER: No pude recibir comando o se cerro el cliente forzadamente"
                      << std::endl;
            break;
        }
    }
    SDL_DestroyWindow(window);
    //SDL_Quit();
    this->is_alive = false;
}


bool ClientDrawer::is_dead() { return !this->is_alive; }

void ClientDrawer::kill() {
    this->keep_talking = false;
    // q_msgs.close();
}