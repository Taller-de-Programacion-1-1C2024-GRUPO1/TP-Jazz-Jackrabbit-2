#include "client_drawer.h"
#include "client_drawable.h"

ClientDrawer::ClientDrawer(Queue<Command*>& q_cmds, Queue<Snapshot>& q_snapshots):
        q_cmds(q_cmds), q_snapshots(q_snapshots), client_id(0) {}


void ClientDrawer::handle_keyboard(bool& game_running) {
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
    } else if (state[SDL_SCANCODE_RCTRL] and
               state[SDL_SCANCODE_RIGHT]) {  // HABILIDAD ESPECIAL SPAZ
        // q_cmds.try_push(AsideKick(client_id, FORWARD_DIR));
    } else if (state[SDL_SCANCODE_RCTRL] and state[SDL_SCANCODE_LEFT]) {  // HABILIDAD ESPECIAL SPAZ
        // q_cmds.try_push(AsideKick(client_id, BACKWARD_DIR));
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
    } else if (state[SDL_SCANCODE_S]) {
        q_cmds.push(new Shoot(client_id));
    } else if (state[SDL_SCANCODE_W]) {
        // q_cmds.try_push(ChangeWeapon(client_id));
    } else if (state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_ESCAPE]) {
        game_running = false;
    } else {
    }
}


int x_counter = 10;
int ammo = 1000;
bool is_shooting = false;


std::vector<std::unique_ptr<Drawable>> loadMap(const std::string& filename, Renderer& renderer,
                                               SDL2pp::Point& cameraPosition) {
    YAML::Node map = YAML::LoadFile(filename);
    std::vector<std::unique_ptr<Drawable>> tiles;

    int tilesetWidth = 10;  // Ancho del tileset en bloques

    for (const auto& layerNode: map["layers"]) {
        int x = 0;
        int y = 0;
        for (const auto& row: layerNode["data"]) {
            for (const auto& block: row) {
                int id = block.as<int>();
                if (id != -1) {  // Ignore empty tiles, but they count in the iteration

                    // Calculate srcRect based on the texture id
                    SDL2pp::Rect srcRect;
                    srcRect.x = (id % tilesetWidth) * 32;
                    srcRect.y = (id / tilesetWidth) * 32;
                    srcRect.w = 32;
                    srcRect.h = 32;

                    // Calculate destRect based on the position in the layer
                    SDL2pp::Rect destRect;
                    destRect.x = x * 32;
                    destRect.y = y * 32;
                    destRect.w = 32;
                    destRect.h = 32;

                    tiles.push_back(std::move(std::unique_ptr<Drawable>(new Drawable(renderer, CASTLE_TILE, cameraPosition, srcRect, destRect))));
                }
                x++;
            }
            x = 0;
            y++;
        }
    }

    return tiles;
}


void handle_events(bool& game_running, int& score, ShiftingDrawable& jazz) {
    SDL_Event event;
    is_shooting = false;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_running = false;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_RIGHT]) {
        x_counter += 10;
        jazz.setPosition(x_counter, 10);
        jazz.setAnimation("Dash");
        jazz.setDirection(1);
    } else if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_LEFT]) {
        x_counter -= 10;
        jazz.setPosition(x_counter, 10);
        jazz.setAnimation("Dash");
        jazz.setDirection(-1);
    } else if (state[SDL_SCANCODE_RIGHT]) {
        score++;
        x_counter += 5;

        jazz.setPosition(x_counter, 10);
        jazz.setAnimation("Run");
        jazz.setDirection(1);

    } else if (state[SDL_SCANCODE_LEFT]) {
        score--;
        x_counter -= 5;
        jazz.setPosition(x_counter, 10);
        jazz.setAnimation("Run");
        jazz.setDirection(-1);
    } else if (state[SDL_SCANCODE_UP]) {

    } else if (state[SDL_SCANCODE_DOWN]) {
        jazz.setAnimation("Hurt");

    } else if (state[SDL_SCANCODE_ESCAPE]) {
        game_running = false;
    } else if (state[SDL_SCANCODE_S]) {
        jazz.setAnimation("Shoot");
        ammo--;
        is_shooting = true;
    } else if (state[SDL_SCANCODE_D]) {
        jazz.setAnimation("Die");
    } else {
        jazz.setAnimation("Idle");
    }
}


