#include "server_gameloop.h"


GameLoop::GameLoop(Queue<uint8_t>& client_cmds_q, ProtectedListOfQueues& list_of_q_msgs):
        client_cmds_q(client_cmds_q),
        enemies(NUM_OF_ENEMIES),
        is_alive(true),
        keep_talking(true),
        list_of_q_msgs(list_of_q_msgs) {}


void GameLoop::kill() { keep_talking = false; }


void GameLoop::run() {
    uint8_t cmd;
    while (keep_talking) {
        try {
            int num_resurrected = enemies.try_resurrect_enemies();
            for (int i = 0; i < num_resurrected; i++) {
                gameloop_push_msg(EVENT_RESURRECT);
            }
            bool msg = client_cmds_q.try_pop(cmd);
            if (msg && cmd == ATACK) {
                bool could_kill = enemies.try_kill_enemy();
                if (could_kill) {
                    gameloop_push_msg(EVENT_DEAD);
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error en el pop del gameloop" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_TIME));
    }
    this->is_alive = false;
}


void GameLoop::gameloop_push_msg(const uint16_t& event_type) {
    for (auto& q: list_of_q_msgs) {
        try {
            bool could_push;
            could_push = q->try_push(MSG_INDICATOR);

            if (!could_push) {
                std::cerr << "0NOOOOOOOOOOOOOOOOOOOOo se pudo pushear el mensaje" << std::endl;
            }

            uint16_t num_alive_enemies = enemies.get_num_alive_enemies();

            if (!could_push) {
                std::cerr << "1NOOOOOOOOOOOOOOOOOOOOo se pudo pushear el mensaje" << std::endl;
            }

            could_push = q->try_push(num_alive_enemies);

            if (!could_push) {
                std::cerr << "2NOOOOOOOOOOOOOOOOOOOOo se pudo pushear el mensaje" << std::endl;
            }

            uint16_t num_dead_enemies = enemies.get_num_of_dead_enemies();
            could_push = q->try_push(num_dead_enemies);

            if (!could_push) {
                std::cerr << "3NOOOOOOOOOOOOOOOOOOOOo se pudo pushear el mensaje" << std::endl;
            }

            could_push = q->try_push(event_type);

            if (!could_push) {
                std::cerr << "4NOOOOOOOOOOOOOOOOOOOOo se pudo pushear el mensaje" << std::endl;
            }

        } catch (const std::exception& e) {
            std::cerr << "Error en el push del gameloop" << std::endl;
        }
    }
}
