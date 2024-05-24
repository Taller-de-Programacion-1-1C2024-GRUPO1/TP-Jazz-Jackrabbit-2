//#define BACKGROUND_IMG BACKGROUNDS_PATH "/fondo.png"
//#define MUSIC_FILE DSOUNDS_PATH "/music.wav"
//#define PLAYER_IMG CHARACTERS_PATH "/Jazz.png"
//#define FONT FONTS_PATH "/04B_30__.ttf"
//#define GAME_TITLE "Juego"

#define BACKGROUND_IMG "../client_src/resources/backgrounds/fondo.png"
#define MUSIC_FILE "../client_src/resources/sounds/music.wav"
//#define PLAYER_IMG CHARACTERS_PATH "/Jazz.png" PREGUNTAR SI ESTA BIEN
#define PLAYER_IMG "../client_src/resources/characters/Jazz.png"
#define FONT "../client_src/resources/fonts/04B_30__.ttf"
#define GAME_TITLE "Juego"
#define MUSIC_VOLUME 5





// pre-commit run --hook-stage manual --all-files


#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

#include <SDL2pp/SDL2pp.hh>

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


    // Load sprites image as a new texture; since there's no alpha channel
    // but we need transparency, use helper surface for which set color key
    // to color index 0 -> black background on image will be transparent on our
    // texture
    SDL_Color colorKey = {44, 102, 150, 255}; // Color en formato RGBA
    Surface surface(PLAYER_IMG);
    SDL_SetColorKey(surface.Get(), SDL_TRUE, SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b));
    Texture sprites(renderer, surface);


    // Enable alpha blending for the sprites
    sprites.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Load font, 12pt size
    Font font(FONT, 12);

    // Game state
    bool is_running = false;  // whether the character is currently running
    int run_phase = -1;       // run animation phase
    float position = 0.0;     // player position
    int score = 0;            // player score

    unsigned int prev_ticks = SDL_GetTicks();
    // Main loop
    while (1) {
        // Timing: calculate difference between this and previous frame
        // in milliseconds
        unsigned int frame_ticks = SDL_GetTicks();
        unsigned int frame_delta = frame_ticks - prev_ticks;
        prev_ticks = frame_ticks;

        // Event processing:
        // - If window is closed, or Q or Escape buttons are pressed,
        //   quit the application
        // - If Right key is pressed, character would run
        // - If Right key is released, character would stop
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        return 0;
                    case SDLK_RIGHT:
                        is_running = true;
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        is_running = false;
                        score++;
                        break;
                }
            }
        }

        // Update game state for this frame:
        // if character is runnung, move it to the right
        if (is_running) {
            position += frame_delta * 0.2;
            run_phase = (frame_ticks / 100) % 8;
        } else {
            run_phase = 0;
        }

        // If player passes past the right side of the window, wrap him
        // to the left side
        if (position > renderer.GetOutputWidth())
            position = -50;

        int vcenter = renderer.GetOutputHeight() / 2;  // Y coordinate of window center

        // Clear screen
        renderer.Clear();

        

        // Pick sprite from sprite atlas based on whether
        // player is running and run animation phase
        int src_x = 8, src_y = 11;  // by default, standing sprite
        if (is_running) {
            // one of 8 run animation sprites
            src_x = 8 + 51 * run_phase;
            src_y = 67;
        }

        // Draw player sprite
        sprites.SetAlphaMod(255);  // sprite is fully opaque
        renderer.Copy(sprites, Rect(src_x, src_y, 25, 50),
                      Rect((int)position, vcenter - 50, 50, 50));

        // Draw the same sprite, below the first one, 50% transparent and
        // vertically flipped. It'll look like reflection in the mirror
        sprites.SetAlphaMod(127);  // 50% transparent
        renderer.Copy(sprites, Rect(src_x, src_y, 50, 50), Rect((int)position, vcenter, 50, 50),
                      0.0,                 // don't rotate
                      NullOpt,             // rotation center - not needed
                      SDL_FLIP_VERTICAL);  // vertical flip

        // Create text string to render
        std::string text = "Score: " + std::to_string(score) +
                           ", running: " + (is_running ? "true" : "false");

        // Render the text into new texture. Note that SDL_ttf render
        // text into Surface, which is converted into texture on the fly
        Texture text_sprite(renderer, font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255}));

        // Copy texture into top-left corner of the window
        renderer.Copy(text_sprite, NullOpt,
                      Rect(0, 0, text_sprite.GetWidth(), text_sprite.GetHeight()));

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
