#include <iostream>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <unistd.h>  // for sleep

#include "SDL2/SDL.h"

#define BACKGROUND_IMG "../client_src/resources/backgrounds/fondo.png"
#define MUSIC_FILE "../client_src/resources/sounds/music.wav"
#define PLAYER_IMG "../client_src/resources/characters/Lori.png"

#define GAME_TITLE "Juego"


// pre-commit run --hook-stage manual --all-files


int x = 0;
int y = 0;

// g++ -g -std=c++17 ./src/*.cpp -I.include -o prog -lSDL2 -L/path/to/sdl/library -lSDL2_image
// -L/path/to/sdl_image/library -lSDL2_mixer -ldl g++ -g -std=c++17 ./src/*.cpp -I.include -o
// ./build/prog -lSDL2 -L/path/to/sdl/library -lSDL2_image -L/path/to/sdl_image/library -lSDL2_mixer
// -ldl

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren) {
        SDL_Surface* tempSurface = IMG_Load(fileName);

        // Establecer el color #2C6696 (R:44, G:102, B:150) como transparente
        SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 44, 102, 150));

        SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
        SDL_FreeSurface(tempSurface);
        return tex;
    }
    static void Draw(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
        SDL_RenderCopy(ren, tex, &src, &dest);
    }
};

class GameObject {
private:
    int xpos;
    int ypos;
    SDL_Renderer* renderer;
    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;  // Agrega estas lÃ­neas
public:
    GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y) {
        renderer = ren;
        objTexture = TextureManager::LoadTexture(texturesheet, ren);
        xpos = x;
        ypos = y;
    }
    ~GameObject() { SDL_DestroyTexture(objTexture); }

    void Update() {
        xpos = x;
        ypos = y;
        // defino el tamaño del sprite
        srcRect.h = 48;
        srcRect.w = 48;
        srcRect.x = 0;
        srcRect.y = 350;

        // defino el tamaño del destino
        destRect.x = xpos;  // pos en pantalla
        destRect.y = ypos;  // pos en pantalla
        destRect.w = srcRect.w * 2;
        destRect.h = srcRect.h * 2;
    }

    /*
    void Update() {
            //en cada frame muevo hacia abajo y derecha
            xpos++;
            ypos++;

            //defino el tamaño del sprite
            srcRect.h = 48;
            srcRect.w = 48;
            srcRect.x = 0;
            srcRect.y = 350;

            //defino el tamaño del destino
            destRect.x = xpos; //pos en pantalla
            destRect.y = ypos; //pos en pantalla
            destRect.w = srcRect.w * 2;
            destRect.h = srcRect.h * 2;
    }
    */

    void Render() { SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect); }
};


class Music {
private:
    Mix_Music* m_music;

public:
    explicit Music(const char* filename) {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cerr << "Error al iniciar SDL_mixer: " << Mix_GetError() << std::endl;
        } else {
            m_music = Mix_LoadMUS(filename);
            if (m_music == nullptr) {
                std::cerr << "Error al cargar la música: " << Mix_GetError() << std::endl;
            }
        }
    }
    ~Music() {
        Mix_CloseAudio();
        Mix_FreeMusic(m_music);
    }
    void PlayMusic() {
        Mix_PlayMusic(m_music, -1);  // -1 para reproducir en bucle
    }
    void StopMusic() { Mix_PauseMusic(); }
    void SetVolume(int volume) {  // A range of 0 to MIX_MAX_VOLUME (128).
        Mix_VolumeMusic(volume);
    }
};


class BackGround {
private:
    SDL_Texture* texture;

public:
    explicit BackGround(SDL_Renderer* renderer) {
        SDL_Surface* surface = IMG_Load(BACKGROUND_IMG);
        if (surface == nullptr) {
            std::cerr << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        } else {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
        }
    }
    ~BackGround() { SDL_DestroyTexture(texture); }
    void Render(SDL_Renderer* renderer) { SDL_RenderCopy(renderer, texture, nullptr, nullptr); }
};


class SDLWindow {
    SDL_Window* window;

public:
    SDL_Renderer* renderer;
    explicit SDLWindow(const char* title):
            window(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                    SDL_WINDOW_SHOWN)),
            renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) {}


    ~SDLWindow() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
};

class Game {
    SDLWindow window;
    Music music;
    GameObject* player = new GameObject(PLAYER_IMG, window.renderer, 0, 0);
    BackGround background = BackGround(window.renderer);
    bool running;

public:
    Game(): window("Juego"), music(MUSIC_FILE), running(false) {}
    void run() {
        running = true;
        music.SetVolume(10);
        music.PlayMusic();
        SDL_Rect rect1 = {100, 100, 50, 50};
        SDL_RenderFillRect(window.renderer, &rect1);

        while (running) {
            // Events
            handleEvents();

            // Updates
            player->Update();

            // Render
            SDL_RenderClear(window.renderer);
            background.Render(window.renderer);
            player->Render();
            SDL_RenderPresent(window.renderer);
            SDL_Delay(1);
        }
    }

    void handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:  // Si la tecla presionada es la flecha derecha
                        x += 10;
                        break;

                    case SDLK_LEFT:
                        x -= 10;
                        break;

                    case SDLK_ESCAPE:
                        running = false;  // Cierra el juego

                        break;
                    case SDLK_UP:
                        y -= 10;
                        break;
                    case SDLK_DOWN:
                        y += 10;
                        break;
                }
            }
            // Aquí puedes manejar otros eventos como teclas presionadas, etc.
        }
    }

    ~Game() {
        music.StopMusic();
        SDL_Quit();
    }
};

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error al iniciar SDL: " << SDL_GetError() << std::endl;
        return 1;
    } else {
        Game game;
        game.run();
        return 0;
    }
}
