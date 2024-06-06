#ifndef CLIENT_KEYBOARD_HANDLER_H
#define CLIENT_KEYBOARD_HANDLER_H

#include "../game_src/commands/command.h"
#include "../game_src/commands/command_jump.h"
#include "../game_src/commands/command_move.h"
#include "../game_src/commands/command_move_faster.h"
#include "../game_src/commands/command_shoot.h"
#include "../common_src/queue.h"
#include "SDL2pp/SDL2pp.hh"

class KeyboardHandler {
private:
    int client_id;
    std::shared_ptr<Queue<std::shared_ptr<Command>>>& q_cmds;

public:
    explicit KeyboardHandler(std::shared_ptr<Queue<std::shared_ptr<Command>>>& q_cmds);

    void listenForCommands(bool& gameRunning);
    void setId(int id);
};


#endif  // CLIENT_KEYBOARD_HANDLER_H
