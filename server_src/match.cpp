#include "match.h"

Match::Match(std::shared_ptr<Queue<std::shared_ptr<ContainerProtocol>>> matches_protocols_queue,
             const Map& map, const std::string& match_name, bool* playing, int* status):
        map(map),
        match_name(match_name),
        matches_protocols_queue(matches_protocols_queue),
        playing(playing),
        status(status),
        id_counter(0) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

uint8_t Match::get_number_of_players() { return id_counter; }

void Match::send_game_initial(Gameloop game) {
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
            if (number_of_players >= map.get_max_players())
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
        // enviar a cada jugador su id
        send_players_ids();

        // esperar a que todos los jugadores elijan su personaje
        wait_for_players_to_choose_champion();

        // hay que agregar el game_map
        Gameloop gameloop = Gameloop(clients_cmd_queue, broadcaster_snapshots, players, playing);
        *status = MATCH_ALIVE;
        send_game_initial(gameloop);
        gameloop.run();

        clients_cmd_queue.close();
        delete_players();
        *status = MATCH_OVER;

    } catch (const ClosedQueue& err) {
        std::cerr << "Error: " << err.what() << std::endl;
    }
}

void Match::send_players_ids() {
    /*
    for (auto& player: players) {
        player->send_id();
    }
    */
}


void Match::wait_for_players_to_choose_champion() {
    /*
    for (auto& player: players) {
        player->wait_for_character();
    }
    */
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