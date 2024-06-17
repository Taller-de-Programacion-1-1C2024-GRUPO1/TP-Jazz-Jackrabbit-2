#ifndef CLIENT_KEYBOARD_HANDLER_H
#define CLIENT_KEYBOARD_HANDLER_H

#include <memory>

#include "../common_src/queue.h"
#include "../game_src/commands/cheats.h"
#include "../game_src/commands/command.h"
#include "../game_src/commands/command_change_weapon.h"
#include "../game_src/commands/command_jump.h"
#include "../game_src/commands/command_move.h"
#include "../game_src/commands/command_move_faster.h"
#include "../game_src/commands/command_shoot.h"
#include "../game_src/commands/command_special_jazz.h"
#include "../game_src/commands/command_special_lori.h"
#include "../game_src/commands/command_special_spaz.h"
#include "SDL2pp/SDL2pp.hh"

class KeyboardHandler {
private:
    int client_id;
    Queue<std::unique_ptr<Command>>& q_cmds;

public:
    explicit KeyboardHandler(Queue<std::unique_ptr<Command>>& q_cmds);

    void listenForCommands(bool& gameRunning);
    void setId(int id);
};


#endif  // CLIENT_KEYBOARD_HANDLER_H
