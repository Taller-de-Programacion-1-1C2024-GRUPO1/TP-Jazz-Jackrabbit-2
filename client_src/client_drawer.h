#ifndef CLIENT_DRAWER_H
#define CLIENT_DRAWER_H

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

#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/snapshots/snapshot.h"
#include "../game_src/commands/command.h"
#include "../game_src/commands/command_jump.h"
#include "../game_src/commands/command_move.h"
#include "../game_src/commands/command_move_faster.h"
#include "../game_src/commands/command_shoot.h"

#include "client_ammo_left.h"
#include "client_animation.h"
#include "client_clock.h"
#include "client_constants.h"
#include "client_drawable.h"
#include "client_hearts_banner.h"
#include "client_keyboard_handler.h"
#include "client_shifting_drawable.h"
#include "client_top_scores.h"


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
#include "client_drawable_ammo.h"
#include "client_drawable_enemy.h"
#include "client_drawable_projectile.h"
#include "client_drawable_rabbit.h"
#include "client_drawable_valuable.h"
#include "client_fonts_printer.h"
#include "client_food_provider.h"
#include "client_map_loader.h"
#include "client_sound_manager.h"
#include "client_textures_provider.h"

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
    std::map<int, DrawableProjectile*> projectiles;
    std::map<int, DrawableValuable*> valuables;
    std::map<int, DrawableAmmo*> ammo_drops;
    std::map<int, Drawable*> food;

    int rabbit_width;
    int rabbit_height;

    KeyboardHandler keyboard_handler;

public:
    int run(int player_id);
    ClientDrawer(Queue<std::unique_ptr<Command>>& q_cmds, Queue<Snapshot>& q_snapshots);

    void showLoadingScreen(Renderer& renderer);
    void showFinalScreen(Renderer& renderer, Snapshot& last_snapshot);
};

#endif
