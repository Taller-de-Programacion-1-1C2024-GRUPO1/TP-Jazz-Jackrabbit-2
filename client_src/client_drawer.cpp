#include "client_drawer.h"


ClientDrawer::ClientDrawer(std::shared_ptr<Queue<Command*>> q_cmds, Queue<Snapshot>& q_snapshots):
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
        // q_cmds->push(new UpperHit(client_id, FORWARD_DIR));
        // q_cmds->push(new ShortRangeKick(client_id, BACKWARD_DIR));
    } else if (state[SDL_SCANCODE_RCTRL] and
               state[SDL_SCANCODE_RIGHT]) {  // HABILIDAD ESPECIAL SPAZ
        // q_cmds.try_push(AsideKick(client_id, FORWARD_DIR));
    } else if (state[SDL_SCANCODE_RCTRL] and state[SDL_SCANCODE_LEFT]) {  // HABILIDAD ESPECIAL SPAZ
        // q_cmds.try_push(AsideKick(client_id, BACKWARD_DIR));
    } else if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_RIGHT]) {
        q_cmds->push(new MoveFaster(client_id, FORWARD_DIR));
    } else if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_LEFT]) {
        q_cmds->push(new MoveFaster(client_id, BACKWARD_DIR));
    } else if (state[SDL_SCANCODE_RIGHT]) {
        q_cmds->push(new Move(client_id, FORWARD_DIR));
    } else if (state[SDL_SCANCODE_LEFT]) {
        q_cmds->push(new Move(client_id, BACKWARD_DIR));
    } else if (state[SDL_SCANCODE_UP] and state[SDL_SCANCODE_RIGHT]) {
        q_cmds->push(new Jump(client_id, FORWARD_DIR));
    } else if (state[SDL_SCANCODE_UP] and state[SDL_SCANCODE_LEFT]) {
        q_cmds->push(new Jump(client_id, BACKWARD_DIR));
    } else if (state[SDL_SCANCODE_S]) {
        q_cmds->push(new Shoot(client_id));
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

struct Tile {
    int id;
    Rect srcRect;   // Rectángulo de la textura
    Rect destRect;  // Rectángulo de destino en la pantalla
};

std::vector<Tile> loadMap(const std::string& filename) {
    YAML::Node map = YAML::LoadFile(filename);
    std::vector<Tile> tiles;

    int tilesetWidth = 10;  // Ancho del tileset en bloques


    for (const auto& layerNode: map["layers"]) {
        int x = 0;
        int y = 0;
        for (const auto& row: layerNode["data"]) {
            for (const auto& block: row) {
                int id = block.as<int>();
                if (id != -1) {  // Ignorar tiles vacíos, pero cuentan en la iteración
                    Tile tile;
                    tile.id = id;
                    // Calcular srcRect basado en el id de la textura
                    tile.srcRect.x = (id % tilesetWidth) * 32;
                    tile.srcRect.y = (id / tilesetWidth) * 32;
                    tile.srcRect.w = 32;
                    tile.srcRect.h = 32;
                    // Calcular destRect basado en la posición en la capa
                    tile.destRect.x = x * 32;
                    tile.destRect.y = y * 32;
                    tile.destRect.w = 32;
                    tile.destRect.h = 32;
                    tiles.push_back(tile);
                }
                x++;
            }
            x = 0;
            y++;
        }
    }

    return tiles;
}


void handle_events(bool& game_running, int& score, ShiftingDrawable& jazz, ShiftingDrawable& spaz,
                   ShiftingDrawable& lori) {
    SDL_Event event;
    is_shooting = false;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_running = false;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_RIGHT]) {
        x_counter += 2;
        jazz.setPosition(x_counter, 10);
        jazz.setAnimation("Dash");
        jazz.setDirection(1);
    } else if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_LEFT]) {
        x_counter -= 2;
        jazz.setPosition(x_counter, 10);
        jazz.setAnimation("Dash");
        jazz.setDirection(-1);
    } else if (state[SDL_SCANCODE_RIGHT]) {
        score++;

        jazz.setPosition(++x_counter, 10);
        jazz.setAnimation("Run");
        jazz.setDirection(1);

        spaz.setPosition(++x_counter, 100);
        spaz.setAnimation("Run");
        spaz.setDirection(1);

        lori.setPosition(++x_counter, 200);
        lori.setAnimation("Run");
        lori.setDirection(1);

    } else if (state[SDL_SCANCODE_LEFT]) {
        score--;

        jazz.setPosition(--x_counter, 10);
        jazz.setAnimation("Run");
        jazz.setDirection(-1);

        spaz.setPosition(--x_counter, 100);
        spaz.setAnimation("Run");
        spaz.setDirection(-1);

        lori.setPosition(--x_counter, 200);
        lori.setAnimation("Run");
        lori.setDirection(-1);

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
        spaz.setAnimation("Idle");
        lori.setAnimation("Idle");
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

    // Load map!!
    // YAML::Node config = loadYAML("../external/maps/map.yml");
    // const YAML::Node &layers = config["layers"];

    std::vector<Tile> mapComponents = loadMap("../external/maps/map.yml");

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
    ShiftingDrawable jazz(10, 10, 64, 64, renderer, JAZZ_IMG, colorKey, &mixer);
    jazz.loadAnimations("../external/animations/jazz.yml");
    SDL2pp::Point playerPosition(10, 10);
    jazz.setCameraPosition(playerPosition);

    // Another testing player
    ShiftingDrawable spaz(10, 100, 64, 64, renderer, SPAZ_IMG, colorKey, &mixer);
    spaz.loadAnimations("../external/animations/spaz.yml");
    spaz.setCameraPosition(playerPosition);

    // A third one
    ShiftingDrawable lori(10, 200, 64, 64, renderer, LORI_IMG, colorKey, &mixer);
    lori.loadAnimations("../external/animations/lori.yml");
    lori.setCameraPosition(playerPosition);

    // A coin and a diamond
    SDL_Color itemsColorKey = {0, 128, 255, 1};

    ShiftingDrawable coin(80, 15, 32, 32, renderer, ITEMS_IMG, itemsColorKey, &mixer);
    coin.loadAnimations("../external/animations/resources.yml");
    coin.setCameraPosition(playerPosition);

    ShiftingDrawable diamond(150, 15, 32, 32, renderer, ITEMS_IMG, itemsColorKey, &mixer);
    diamond.loadAnimations("../external/animations/resources.yml");
    diamond.setCameraPosition(playerPosition);

    coin.setAnimation("Coin-flip");
    diamond.setAnimation("Diamond-flip");

    // PROJECTILES
    ShiftingDrawable projectile(10, 10, 32, 32, renderer, PROJECTILES_IMG, itemsColorKey, &mixer);
    WeaponData::loadAnimationsToProjectile(1, projectile);
    bool exploded = false;
    // ENEMIES

    // Crab
    ShiftingDrawable crab(10, 500, 32, 32, renderer, ENEMIES_IMG, itemsColorKey, &mixer);
    crab.loadAnimations("../external/animations/crab.yml");
    crab.setAnimation("Walk");
    crab.setCameraPosition(playerPosition);

    // Tall guy
    ShiftingDrawable lizard(10, 400, 64, 64, renderer, ENEMIES_IMG, itemsColorKey, &mixer);
    lizard.loadAnimations("../external/animations/lizard.yml");
    lizard.setAnimation("Walk");
    lizard.setCameraPosition(playerPosition);

    int enemie_x = 10;
    int multiplier = 1;

    // Game state
    bool running = true;  // whether the game is running
    int score = 000000;   // player score


    const int FPS = 60;
    const int frameDelay = 1000 / FPS;


    // Main loop
    while (running) {
        Uint32 frameStart;
        int frameTime;
        frameStart = SDL_GetTicks();

        // Event processing:
        // - If window is closed, or Q or Escape buttons are pressed,
        //   quit the application
        // - If Right key is pressed, character would run
        // - If Right key is released, character would stop

        // handle_keyboard(running);///////////////////////////////////////////////////////////////////////////////////////////

        handle_events(running, score, jazz, spaz, lori);
        if (enemie_x > 700) {
            crab.setDirection(-1);
            lizard.setDirection(-1);
            multiplier = -1;
        }
        if (enemie_x < 10) {
            crab.setDirection(1);
            lizard.setDirection(1);
            multiplier = 1;
        }
        enemie_x += 1 * multiplier;
        crab.setPosition(enemie_x, 500);
        lizard.setPosition(enemie_x, 400);

        playerPosition.x = x_counter;
        projectile.setPosition(enemie_x * 8, 40);
        if (!exploded && enemie_x * 8 > 600) {
            projectile.setAnimation("Explode");
            exploded = true;
        }
        // std::cout << "Player position: " << playerPosition.x << ", " << playerPosition.y <<
        // std::endl;

        // UPDATE ENTITIES
        jazz.updateCameraPosition(playerPosition);
        jazz.update();

        spaz.updateCameraPosition(playerPosition);
        spaz.update();

        lori.updateCameraPosition(playerPosition);
        lori.update();

        projectile.updateCameraPosition(playerPosition);
        projectile.update();

        coin.updateCameraPosition(playerPosition);
        coin.update();

        diamond.updateCameraPosition(playerPosition);
        diamond.update();

        crab.updateCameraPosition(playerPosition);
        crab.update();

        lizard.updateCameraPosition(playerPosition);
        lizard.update();

        // Clear screen
        renderer.Clear();
        renderer.Copy(background, SDL2pp::NullOpt, SDL2pp::NullOpt);

        // Map render
        for (const Tile& tile: mapComponents) {
            renderer.Copy(map_tile, tile.srcRect, tile.destRect);
        }

        jazz.render(renderer);
        /*if (is_shooting) {
            mixer.PlayChannel(-1, soundEffect);
            SDL_Delay(200);
            mixer.HaltChannel(-1);
        }*/

        spaz.render(renderer);
        lori.render(renderer);

        crab.render(renderer);
        lizard.render(renderer);

        coin.render(renderer);
        diamond.render(renderer);

        projectile.render(renderer);

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
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // Here all resources are automatically released and libraries deinitialized
    return 0;
} catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}
