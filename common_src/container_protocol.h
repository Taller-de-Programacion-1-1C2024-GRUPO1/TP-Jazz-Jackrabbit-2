#ifndef CONTAINER_PROTOCOL_H
#define CONTAINER_PROTOCOL_H

#include <string>
#include <utility>

#include "common_socket.h"
#include "protocol.h"

/*
Teniamos un error con el uso de Queue<Protocol&> en la clase MatchInfo. Por ende, decidimos crear
esta clase para poder utilizar un contenedor de protocolos en el monitor de matches.
El error que estabamos viendo se debe a que intentantamos utilizar un objeto que utiliza
un contenedor estándar de C++ (en este caso, std::queue o std::deque) para almacenar referencias
(Protocol&). Los contenedores estándar de C++ no soportan referencias directamente; en su lugar,
deben contener objetos o punteros.
*/

struct ContainerProtocol {
    Protocol protocol;
    explicit ContainerProtocol(Socket&& socket): protocol(std::move(socket)) {}
    ContainerProtocol(const std::string& hostname, const std::string& servname):
            protocol(hostname, servname) {}
    ~ContainerProtocol() {}
};

#endif
