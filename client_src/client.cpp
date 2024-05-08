#include "client.h"


Client::Client(const std::string& host, const std::string& service):
        protocol(std::move(host), std::move(service)) {}


void Client::run() {
    std::string line;
    while (std::getline(std::cin, line)) {

        if (this->protocol.is_close()) {
            std::cout << "El servidor se ha desconectado." << std::endl;
            break;
        }
        std::pair<uint8_t, int> serialized_line = this->parser.line_to_bytes_parser(line);
        if (!action_handler(serialized_line)) {
            break;
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


Client::~Client() { this->protocol.~ClientProtocol(); }
