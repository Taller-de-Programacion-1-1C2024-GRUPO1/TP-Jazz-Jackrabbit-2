#include "gameloop.h"

#define EXTRA_HEALTH ConfigSingleton::getInstance().get_extra_health()

Gameloop::Gameloop(Queue<std::shared_ptr<Command>>& client_cmds_queue,
                   BroadcasterSnapshots& broadcaster_snapshots, std::list<Player*>& players,
                   std::shared_ptr<Map> map, bool& server_running, bool& playing):
        client_cmds_queue(client_cmds_queue),
        broadcaster_snapshots(broadcaster_snapshots),
        players(players),
        map(map),
        server_running(server_running),
        playing(playing),
        game_ended(false) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Gameloop::send_initial_snapshots() {
    Snapshot snapshot = map->get_init_snapshot();

    // Enviar el snapshot inicial
    push_all_players(snapshot);
}

void Gameloop::push_all_players(const Snapshot& snapshot) {
    // Enviar a cada jugador la snapshot
    broadcaster_snapshots.broadcast(std::make_shared<Snapshot>(snapshot));
}

void Gameloop::run() {
    auto game_start = std::chrono::high_resolution_clock::now();
    int game_duration_seconds = GAME_DURATION_MINUTES * UPDATE_RATE;

    while (playing && server_running) {
        try {
            auto start = std::chrono::high_resolution_clock::now();

            std::shared_ptr<Command> game_command;
            while (client_cmds_queue.try_pop(game_command)) {
                map->add_command(game_command);
            }

            map->update();

            uint32_t match_time =
                    std::chrono::duration_cast<std::chrono::seconds>(start - game_start).count();

            push_all_players(map->get_snapshot(game_duration_seconds - match_time));

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            if (DELTA_TIME > duration.count()) {
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(DELTA_TIME - duration.count()));
            }

            check_players();
            auto elapsed =
                    std::chrono::duration_cast<std::chrono::seconds>(end - game_start).count();

            if (elapsed >= game_duration_seconds) {
                stop();
            }

        } catch (ClosedQueue& err) {
            playing = false;
        } catch (const std::exception& e) {
            std::cerr << "Error in gameloop: " << e.what() << std::endl;
            playing = false;
        }
    }
    Snapshot final_snapshot = map->get_snapshot(game_duration_seconds);
    final_snapshot.set_end_game();
    push_all_players(final_snapshot);
    std::cout << "Closing match..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void Gameloop::stop() { playing = false; }

void Gameloop::check_players() {
    if (broadcaster_snapshots.is_empty()) {
        playing = false;
    }
}
