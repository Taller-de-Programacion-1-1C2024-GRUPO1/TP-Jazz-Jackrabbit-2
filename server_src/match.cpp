#include "match.h"

Match::Match(std::shared_ptr<Queue<std::shared_ptr<PlayerInfo>>> matches_protocols_players_queue,
             const Map& map_recibido, const std::string& match_name, bool* playing, int* status,
             int number_of_players):
        map(map_recibido),
        match_name(match_name),
        matches_protocols_players_queue(matches_protocols_players_queue),
        playing(playing),
        status(status) {
    this->number_of_players = number_of_players;
    this->map.set_amount_players(number_of_players);
    this->map.create_entities();
    srand(static_cast<unsigned int>(time(nullptr)));
}

uint8_t Match::get_number_of_players() { return this->number_of_players; }

/*
void Match::send_game_initial(Gameloop game) {
    std::shared_ptr<Snapshot> init_snapshot = game.get_initial_snapshot();
    // Enviar a cada jugador su snapshot inicial
    for (auto& player: players) {
        Queue<std::shared_ptr<Snapshot>>& player_snapshot_queue = player->get_snapshots_queue();
        try {
            player_snapshot_queue.push(init_snapshot);
        } catch (const ClosedQueue& err) {
            continue;
        }
    }
}
*/

void Match::run() {
    Queue<std::shared_ptr<Command>> clients_cmd_queue(QUEUE_MAX_SIZE);
    BroadcasterSnapshots broadcaster_snapshots;
    try {
        for (int cont = 0; cont < number_of_players; cont++) {
            std::cout << "EL ESTADO DE LA PARTIDA ES" << status << std::endl;
            if (has_started())
                throw MatchAlreadyStarted();
            if (number_of_players >= map.get_max_players())
                throw MatchFull();

            // Desencolo el protocolo de los jugadores que se conectaron
            std::shared_ptr<PlayerInfo> player_info = matches_protocols_players_queue->pop();

            // Agrego al jugador al mapa, seteando su id y champion a un rabbit particular
            map.add_player(player_info->get_player_id(), player_info->get_character_name());
            Player* player =
                    new Player(player_info->get_container_protocol(), player_info->get_player_id(),
                               broadcaster_snapshots, clients_cmd_queue);

            player->start();
            players.push_back(player);
        }
        // Ya se conectaron todos los jugadores, se envian los ids de cada uno
        std::cout << "SE ENVIAN PLAYER IDS A CADA PLAYER" << std::endl;
        send_players_ids();

        Gameloop gameloop =
                Gameloop(clients_cmd_queue, broadcaster_snapshots, players, map, playing);
        *status = MATCH_ALIVE;
        gameloop.send_initial_snapshots();
        gameloop.run();

        std::cout << "SE TERMINO TODOA" << std::endl;
        // clients_cmd_queue.close();
        std::cout << "SE TERMINO TODOB" << std::endl;
        *status = MATCH_OVER;
        std::cout << "SE TERMINO TODOC" << std::endl;
        delete_players();
        std::cout << "SE TERMINO TODOD" << std::endl;

    } catch (const ClosedQueue& err) {
        std::cerr << "Error: " << err.what() << std::endl;
    }
}

void Match::send_players_ids() {
    for (auto& player: players) {
        std::cout << "Player id: " << player->get_id() << std::endl;
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
