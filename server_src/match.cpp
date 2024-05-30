#include "match.h"

#define MAX_PLAYERS ConfigSingleton::getInstance().getMaxPlayers()

Match::Match(std::shared_ptr<Queue<std::shared_ptr<ContainerProtocol>>> matches_protocols_queue,
             const std::string& match_name, bool* playing, int* status):
        match_name(match_name),
        matches_protocols_queue(matches_protocols_queue),
        playing(playing),
        status(status),
        id_counter(0) {
    // number_of_player = game_map.get_number_of_players();
    srand(static_cast<unsigned int>(time(nullptr)));
}

uint8_t Match::get_number_of_players() { return id_counter; }

void Match::send_game_initial(Game game) {
    std::shared_ptr<Snapshot> init_snapshot = game.get_initial_snapshot(map);
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

void Match::run() {
    Queue<std::shared_ptr<Command>> clients_cmd_queue(QUEUE_MAX_SIZE);
    BroadcasterSnapshots broadcaster_snapshots;
    try {
        for (int cont = 0; cont < number_of_players; cont++) {
            if (has_started())
                throw MatchAlreadyStarted();
            if (number_of_players >= MAX_PLAYERS)
                throw MatchFull();
            int current_id = id_counter;

            // Desencolo el protocolo de los jugadores que se conectaron
            std::shared_ptr<ContainerProtocol> container_protocol = matches_protocols_queue->pop();

            // game_map.add_player(current_id);
            Player* player = new Player(container_protocol, current_id, broadcaster_snapshots,
                                        clients_cmd_queue);
            player->start();

            players.push_back(player);
            id_counter++;
        }
        // crear el mapa

        // hay que agregar el game_map
        Game game = Game(clients_cmd_queue, broadcaster_snapshots, players, playing);
        *status = MATCH_ALIVE;
        send_game_initial(game);
        game.run();

        clients_cmd_queue.close();
        delete_players();
        *status = MATCH_OVER;

    } catch (const ClosedQueue& err) {
        std::cerr << "Error: " << err.what() << std::endl;
    }
}

void Match::delete_players() {
    for (auto& player: players) {
        if (!player->is_dead()) {
            player->kill();
        }
        delete player;
    }
    players.clear();
}

bool Match::has_started() { return status; }

std::string Match::get_match_name() { return this->match_name; }

Match::~Match() {}
