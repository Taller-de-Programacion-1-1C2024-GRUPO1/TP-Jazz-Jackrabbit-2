//#define BACKGROUND_IMG BACKGROUNDS_PATH "/fondo.png"
//#define MUSIC_FILE DSOUNDS_PATH "/music.wav"
//#define PLAYER_IMG CHARACTERS_PATH "/Jazz.png"
//#define FONT FONTS_PATH "/04B_30__.ttf"
//#define GAME_TITLE "Juego"

#define BACKGROUND_IMG "../client_src/resources/backgrounds/fondo.png"
#define MUSIC_FILE "../client_src/resources/sounds/music.wav"
//#define PLAYER_IMG CHARACTERS_PATH "/Jazz.png" PREGUNTAR SI ESTA BIEN

#define JAZZ_IMG "../client_src/resources/characters/Jazz.png"
#define LORI_IMG "../client_src/resources/characters/Lori.png"
#define SPAZ_IMG "../client_src/resources/characters/Spaz.png"

#define FONT "../client_src/resources/fonts/04B_30__.ttf"
#define ITEMS_IMG "../client_src/resources/items/items.png"
#define GAME_TITLE "Juego"
#define MUSIC_VOLUME 5

// pre-commit run --hook-stage manual --all-files

#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "../client_src/client_animation.h"
#include "../client_src/client_shifting_drawable.h"

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
using SDL2pp::Chunk;

int x_counter = 10;
bool is_shooting = false;

void handle_events(bool& game_running, int& score, ShiftingDrawable& jazz,
                   ShiftingDrawable& spaz, ShiftingDrawable& lori) {
    SDL_Event event;
    is_shooting = false;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_running = false;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_RIGHT]) {

    } else if (state[SDL_SCANCODE_SPACE] and state[SDL_SCANCODE_LEFT]) {

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
        is_shooting = true;
    } else if (state[SDL_SCANCODE_D]) {
        jazz.setAnimation("Die");
    }
    else {
        jazz.setAnimation("Idle");
        spaz.setAnimation("Idle");
        lori.setAnimation("Idle");
    }
}

int main() try {
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

    // Load font, 12pt size
    Font font(FONT, 12);

    //Sound effect
    Chunk soundEffect("../client_src/resources/sounds/shooting.wav");
    soundEffect.SetVolume(128);

    // A testing player
    ShiftingDrawable jazz(10, 10, 64, 64, renderer, JAZZ_IMG, colorKey);
    jazz.loadAnimations("../external/animations/jazz.yml");

    // Another testing player
    ShiftingDrawable spaz(10, 100, 64, 64, renderer, SPAZ_IMG, colorKey);
    spaz.loadAnimations("../external/animations/spaz.yml");

    // A third one
    ShiftingDrawable lori(10, 200, 64, 64, renderer, LORI_IMG, colorKey);
    lori.loadAnimations("../external/animations/lori.yml");

    // A coin and a diamond
    SDL_Color itemsColorKey = {0, 128, 255, 1};

    ShiftingDrawable coin(80, 15, 32, 32, renderer, ITEMS_IMG, itemsColorKey);
    coin.loadAnimations("../external/animations/resources.yml");

    ShiftingDrawable diamond(150, 15, 32, 32, renderer, ITEMS_IMG, itemsColorKey);
    diamond.loadAnimations("../external/animations/resources.yml");

    coin.setAnimation("Coin-flip");
    diamond.setAnimation("Diamond-flip");

    // Game state
    bool running = true;      // whether the game is running
    int score = 0;            // player score


    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    // Main loop
    while (running) {
        frameStart = SDL_GetTicks();

        // Event processing:
        // - If window is closed, or Q or Escape buttons are pressed,
        //   quit the application
        // - If Right key is pressed, character would run
        // - If Right key is released, character would stop
        handle_events(running, score, jazz, spaz, lori);

        //UPDATE ENTITIES
        jazz.update();
        spaz.update();
        lori.update();

        coin.update();
        diamond.update();

        // Clear screen
        renderer.Clear();
        renderer.Copy(background, SDL2pp::NullOpt, SDL2pp::NullOpt);

        jazz.render(renderer);
        if (is_shooting) {
	        mixer.PlayChannel(-1, soundEffect);
	        SDL_Delay(200);
	        mixer.HaltChannel(-1);
        }

        spaz.render(renderer);
        lori.render(renderer);

        coin.render(renderer);
        diamond.render(renderer);

        // Create text string to render
        std::string text =
                "Score: " + std::to_string(score);

        // Show rendered frame
        renderer.Present();

        // Frame limiter: sleep for a little bit to not eat 100% of CPU
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
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
