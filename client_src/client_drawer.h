#ifndef CLIENT_DRAWER_H
#define CLIENT_DRAWER_H

#include "client_manager.h"


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


class ClientDrawer {
private:
    ClientManager manager;


public:
    ClientDrawer(const std::string& host, const std::string& service);

    int run();

    //~ClientDrawer();
};

#endif
