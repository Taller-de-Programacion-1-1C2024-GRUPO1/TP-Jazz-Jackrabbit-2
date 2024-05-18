#include "client.h"


Client::Client(const std::string& host, const std::string& service):
        protocol(std::move(host), std::move(service)), listener(protocol), drawer(protocol) {}

void Client::run() {


    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error al iniciar SDL: " << SDL_GetError() << std::endl;
        return;
    } else {
        drawer.start();
        listener.start();
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line == "q") {
                // VER QUE HACER ACA

                //  joins??
                break;
            }
        }

    }


}

bool Client::action_handler(std::pair<uint8_t, int> result) {
    if (result.first == READ && result.second > 0) {
        read_handler(result.second);
        return true;
    } else if (result.first == ATACK) {
        if (this->protocol.send_byte(result.first)) {
            return true;
        }
        std::cout << "Error al enviar el byte o Server cerrado." << std::endl;
        return false;
    } else if (result.first == EXIT) {
        return false;
    } else {
        // std::cout << "La palabra no se encuentra en el mapeo." << std::endl;
        return true;
    }
}


void Client::read_handler(int num_msgs_to_read) {
    for (int i = 0; i < num_msgs_to_read; i++) {
        Message msg;
        this->protocol.get_msg(msg);
        // Imprimir el mensaje
        std::cout << "Un enemigo ha ";
        if (msg.event_type == EVENT_DEAD_8) {
            std::cout << "muerto. ";
        } else if (msg.event_type == EVENT_RESURRECT_8) {
            std::cout << "revivido. ";
        } else {
            std::cout << "ocurrido un evento desconocido ";
        }
        std::cout << msg.num_alive_enemies << " vivo(s) y " << msg.num_dead_enemies << " muerto(s)."
                  << std::endl;
    }
}


Client::~Client() { 
    //  joins??
    SDL_Quit();
    this->protocol.~ClientProtocol(); 
}
