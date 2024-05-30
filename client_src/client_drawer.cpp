#include "client_drawer.h"
#include "SDL2pp/SDL2pp/SDL2pp.hh"

using SDL2pp::Font;
using SDL2pp::Mixer;
using SDL2pp::Music;
using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::SDL;
using SDL2pp::SDLTTF;
using SDL2pp::Surface;
using SDL2pp::Texture;
using SDL2pp::Window;
#include <utility>

#define BACKGROUND_IMG "../client_src/resources/backgrounds/fondo.png"
#define MUSIC_FILE "../client_src/resources/sounds/music.wav"
//#define PLAYER_IMG CHARACTERS_PATH "/Jazz.png" PREGUNTAR SI ESTA BIEN
#define PLAYER_IMG "../client_src/resources/characters/Jazz.png"
#define FONT "../client_src/resources/fonts/04B_30__.ttf"
#define GAME_TITLE "Juego"
#define MUSIC_VOLUME 5

#include "../game_src/commands/command_jump.h"
#include "../game_src/commands/command_move.h"
#include "../game_src/commands/command_move_faster.h"
#include "../game_src/commands/command_shoot.h"
#include "../common_src/constants.h"

ClientDrawer::ClientDrawer(Queue<Command*>& q_cmds, Queue<Snapshot>& q_snapshots)
   : q_cmds(q_cmds), q_snapshots(q_snapshots) {}

void ClientDrawer::process_snapshot(){
    //entities.clear();
    Snapshot snapshot = q_snapshots.pop();

    /*for (auto& rabbit : snapshot.rabbits) {
        entities.push_back(new ShiftingDrawable(rabbit));
    }

    for (auto& projectile : snapshot.projectiles) {
        entities.push_back(new ShiftingDrawable(projectile));
    }

    for (auto& supply : snapshot.supplies) {
        entities.push_back(new ShiftingDrawable(supply));
    }*/
}

void ClientDrawer::handle_keyboard(bool &game_running){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_running = false;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP] and state[SDL_SCANCODE_RCTRL]) { //HABILIDAD ESPECIAL JAZZ Y LLORI
        //q_cmds.push(new UpperHit(client_id, FORWARD_DIR));
        //q_cmds.push(new ShortRangeKick(client_id, BACKWARD_DIR));
    } else if (state[SDL_SCANCODE_RCTRL] and state[SDL_SCANCODE_RIGHT]) {// HABILIDAD ESPECIAL SPAZ
        //q_cmds.try_push(AsideKick(client_id, FORWARD_DIR));
    } else if (state[SDL_SCANCODE_RCTRL] and state[SDL_SCANCODE_LEFT]) { //HABILIDAD ESPECIAL SPAZ
        //q_cmds.try_push(AsideKick(client_id, BACKWARD_DIR));
    } else if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_RIGHT]) {
        q_cmds.push(new MoveFaster(client_id, FORWARD_DIR));
    } else if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_LEFT]) {
        q_cmds.push(new MoveFaster(client_id, BACKWARD_DIR));
    } else if (state[SDL_SCANCODE_RIGHT]) {
        q_cmds.push(new Move(client_id, FORWARD_DIR));
    } else if (state[SDL_SCANCODE_LEFT]) {
        q_cmds.push(new Move(client_id, BACKWARD_DIR));
    } else if (state[SDL_SCANCODE_UP] and state[SDL_SCANCODE_RIGHT]) {
        q_cmds.push(new Jump(client_id, FORWARD_DIR));
    } else if (state[SDL_SCANCODE_UP] and state[SDL_SCANCODE_LEFT]) {
        q_cmds.push(new Jump(client_id, BACKWARD_DIR));
    } else if (state[SDL_SCANCODE_UP] and state[SDL_SCANCODE_RIGHT]) {
        q_cmds.push(new Jump(client_id, FORWARD_DIR));
    } else if (state[SDL_SCANCODE_S]) {
        q_cmds.push(new Shoot(client_id, FORWARD_DIR));
    } else if (state[SDL_SCANCODE_W]) {
        //q_cmds.try_push(ChangeWeapon(client_id));
    } else if (state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_ESCAPE]) {
        game_running = false;
    } else {

    }
}

int ClientDrawer::run() {

    /* necesito:
        componentes del mapa en bloquecitos de 32x32
        personajes
        enemigos
        recursos y municion
        projectiles (balas)
        puntaje inicial
        tiempo restante
     */

    /*try {
        SDL initialization
        Receive first snapshot
        while (true) {
            Receive keyboard events
            Send commands
            Receive snapshot
            Update entities
            Draw snapshot
        }
    }
    */

    try {
        // Initialize SDL library
        SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
        // Initialize SDL_ttf library
        SDLTTF ttf;
        // Inicialización de SDL_mixer a través de SDL2pp::Mixer
        Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
        // Cargar música de fondo
        Music backgroundMusic(MUSIC_FILE);
        // Set music volume
        mixer.SetMusicVolume(MUSIC_VOLUME);
        // Reproducir música en bucle
        mixer.PlayMusic(backgroundMusic, -1);
        // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
        Window window(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                      SDL_WINDOW_SHOWN);
        // Create accelerated video renderer with default driver
        Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
        // Dibuja la imagen de fondo
        Texture background(renderer, SDL2pp::Surface(BACKGROUND_IMG));

        // Load sprites image as a new texture; since there's no alpha channel
        // but we need transparency, use helper surface for which set color key
        // to color index 0 -> black background on image will be transparent on our
        // texture
        SDL_Color colorKey = {44, 102, 150, 255};  // Color en formato RGBA
        Surface surface(PLAYER_IMG);
        SDL_SetColorKey(surface.Get(), SDL_TRUE,
                        SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b));
        Texture sprites(renderer, surface);


        // Enable alpha blending for the sprites
        sprites.SetBlendMode(SDL_BLENDMODE_BLEND);

        // Load font, 12pt size
        Font font(FONT, 12);

        bool is_running = true;

        //FIRST SNAPSHOT

        //Snapshot first_snapshot = q_snapshots.pop();


        client_id = 0; //snapshot me da un id


        // Game state
        //int score = 0;            // player score

        unsigned int prev_ticks = SDL_GetTicks();
        // Main loop
        while (is_running) {
            // Timing: calculate difference between this and previous frame
            // in milliseconds
            unsigned int frame_ticks = SDL_GetTicks();
            unsigned int frame_delta = frame_ticks - prev_ticks;
            prev_ticks = frame_ticks;

            // Event processing
            handle_keyboard(is_running);

            // Read snapshot
            process_snapshot();

            // Clear screen
            renderer.Clear();
            renderer.Copy(background, SDL2pp::NullOpt, SDL2pp::NullOpt);

            // Show rendered frame
            renderer.Present();

            // Frame limiter: sleep for a little bit to not eat 100% of CPU
            SDL_Delay(1);
        }

        // Here all resources are automatically released and libraries deinitialized
        return 0;
    } catch (std::exception& e) {
        // If case of error, print it and exit with error
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
