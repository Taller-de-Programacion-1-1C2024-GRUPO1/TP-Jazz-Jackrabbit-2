#include "protocol.h"

// Protocol
Protocol::Protocol(const std::string& host, const std::string& service):
        hostname(host), servname(service), socket(host.c_str(), service.c_str()) {}


Protocol::Protocol(Socket peer): socket(std::move(peer)), was_closed(false) {}


bool Protocol::is_close() { return this->was_closed; }

Protocol::~Protocol() {
    this->was_closed = true;
    this->socket.~Socket();
}
