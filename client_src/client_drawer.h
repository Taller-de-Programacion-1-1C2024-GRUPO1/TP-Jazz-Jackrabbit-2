#ifndef CLIENT_DRAWER_H
#define CLIENT_DRAWER_H


//#define BACKGROUND_IMG BACKGROUNDS_PATH "/fondo.png"
//#define MUSIC_FILE DSOUNDS_PATH "/music.wav"
//#define PLAYER_IMG CHARACTERS_PATH "/Jazz.png"
//#define FONT FONTS_PATH "/04B_30__.ttf"
//#define GAME_TITLE "Juego"

//#include "client_config.h"
//#define CHARACTERS_PATH ClientConfigSingleton::getInstance().getCharactersPath()


#define BACKGROUND_IMG "../client_src/resources/backgrounds/fondo.png"
#define MUSIC_FILE "../client_src/resources/sounds/music.wav"

#define CARROTUS_TILE "../client_src/resources/tiles/castle.png"
#define CASTLE_TILE "../client_src/resources/tiles/carrotus.png"

#define FONT "../client_src/resources/fonts/04B_30__.ttf"
#define ITEMS_IMG "../client_src/resources/items/items.png"
#define PROJECTILES_IMG "../client_src/resources/projectiles/Projectiles.png"
#define GAME_TITLE "Juego"
#define MUSIC_VOLUME 5

// pre-commit run --hook-stage manual --all-files
#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

#include "../client_keyboard_handler.h"
#include "../client_src/client_ammo_left.h"
#include "../client_src/client_animation.h"
#include "../client_src/client_drawable.h"
#include "../client_src/client_hearts_banner.h"
#include "../client_src/client_shifting_drawable.h"
#include "../client_src/client_weapon_data.h"
#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/snapshots/snapshot.h"
#include "../game_src/commands/command.h"
#include "../game_src/commands/command_jump.h"
#include "../game_src/commands/command_move.h"
#include "../game_src/commands/command_move_faster.h"
#include "../game_src/commands/command_shoot.h"

using SDL2pp::Chunk;
using SDL2pp::Font;
using SDL2pp::Mixer;
using SDL2pp::Music;
using SDL2pp::NullOpt;
using SDL2pp::Point;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::SDL;
using SDL2pp::SDLTTF;
using SDL2pp::Surface;
using SDL2pp::Texture;
using SDL2pp::Window;

#include "client_constants.h"
#include "client_drawable.h"
#include "client_drawable_enemy.h"
#include "client_drawable_rabbit.h"
#include "client_drawable_valuable.h"
#include "client_food_provider.h"
#include "client_map_loader.h"
#include "client_number_images.h"
#include "client_sound_manager.h"


// pre-commit run --hook-stage manual --all-files

class ClientDrawer {
private:
    Queue<std::unique_ptr<Command>>& q_cmds;
    Queue<Snapshot>& q_snapshots;
    bool game_running;

    // This client match data
    int client_id;
    int score;
    int lives;
    DrawableRabbit* client_rabbit;

    // Game data
    std::map<int, DrawableRabbit*> rabbits;
    std::map<int, DrawableEnemy*> enemies;
    std::map<int, ShiftingDrawable*> projectiles;
    std::map<int, ShiftingDrawable*> supplies;
    std::map<int, Drawable*> food;

    int rabbit_width;
    int rabbit_height;

    KeyboardHandler keyboard_handler;

public:
    int run(int player_id, int map_texture);
    ClientDrawer(Queue<std::unique_ptr<Command>>& q_cmds, Queue<Snapshot>& q_snapshots);

    void showLoadingScreen(Renderer& renderer);
    void showFinalScreen(Renderer& renderer, const Snapshot& snapshot, Texture& background);
    //~ClientDrawer();
};

#endif
