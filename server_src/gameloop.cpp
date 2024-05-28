#include "gameloop.h"

#define EXTRA_HEALTH ConfigSingleton::getInstance().get_extra_health()

Game::Game(Queue<std::shared_ptr<Command>>& client_cmd_queue, BroadcasterSnapshots& broadcaster_snapshots, std::list<Player*>& players, bool* keep_running):
    height(0),
    width(0),
    client_cmd_queue(client_cmd_queue),
    broadcaster_snapshots(broadcaster_snapshots),
    players(players),
    keep_running(keep_running),
    game_ended(false)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

std::shared_ptr<Snapshot> Game::get_initial_snapshot(const Map& map) {

    // Se debe leer el mapa elegido por el usuario y crearlo
    std::shared_ptr<Snapshot> snapshot = map.get_snapshot();
    // builder.create_map(snapshot);
    height = map.height;
    width = map.width;

    // Se deben crear enemigos y suministros. 
    // game_manager.add_enemies(snapshot);
    // game_manager.add_supplies(snapshot);

    // Enviar el snapshot inicial
    return snapshot;
}

void Game::push_all_players(const Snapshot& snapshot) {
    // Enviar a cada jugador la snapshot
    for (auto& player: players) {
        Queue<std::shared_ptr<Snapshot>>& player_snapshot_queue = player->get_snapshots_queue();
        try {
            player_snapshot_queue.push(std::make_shared<Snapshot>(snapshot));
        } catch (const ClosedQueue& err) {
            continue;
        }
    }
}

void Game::execute_and_step(int iter) {
    try {
        std::shared_ptr<Command> game_command;
        while (client_cmd_queue.try_pop(game_command)) {
            // game_command->execute_Command();
        }
        // game_world.step(iter);

        // Snapshot snapshot = gameWorld.get_game_snapshot();
        // push_all_players(snapshot);
        // gameWorld.game_post_cleanup();
        // If the game has ended, we should stop the match
        /*
        if (gameWorld.check_end_game()) {
            Snapshot ending_snapshot = game.get_end_game_snapshot();
            push_all_players(ending_snapshot);
            stop();
        }
        */
    } catch (const ClosedQueue& err) {
        if (!keep_running)
            return;
        std::cerr << "Error: " << err.what() << std::endl;
        *keep_running = false;
    }
}

void Game::stop() { *keep_running = false; }

void Game::run() {
    Clock clock([this](int iter) { execute_and_step(iter); }, FRAME_TIME , *keep_running);
    clock.tick();
}



