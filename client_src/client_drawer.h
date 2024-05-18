
#include "../common_src/protocol.h"
#include "../common_src/thread.h"


#include <iostream>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <unistd.h>  // for sleep

#include "SDL2/SDL.h"

#define BACKGROUND_IMG "../client_src/resources/backgrounds/fondo.png"
#define MUSIC_FILE "../client_src/resources/sounds/music.wav"
#define PLAYER_IMG "../client_src/resources/characters/Lori.png"

#define GAME_TITLE "Juego"


class ClientDrawer: public Thread {

private:
    ClientProtocol& protocol;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

public:
    explicit ClientDrawer(ClientProtocol& protocol);
    virtual void run() override;
    bool is_dead();
    void kill();
};