int ClientDrawer::run() try {
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

    Texture map_tile(renderer, SDL2pp::Surface(CASTLE_TILE));

    // Load sprites image as a new texture; since there's no alpha channel
    // but we need transparency, use helper surface for which set color key
    // to color index 0 -> black background on image will be transparent on our
    // texture
    SDL_Color colorKey = {44, 102, 150, 255};  // Color en formato RGBA

    SDL2pp::Point playerPosition(10, 10);
    SDL2pp::Point cameraPosition(0, 0);
    SDL2pp::Point desiredCameraPosition(0, 0);
    float lerpFactor = 0.1f;  // Ajusta este valor para cambiar la suavidad

    //Load map
    std::vector<std::unique_ptr<Drawable>> mapComponents = loadMap("../external/maps/carrotus.yml", renderer, cameraPosition);

    // Load font, 12pt size
    Font font(FONT, 12);

    // Number images
    NumberImages numberImages(renderer);
    numberImages.setCorner(0);

    // Heart banner
    WeaponData::initialize();
    HeartsBanner banner(renderer);
    AmmoLeft ammoLeft(renderer);
    ammoLeft.setWeapon(5);

    // Sound effect
    Chunk soundEffect("../client_src/resources/sounds/shooting.wav");
    soundEffect.SetVolume(128);

    // A testing player
    SDL2pp::Rect textureRect(0, 0, 32, 32); // Asume que quieres dibujar una textura de 32x32 desde el punto (0,0)
    SDL2pp::Rect onMapRect(10, 10, 64, 64); // Asume que quieres dibujar la textura en el punto (10,10) en el mapa con un tamaño de 32x32

    ShiftingDrawable jazz(renderer, JAZZ_IMG, colorKey, cameraPosition, textureRect, onMapRect, mixer);
    jazz.setAnimation("Idle");
    jazz.loadAnimations("../external/animations/jazz.yml");

    int enemie_x = 10;
    int multiplier = 1;

    // Game state
    bool running = true;  // whether the game is running
    int score = 000000;   // player score

    const int FPS = 60;
    const int expectedFrameTime = 1000 / FPS;
    Uint32 frameStart = SDL_GetTicks();

    // Main loop
    while (running) {

        //EVENTS HANDLER
        //handle_keyboard(running);///////////////////////////////////////////////////////////////////////////////////////////

        handle_events(running, score, jazz);

        playerPosition.x = x_counter;
        // En tu bucle principal o función de actualización de cámara
        desiredCameraPosition.x = x_counter - (window.GetWidth() / 2);
        desiredCameraPosition.y = playerPosition.y - (window.GetHeight() / 2);

        // Interpolación lineal para suavizar el movimiento
        cameraPosition.x += (desiredCameraPosition.x - cameraPosition.x) * lerpFactor;
        cameraPosition.y += (desiredCameraPosition.y - cameraPosition.y) * lerpFactor;

        // UPDATE ENTITIES
        jazz.update();

        for (auto& tilePtr : mapComponents) {
            tilePtr->update();
        }

        // Clear screen
        renderer.Clear();
        renderer.Copy(background, SDL2pp::NullOpt, SDL2pp::NullOpt);

        // Map render
        for (auto& tilePtr : mapComponents) {
            tilePtr->render();
        }

        jazz.render(renderer);

        banner.render();
        ammoLeft.setAmmo(ammo);
        ammoLeft.render();

        std::string scoreStr = std::to_string(score);
        int offset = 32;  // Start position

        for (char c: scoreStr) {
            int number = c - '0';  // Convert char to int
            numberImages.renderNumber(number, offset);
            offset += 24;  // Move position to the left for the next digit
        }

        // Show rendered frame
        renderer.Present();

        // Frame limiter: sleep for a little bit to not eat 100% of CPU
        Uint32 realFrameTime = SDL_GetTicks() - frameStart;
        int rest = expectedFrameTime - realFrameTime;

        if (rest < 0) {
           int behind = -rest;
           int lost = behind - behind % expectedFrameTime;
           frameStart += lost;
        }
        else {
           SDL_Delay(rest);
        }
        frameStart += expectedFrameTime;
    }


    // Here all resources are automatically released and libraries deinitialized
    return 0;
} catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}
