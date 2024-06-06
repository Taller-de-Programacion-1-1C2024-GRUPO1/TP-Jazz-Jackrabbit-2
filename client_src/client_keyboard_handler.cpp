#include "client_keyboard_handler.h"

KeyboardHandler::KeyboardHandler(std::shared_ptr<Queue<Command*>>& q_cmds): 
    q_cmds(q_cmds) {}

void KeyboardHandler::listenForCommands(bool& game_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_running = false;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP] and state[SDL_SCANCODE_RCTRL]) {  // HABILIDAD ESPECIAL JAZZ Y LLORI
        // q_cmds.push(new UpperHit(client_id, 1)); //1: FORWARD
        // q_cmds.push(new ShortRangeKick(client_id, 0));
    } else if (state[SDL_SCANCODE_RCTRL] and
               state[SDL_SCANCODE_RIGHT]) {  // HABILIDAD ESPECIAL SPAZ
        // q_cmds.try_push(AsideKick(client_id, 1)); //1: FORWARD
    } else if (state[SDL_SCANCODE_RCTRL] and state[SDL_SCANCODE_LEFT]) {  // HABILIDAD ESPECIAL SPAZ
        // q_cmds.try_push(AsideKick(client_id, 0));
    } else if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_RIGHT]) {
        q_cmds->push(new MoveFaster(client_id, 1)); //1: FORWARD
    } else if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_LEFT]) {
        q_cmds->push(new MoveFaster(client_id, 0));
    } else if (state[SDL_SCANCODE_RIGHT]) {
        q_cmds->push(new Move(client_id, 1)); //1: FORWARD
    } else if (state[SDL_SCANCODE_LEFT]) {
        q_cmds->push(new Move(client_id, 0));
    } else if (state[SDL_SCANCODE_UP] and state[SDL_SCANCODE_RIGHT]) {
        q_cmds->push(new Move(client_id, 1)); //1: FORWARD
    } else if (state[SDL_SCANCODE_UP] and state[SDL_SCANCODE_LEFT]) {
        q_cmds->push(new Jump(client_id, 0));
    } else if (state[SDL_SCANCODE_S]) {
        //return new Shoot(client_id);
    } else if (state[SDL_SCANCODE_W]) {
        // q_cmds->try_push(ChangeWeapon(client_id));
    } else if (state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_ESCAPE]) {
        game_running = false;
    }
}

void KeyboardHandler::setId(int id) {
    client_id = id;
}