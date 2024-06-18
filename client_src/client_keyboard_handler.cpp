#include "client_keyboard_handler.h"

KeyboardHandler::KeyboardHandler(Queue<std::unique_ptr<Command>>& q_cmds):
        client_id(-1), q_cmds(q_cmds) {}

void KeyboardHandler::listenForCommands(bool& game_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_running = false;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);

    // CHECK CHEATS
    if (state[SDL_SCANCODE_F1]) {
        q_cmds.push(std::make_unique<Cheats>(client_id, MAX_AMMO));
    } else if (state[SDL_SCANCODE_F2]) {
        q_cmds.push(std::make_unique<Cheats>(client_id, MAX_HEALTH));
    } else if (state[SDL_SCANCODE_F3]) {
        q_cmds.push(std::make_unique<Cheats>(client_id, RESPAWN));
    } else if (state[SDL_SCANCODE_D] && state[SDL_SCANCODE_I] && state[SDL_SCANCODE_P] &&
               state[SDL_SCANCODE_A]) {
        q_cmds.push(std::make_unique<Cheats>(client_id, GODMODE));
    }

    if (state[SDL_SCANCODE_RIGHT]) {
        if (state[SDL_SCANCODE_LSHIFT]) {
            q_cmds.push(std::make_unique<MoveFaster>(client_id, RIGHT));
        } else {
            q_cmds.push(std::make_unique<Move>(client_id, RIGHT));
        }
    } else if (state[SDL_SCANCODE_LEFT]) {
        if (state[SDL_SCANCODE_LSHIFT]) {
            q_cmds.push(std::make_unique<MoveFaster>(client_id, LEFT));
        } else {
            q_cmds.push(std::make_unique<Move>(client_id, LEFT));
        }
    }
    if (state[SDL_SCANCODE_LCTRL]) {
        if (state[SDL_SCANCODE_UP]) {
            if (state[SDL_SCANCODE_LSHIFT]) {
                q_cmds.push(std::make_unique<SpecialLori>(client_id, RIGHT));
            } else {
                q_cmds.push(std::make_unique<SpecialJazz>(client_id));
            }
        } else if (state[SDL_SCANCODE_RIGHT]) {
            q_cmds.push(std::make_unique<SpecialSpaz>(client_id, RIGHT));
        } else if (state[SDL_SCANCODE_LEFT]) {
            q_cmds.push(std::make_unique<SpecialSpaz>(client_id, LEFT));
        }
    }

    if (state[SDL_SCANCODE_UP]) {
        q_cmds.push(std::make_unique<Jump>(client_id, LEFT));
    }
    if (state[SDL_SCANCODE_SPACE]) {
        q_cmds.push(std::make_unique<Shoot>(client_id));
    }
    if (state[SDL_SCANCODE_LALT]) {
        q_cmds.push(std::make_unique<ChangeWeapon>(client_id));
    }
    if (state[SDL_SCANCODE_ESCAPE]) {
        game_running = false;
    } else {
    }
}

void KeyboardHandler::setId(int id) { client_id = id; }
