#include "server_gameloop.h"

GameLoop::GameLoop(Queue<uint8_t>& client_cmds_q, ProtectedListOfQueues& list_of_q_msgs):
        client_cmds_q(client_cmds_q),
        enemies(NUM_OF_ENEMIES),
        is_alive(true),
        keep_talking(true),
        broadcaster(list_of_q_msgs) {}


void GameLoop::kill() { keep_talking = false; }

void GameLoop::run() {
    uint8_t cmd;
    while (keep_talking) {
        try {
            int num_resurrected = enemies.try_resurrect_enemies();
            for (int i = 0; i < num_resurrected; i++) {
                Message msg = {MSG_INDICATOR, enemies.get_num_alive_enemies(),
                               enemies.get_num_of_dead_enemies(), EVENT_RESURRECT};
                gameloop_push_msg(msg);
            }
            bool popeo = client_cmds_q.try_pop(cmd);
            if (popeo && cmd == ATACK) {
                bool could_kill = enemies.try_kill_enemy();
                if (could_kill) {
                    Message msg = {MSG_INDICATOR, enemies.get_num_alive_enemies(),
                                   enemies.get_num_of_dead_enemies(), EVENT_DEAD};
                    gameloop_push_msg(msg);
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error en el pop del gameloop" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_TIME));
    }
    this->is_alive = false;
}

void GameLoop::gameloop_push_msg(const Message& msg) { broadcaster.broadcast(msg); }
