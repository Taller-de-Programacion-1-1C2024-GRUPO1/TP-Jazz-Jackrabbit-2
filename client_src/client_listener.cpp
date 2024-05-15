#include "client_listener.h"


ClientListener::ClientListener(ClientProtocol& protocol):
        protocol(protocol), keep_talking(true), is_alive(true) {}

void ClientListener::run() {
    while (keep_talking) {
        try {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    keep_talking = false;
                }
                if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_RIGHT:  // Si la tecla presionada es la flecha derecha
                            std::cout << "derecha" << std::endl;
                            /// this->protocol.send(derecha)
                            break;

                        case SDLK_LEFT:

                            break;

                        case SDLK_ESCAPE:
                            keep_talking = false;  // Cierra el juego

                            break;
                        case SDLK_UP:

                            break;
                        case SDLK_DOWN:

                            break;
                    }
                }
                // Aquí puedes manejar otros eventos como teclas presionadas, etc.
            }
        }


        catch (const std::exception& e) {
            std::cerr << "SENDER: No pude recibir comando o se cerro el cliente forzadamente"
                      << std::endl;
            break;
        }
    }
    this->is_alive = false;
}


bool ClientListener::is_dead() { return !this->is_alive; }

void ClientListener::kill() {
    this->keep_talking = false;
    // q_msgs.close();
}
