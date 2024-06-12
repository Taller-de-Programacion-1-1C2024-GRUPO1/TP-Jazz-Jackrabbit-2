#ifndef CLIENT_ERROR_H
#define CLIENT_ERROR_H

#include <exception>
#include <iostream>
#include <string>

// Error commando inválido
class InvalidCommand: public std::exception {
public:
    InvalidCommand() {}
    ~InvalidCommand() {}
    virtual const char* what() const noexcept { return "Invalid command"; }
};

// Error de partida ya existente
class MatchAlreadyExists: public std::exception {
public:
    MatchAlreadyExists() {}
    ~MatchAlreadyExists() {}
    virtual const char* what() const noexcept { return "Match already exists"; }
};

// Error de partida no encontrada
class MatchNotFound: public std::exception {
public:
    MatchNotFound() {}
    ~MatchNotFound() {}
    virtual const char* what() const noexcept { return "Match not found"; }
};

// Error de partida llena
class MatchFull: public std::exception {
public:
    MatchFull() {}
    ~MatchFull() {}
    virtual const char* what() const noexcept { return "Match is full"; }
};

// Error de jugador ya existente
class PlayerNotFound: public std::exception {
public:
    PlayerNotFound() {}
    ~PlayerNotFound() {}
    virtual const char* what() const noexcept { return "Player not found"; }
};

// Error de partida ya iniciada
class MatchAlreadyStarted: public std::exception {
public:
    MatchAlreadyStarted() {}
    ~MatchAlreadyStarted() {}
    virtual const char* what() const noexcept { return "Match already started"; }
};

// Error de mapa no encontrado
class MapNotFound: public std::exception {
    const char* what() const noexcept override {
        return "Was not able to find Map with that id when creating the match";
    }
};

// Error de partida no iniciada
class NoJazzLeft: public std::exception {
public:
    NoJazzLeft() {}
    ~NoJazzLeft() {}
    virtual const char* what() const noexcept { return "No Jazz left"; }
};

// Error de conexión perdida con el servidor
class LostConnection: public std::exception {
public:
    LostConnection() {}
    ~LostConnection() {}
    virtual const char* what() const noexcept { return "Lost connection with the server"; }
};

// Error de cliente cerrado
struct ClientClosed: public std::runtime_error {
    ClientClosed(): std::runtime_error("Client is closed") {}
};

struct SocketClosed: public std::runtime_error {
    SocketClosed(): std::runtime_error("Socket is closed") {}
};

#endif
