#ifndef MATCH_STRUCT_H
#define MATCH_STRUCT_H

#include <vector>
#include <string>
#include <iostream>

#include "match.h"
#include "constants_server.h"

#include "../common_src/thread.h"
#include "../common_src/queue.h"
#include "../common_src/container_protocol.h"

#include "../game_src/map.h"

// Estrucutra que contiene la informacion de la partida, como el estado de la partida, el nombre del mapa, el match_starter y la cola de mensajes
struct MatchInfo {

    const std::string& map_name;
    int status = MATCH_WAITING; // se inicializa en waiting para que el match_starter no comience la partida
    std::unique_ptr<Match> match_starter;
    std::shared_ptr<Queue<std::shared_ptr<ContainerProtocol>>> matches_protocols_queue;

    MatchInfo(const std::string& match_name, std::shared_ptr<Map> map, std::shared_ptr<Queue<std::shared_ptr<ContainerProtocol>>> matches_protocols_queue, bool* playing) : 

        map_name(map->get_name()),
        /*  
            Se inicializa el match_starter con un puntero a un objeto Match 
            que se inicializa con:
            - el puntero a la cola de mensajes, 
            - el nombre del match, el mapa, 
            - el puntero al booleano playing y 
            - el puntero a status
        */
        match_starter(std::make_unique<Match>(matches_protocols_queue, match_name, playing, &status)), 

        matches_protocols_queue(matches_protocols_queue) {}

    ~MatchInfo() {}
};

#endif
