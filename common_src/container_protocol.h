#ifndef CONTAINER_PROTOCOL_H
#define CONTAINER_PROTOCOL_H

#include <string>
#include <utility>

#include "common_socket.h"
#include "protocol.h"

// Clase que contiene un protocolo para poder ser utilizado en el monitor de matches
// La idea de esto es no hacer al protocolo shared_ptr, ya que el monitor de matches se encarga de
// liberar la memoria de los protocolos Al no usar shared_ptr sobre el protocolo, se evita el
// overhead asociado con la contabilidad de referencias y la posible sincronización entre hilos.
struct ContainerProtocol {
    Protocol protocol;
    explicit ContainerProtocol(Socket&& socket): protocol(std::move(socket)) {}
    ContainerProtocol(const std::string& hostname, const std::string& servname):
            protocol(hostname, servname) {}
    ~ContainerProtocol() {}
};

#endif
