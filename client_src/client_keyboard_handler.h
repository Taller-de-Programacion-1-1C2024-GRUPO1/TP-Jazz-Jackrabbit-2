#ifndef CLIENT_KEYBOARD_HANDLER_H
#define CLIENT_KEYBOARD_HANDLER_H

#include "SDL2pp/SDL2pp.hh"
#include "../game_src/commands/command.h"
#include "../game_src/commands/command_jump.h"
#include "../game_src/commands/command_move.h"
#include "../game_src/commands/command_move_faster.h"
#include "../game_src/commands/command_shoot.h"

class KeyboardHandler {
private:
    int client_id;
public:
    KeyboardHandler(int client_id);

    Command* listenForCommands(bool &gameRunning);
};



#endif //CLIENT_KEYBOARD_HANDLER_H
