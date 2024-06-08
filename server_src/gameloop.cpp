#include "gameloop.h"

#define EXTRA_HEALTH ConfigSingleton::getInstance().get_extra_health()

Gameloop::Gameloop(Queue<std::shared_ptr<Command>>& client_cmds_queue,
                   BroadcasterSnapshots& broadcaster_snapshots, std::list<Player*>& players,
                   Map& map, bool* playing):
        client_cmds_queue(client_cmds_queue),
        broadcaster_snapshots(broadcaster_snapshots),
        players(players),
        map(map),
        playing(playing),
        game_ended(false) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Gameloop::send_initial_snapshots() {
    // Se debe leer el mapa elegido por el usuario y crearlo
    Snapshot snapshot = map.get_init_snapshot();

    // Enviar el snapshot inicial
    push_all_players(snapshot);
}

void Gameloop::push_all_players(const Snapshot& snapshot) {
    // Enviar a cada jugador la snapshot
    broadcaster_snapshots.broadcast(std::make_shared<Snapshot>(snapshot));
}

void Gameloop::run() {
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    while (playing) {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::shared_ptr<Command> game_command;
            while (client_cmds_queue.try_pop(game_command)) {
                game_command->execute_Command(map);
            }

            map.update();

            push_all_players(map.get_snapshot());

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            if (FRAME_DELAY > duration.count()) {
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(FRAME_DELAY - duration.count()));
            }
            check_players();

        } catch (ClosedQueue& err) {
            *playing = false;
        } catch (const std::exception& e) {
            std::cerr << "Error in gameloop: " << e.what() << std::endl;
            *playing = false;
        }
    }
}

void Gameloop::stop() { *playing = false; }

void Gameloop::check_players() {
    if (broadcaster_snapshots.is_empty()) {
        *playing = false;
    }
}