#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../common_src/container_protocol.h"
#include "../game_src/constants_game.h"

// Estrucutra que contiene la informacion de un jugador particular, contiene el id del jugador, el
// nombre del personaje y el protocolo de comunicacion. Se utiliza para mantener la informacion de
// los jugadores.
struct PlayerInfo {

    const int playerID;
    ChampionType character_name;
    std::shared_ptr<ContainerProtocol> container_protocol;
    std::string player_name;

    PlayerInfo(int playerID, ChampionType character_name,
               std::shared_ptr<ContainerProtocol> container_protocol,
               const std::string& player_name):
            playerID(playerID),
            character_name(character_name),
            container_protocol(container_protocol),
            player_name(player_name) {}

    int get_player_id() const { return playerID; }

    ChampionType get_character_name() const { return character_name; }

    std::shared_ptr<ContainerProtocol> get_container_protocol() const { return container_protocol; }

    std::string get_player_name() const { return player_name; }

    ~PlayerInfo() = default;
};

#endif
