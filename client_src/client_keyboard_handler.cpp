#include "client_keyboard_handler.h"

KeyboardHandler::KeyboardHandler(int client_id) : client_id(client_id) {}

Command* KeyboardHandler::listenForCommands(bool& game_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_running = false;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP] and state[SDL_SCANCODE_RCTRL]) {  // HABILIDAD ESPECIAL JAZZ Y LLORI
        // q_cmds.push(new UpperHit(client_id, FORWARD_DIR));
        // q_cmds.push(new ShortRangeKick(client_id, BACKWARD_DIR));
    } else if (state[SDL_SCANCODE_RCTRL] and state[SDL_SCANCODE_RIGHT]) {  // HABILIDAD ESPECIAL SPAZ
        // q_cmds.try_push(AsideKick(client_id, FORWARD_DIR));
    } else if (state[SDL_SCANCODE_RCTRL] and state[SDL_SCANCODE_LEFT]) {  // HABILIDAD ESPECIAL SPAZ
       // q_cmds.try_push(AsideKick(client_id, BACKWARD_DIR));
    } else if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_RIGHT]) {
       return new MoveFaster(client_id, FORWARD_DIR);
    } else if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_LEFT]) {
       return new MoveFaster(client_id, BACKWARD_DIR);
    } else if (state[SDL_SCANCODE_RIGHT]) {
       return new Move(client_id, FORWARD_DIR);
    } else if (state[SDL_SCANCODE_LEFT]) {
       return new Move(client_id, BACKWARD_DIR);
    } else if (state[SDL_SCANCODE_UP] and state[SDL_SCANCODE_RIGHT]) {
       return new Jump(client_id, FORWARD_DIR);
    } else if (state[SDL_SCANCODE_UP] and state[SDL_SCANCODE_LEFT]) {
       return new Jump(client_id, BACKWARD_DIR);
    } else if (state[SDL_SCANCODE_S]) {
       return new Shoot(client_id);
    } else if (state[SDL_SCANCODE_W]) {
       // q_cmds.try_push(ChangeWeapon(client_id));
    } else if (state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_ESCAPE]) {
       game_running = false;
    }
    return nullptr;
}