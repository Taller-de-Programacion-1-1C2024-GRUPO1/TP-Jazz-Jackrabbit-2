#include "match.h"

Match::Match(std::shared_ptr<Queue<std::shared_ptr<PlayerInfo>>> matches_protocols_players_queue,
             std::shared_ptr<Map> map_recibido, const std::string& match_name, bool& server_running,
             int* status, int number_of_players):
        map(map_recibido),
        match_name(match_name),
        matches_protocols_players_queue(matches_protocols_players_queue),
        server_running(server_running),
        playing(true),
        status(status) {
    this->number_of_players = number_of_players;
    this->map->set_amount_players(number_of_players);
    this->map->create_entities();
    srand(static_cast<unsigned int>(time(nullptr)));
}

uint8_t Match::get_number_of_players() { return this->number_of_players; }

void Match::run() {
    Queue<std::shared_ptr<Command>> clients_cmd_queue(QUEUE_MAX_SIZE);
    BroadcasterSnapshots broadcaster_snapshots;
    try {
        for (int cont = 0; cont < number_of_players; cont++) {
            if (has_started())
                throw MatchAlreadyStarted();
            if (number_of_players > map->get_max_players())
                throw MatchFull();


            // Desencolo el protocolo de los jugadores que se conectaron
            std::shared_ptr<PlayerInfo> player_info = matches_protocols_players_queue->pop();
            // Agrego al jugador al mapa, seteando su id y champion a un rabbit particular
            map->add_player(player_info->get_player_id(), player_info->get_character_name(),
                            player_info->get_player_name());
            Player* player =
                    new Player(player_info->get_container_protocol(), player_info->get_player_id(),
                               broadcaster_snapshots, clients_cmd_queue);

            player->start();
            players.push_back(player);
        }
        // Ya se conectaron todos los jugadores, se envian los ids de cada uno
        send_players_ids();

        Gameloop gameloop = Gameloop(clients_cmd_queue, broadcaster_snapshots, players, map,
                                     server_running, playing);
        *status = MATCH_ALIVE;
        gameloop.send_initial_snapshots();
        gameloop.run();

        clients_cmd_queue.close();
        *status = MATCH_OVER;
        delete_players();

    } catch (const ClosedQueue& err) {
        std::cerr << "Error: " << err.what() << std::endl;
    }
}

void Match::send_players_ids() {
    for (auto& player: players) {
        player->send_player_id();
    }
}

void Match::delete_players() {
    for (auto& player: players) {
        if (!player->is_dead()) {
            player->kill();
        }
        player->join();
        delete player;
    }
    players.clear();
}

bool Match::has_started() { return (*status == MATCH_ALIVE); }

std::string Match::get_match_name() { return this->match_name; }

Match::~Match() { delete_players(); }
