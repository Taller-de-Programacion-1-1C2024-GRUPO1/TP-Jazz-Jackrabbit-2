#ifndef CLIENT_DRAWER_H
#define CLIENT_DRAWER_H


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
#define ENEMIES_IMG "../client_src/resources/enemies/Enemies.png"
#define PROJECTILES_IMG "../client_src/resources/projectiles/Projectiles.png"

#define CASTLE_TILE "../client_src/resources/tiles/carrotus.png"

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
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

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

#include "client_number_images.h"


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


// pre-commit run --hook-stage manual --all-files

struct TheFuckingRabbitSnapshot {
    int id;
    int direction;
    int champion_type;
    int pos_x;
    int pos_y;
    int score;
    int lives;
    int weapon;
    int ammo;
    // int state;
    // int action;
    const char* animation;
};

struct TheFuckingEnemySnapshot {
    int id;
    int direction;
    int enemy_type;
    int pos_x;
    int pos_y;
};

struct TheFuckingProjectileSnapshot {
    int id;
    int weapon;
    int pos_x;
    int pos_y;
    // int state;
    const char* animation;
};

struct TheFuckingSupplySnapshot {
    int supply_type;
    int id;
    int pos_x;
    int pos_y;
};

struct TheFuckingInitialSnapshot {
    bool end_game = false;
    MapDimensions_t map_dimensions;
    const char* map_name;

    std::vector<TheFuckingRabbitSnapshot> rabbits;  // playing rabbits
    std::vector<TheFuckingEnemySnapshot> enemies;
    std::vector<TheFuckingProjectileSnapshot> projectiles;
    std::vector<TheFuckingSupplySnapshot> valuables;
    std::vector<TheFuckingSupplySnapshot> food;
};

class ClientDrawer {
private:
    Queue<Command*>& q_cmds;
    Queue<Snapshot>& q_snapshots;
    Queue<TheFuckingInitialSnapshot> qf_snapshots;
    bool game_running;

    // This client match data
    int client_id;
    int score;
    int lives;
    ShiftingDrawable* client_rabbit;

    // Game data
    std::map<int, ShiftingDrawable*> rabbits;
    std::map<int, ShiftingDrawable*> enemies;
    std::map<int, ShiftingDrawable*> projectiles;
    std::map<int, ShiftingDrawable*> valuables;
    std::map<int, Drawable*> food;
    int rabbit_width;
    int rabbit_height;

public:
    ClientDrawer(Queue<Command*>& q_cmds, Queue<Snapshot>& q_snapshots);

    int run();
    void handle_keyboard(bool& game_running);
    void testingSnapshot();
    void testingSnapshott();


    //~ClientDrawer();
};

#endif
