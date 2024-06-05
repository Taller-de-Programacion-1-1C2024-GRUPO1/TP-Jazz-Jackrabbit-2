#include "client_drawer.h"

#include <algorithm>
#include <memory>
#include <utility>

#include "client_drawable.h"
#include "client_food_provider.h"
#include "client_map_loader.h"
#include "client_sound_manager.h"

/*
COSAS PARA HABLAR
dimensiones de cada cosa

*/

int shiftable_x = 10;
int direction_x = 0;

RabbitSnapshot createRabbitSnapshot(int _id, int _pos_x, int _pos_y) {
    RabbitSnapshot rabbit(_id, direction_x, 0, _pos_x, _pos_y, 10, 3, 0, 1000, 3, 0);
    return rabbit;
}

EnemySnapshot createEnemySnapshot(int _id, int _pos_x, int _pos_y) {
    EnemySnapshot enemy(_id, 0, 0, _pos_x, _pos_y);
    return enemy;
}

ProjectileSnapshot createProjectileSnapshot(int _id, int _pos_x, int _pos_y, int _weapon) {
    ProjectileSnapshot projectile_snapshot(_id, 0, _pos_x, _pos_y, _weapon);
    return projectile_snapshot;
}

SupplySnapshot createSupplySnapshot(int _id, int _pos_x, int _pos_y) {
    SupplySnapshot supply_snapshot(_id, 0, _pos_x, _pos_y);
    return supply_snapshot;
}

Snapshot createInitialSnapshot() {
    Snapshot initial;

    initial.map_dimensions.height = 608;
    initial.map_dimensions.width = 1120;
    initial.map_dimensions.rabbit_amount = 3;
    initial.map_dimensions.rabbit_height = 64;
    initial.map_dimensions.rabbit_width = 64;
    // initial.map_dimensions.map_data;

    initial.rabbits.push_back(createRabbitSnapshot(0, 10, 100));
    // initial.rabbits.push_back(createRabbitSnapshot(1, 10, 150));
    // initial.rabbits.push_back(createRabbitSnapshot(2, 10, 200));

    initial.enemies.push_back(createEnemySnapshot(0, 10, 500));

    initial.projectiles.push_back(createProjectileSnapshot(0, 500, 10, 0));
    initial.projectiles.push_back(createProjectileSnapshot(1, 500, 120, 1));

    initial.supplies.push_back(createSupplySnapshot(0, 400, 400));
    // initial.supplies.push_back(createSupplySnapshot(0, 64, 64));
    // initial.supplies.push_back(createSupplySnapshot(1, 256, 256));
    // initial.supplies.push_back(createSupplySnapshot(2, 300, 300));

    return initial;
}

// ACA EMPIEZA DRAWER

ClientDrawer::ClientDrawer(Queue<Command*>& q_cmds, Queue<Snapshot>& q_snapshots):
        q_cmds(q_cmds),
        q_snapshots(q_snapshots),
        game_running(false),
        client_id(0),
        score(0),
        lives(0),
        client_rabbit(nullptr),
        rabbit_width(0),
        rabbit_height(0) {}

void ClientDrawer::testingSnapshot() {
    Snapshot initial_snapshot = createInitialSnapshot();
    q_snapshots.push(initial_snapshot);
}

void ClientDrawer::setAnimationFromSnapshot(const RabbitSnapshot& snapshot,
                                            ShiftingDrawable* drawable) {
    switch (snapshot.state) {
        case ALIVEE:
            switch (snapshot.action) {
                case STANDD:
                    drawable->setAnimation("Stand");
                    break;
                case RUNN:
                    drawable->setAnimation("Run");
                    break;
                case RUN_FASTT:
                    drawable->setAnimation("Dash");
                    break;
                case FALLINGG:
                    drawable->setAnimation("Run");
                    break;
                case JUMPINGG:
                    drawable->setAnimation("Run");
                    break;
            }
            break;
        case RECIEVED_DAMAGEE:
            drawable->setAnimation("Hurt");
            break;
        case INTOXICATEDD:
            switch (snapshot.action) {
                case STANDD:
                    drawable->setAnimation("Intoxicated-Stand");
                    break;
                case RUNN:
                    drawable->setAnimation("Intoxicated-Run");
                    break;
                case RUN_FASTT:
                    drawable->setAnimation("Intoxicated-Run");
                    break;
                case FALLINGG:
                    drawable->setAnimation("Intoxicated-Stand");
                    break;
                case JUMPINGG:
                    drawable->setAnimation("Intoxicated-Stand");
                    break;
            }
            break;
        case DEADD:
            drawable->setAnimation("Die");
            break;
    }
}

void handle_events(bool& game_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_running = false;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        game_running = false;
    } else if (state[SDL_SCANCODE_RIGHT]) {
        shiftable_x += 10;
        direction_x = 0;
    } else if (state[SDL_SCANCODE_LEFT]) {
        shiftable_x -= 10;
        direction_x = -1;
    }
}

int ClientDrawer::run() try {
    // Initialize SDL library
    SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    // Initialize SDL_ttf library
    SDLTTF ttf;

    SoundManager soundManager;  // pasarle parametros??

    // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
    Window window(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                  SDL_WINDOW_SHOWN);

    // Create accelerated video renderer with default driver
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Dibuja la imagen de fondo
    Texture background(renderer, SDL2pp::Surface(BACKGROUND_IMG));

    SDL_Color characterColor = {44, 102, 150, 255};   // Color en formato RGBA
    SDL_Color enemyAndItemsColor = {0, 128, 255, 1};  // Color en formato RGBA
    SDL_Color mapColor = {87, 0, 203, 0};
    MapLoader mapLoader(renderer);

    SDL2pp::Point playerPosition(10, 10);
    SDL2pp::Point cameraPosition(0, 0);
    SDL2pp::Point desiredCameraPosition(0, 0);
    float lerpFactor = 0.1f;

    const char* CARROTUS_TILE = "../client_src/resources/tiles/carrotus.png";
    const char* MAP_FILE = "../external/maps/carrotus.yml";

    // Number images
    NumberImages numberImages(renderer);
    numberImages.setCorner(0);

    // Heart banner
    WeaponData::initialize();
    FoodProvider::initialize();
    HeartsBanner banner(renderer);
    AmmoLeft ammoLeft(renderer);

    testingSnapshot();

    // Read first snapshot!
    Snapshot initial_snapshot = q_snapshots.pop();
    game_running = !initial_snapshot.get_end_game();

    std::vector<std::unique_ptr<Drawable>> mapComponents =
            mapLoader.loadMap(MAP_FILE, CARROTUS_TILE, mapColor, cameraPosition);
    rabbit_height = initial_snapshot.map_dimensions.rabbit_height;
    rabbit_width = initial_snapshot.map_dimensions.rabbit_width;

    for (auto& rabbit: initial_snapshot.rabbits) {
        SDL2pp::Rect textureRect(0, 0, rabbit_width, rabbit_height);
        SDL2pp::Rect onMapRect(rabbit.pos_x, rabbit.pos_y, rabbit_width, rabbit_height);
        if (rabbit.id == client_id) {
            score = rabbit.score;

            banner.setCurrentLives(rabbit.lives);
            ammoLeft.setWeapon(rabbit.weapon);
            ammoLeft.setAmmo(rabbit.ammo);
            playerPosition.x = rabbit.pos_x;
            playerPosition.y = rabbit.pos_y;

            client_rabbit = new ShiftingDrawable(renderer, JAZZ_IMG, characterColor, cameraPosition,
                                                 textureRect, onMapRect, soundManager);
            client_rabbit->loadAnimations("../external/animations/jazz.yml");
            setAnimationFromSnapshot(rabbit, client_rabbit);
            client_rabbit->setDirection(rabbit.direction);
        } else {
            ShiftingDrawable* newRabbit =
                    new ShiftingDrawable(renderer, SPAZ_IMG, characterColor, cameraPosition,
                                         textureRect, onMapRect, soundManager);
            newRabbit->loadAnimations("../external/animations/spaz.yml");
            setAnimationFromSnapshot(rabbit, newRabbit);
            newRabbit->setDirection(rabbit.direction);
            rabbits.emplace(rabbit.id, newRabbit);
        }
    }
    for (auto& enemy: initial_snapshot.enemies) {
        SDL2pp::Rect textureRect(0, 0, rabbit_width, rabbit_height);
        SDL2pp::Rect onMapRect(enemy.pos_x, enemy.pos_y, rabbit_width, rabbit_height);
        ShiftingDrawable* newEnemy =
                new ShiftingDrawable(renderer, TURTLE_IMG, enemyAndItemsColor, cameraPosition,
                                     textureRect, onMapRect, soundManager);
        newEnemy->loadAnimations("../external/animations/turtle.yml");
        newEnemy->setAnimation("Walk");
        newEnemy->setDirection(enemy.direction);
        enemies.emplace(enemy.id, newEnemy);
    }
    for (auto& projectile: initial_snapshot.projectiles) {
        SDL2pp::Rect textureRect(0, 0, 32, 32);
        SDL2pp::Rect onMapRect(projectile.pos_x, projectile.pos_y, 32, 32);
        ShiftingDrawable* newProjectile =
                new ShiftingDrawable(renderer, PROJECTILES_IMG, enemyAndItemsColor, cameraPosition,
                                     textureRect, onMapRect, soundManager);
        WeaponData::loadAnimationsToProjectile(projectile.weapon, newProjectile);
        newProjectile->setAnimation("Move");
        projectiles.emplace(projectile.id, newProjectile);
    }
    for (auto& valuable: initial_snapshot.supplies) {
        SDL2pp::Rect textureRect(0, 0, 32, 32);
        SDL2pp::Rect onMapRect(valuable.pos_x, valuable.pos_y, 32, 32);
        ShiftingDrawable* newValuable =
                new ShiftingDrawable(renderer, ITEMS_IMG, enemyAndItemsColor, cameraPosition,
                                     textureRect, onMapRect, soundManager);
        newValuable->loadAnimations("../external/animations/valuables/coin.yml");
        newValuable->setAnimation("Flip");
        supplies.emplace(valuable.id, newValuable);
    }

    // Game state
    const int FPS = 60;
    const int expectedFrameTime = 1000 / FPS;
    Uint32 frameStart = SDL_GetTicks();

    // Main loop
    while (game_running) {

        // EVENTS HANDLER
        handle_events(game_running);

        // En tu bucle principal o función de actualización de cámara
        desiredCameraPosition.x = playerPosition.x - (window.GetWidth() / 2);
        desiredCameraPosition.y = playerPosition.y - (window.GetHeight() / 2);

        // Interpolación lineal para suavizar el movimiento
        cameraPosition.x += (desiredCameraPosition.x - cameraPosition.x) * lerpFactor;
        cameraPosition.y += (desiredCameraPosition.y - cameraPosition.y) * lerpFactor;

        // SNAPSHOT RECEIVER
        Snapshot snapshot;
        if (q_snapshots.try_pop(snapshot)) {
            for (const auto& rabbit: snapshot.rabbits) {
                std::cout << "rabbit number " << rabbit.id + 1 << std::endl;
                if (rabbit.id == client_id) {
                    ammoLeft.setAmmo(rabbit.ammo);
                    ammoLeft.setWeapon(rabbit.weapon);
                    banner.setCurrentLives(rabbit.lives);
                    client_rabbit->setPosition(rabbit.pos_x, rabbit.pos_y);
                    setAnimationFromSnapshot(rabbit, client_rabbit);
                    client_rabbit->setDirection(rabbit.direction);
                    playerPosition.x = rabbit.pos_x;
                    playerPosition.y = rabbit.pos_y;
                } else {
                    auto it = rabbits.find(rabbit.id);
                    if (it != rabbits.end()) {
                        it->second->setPosition(rabbit.pos_x, rabbit.pos_y);
                        setAnimationFromSnapshot(rabbit, it->second);
                        it->second->setDirection(rabbit.direction);
                    } else {
                        // Crear un nuevo conejo
                        SDL2pp::Rect textureRect(0, 0, rabbit_width, rabbit_height);
                        SDL2pp::Rect onMapRect(rabbit.pos_x, rabbit.pos_y, rabbit_width,
                                               rabbit_height);
                        ShiftingDrawable* newRabbit = new ShiftingDrawable(
                                renderer, SPAZ_IMG, characterColor, cameraPosition, textureRect,
                                onMapRect, soundManager);
                        newRabbit->loadAnimations("../external/animations/spaz.yml");
                        setAnimationFromSnapshot(rabbit, newRabbit);
                        newRabbit->setDirection(rabbit.direction);
                        rabbits.emplace(rabbit.id, newRabbit);
                    }
                }
            }
            for (const auto& enemy: snapshot.enemies) {
                auto it = enemies.find(enemy.id);
                if (it != enemies.end()) {
                    it->second->setPosition(enemy.pos_x, enemy.pos_y);
                    it->second->setDirection(enemy.direction);
                } else {
                    // Crear un nuevo enemigo
                    SDL2pp::Rect textureRect(0, 0, rabbit_width, rabbit_height);
                    SDL2pp::Rect onMapRect(enemy.pos_x, enemy.pos_y, rabbit_width, rabbit_height);
                    ShiftingDrawable* newEnemy = new ShiftingDrawable(
                            renderer, ENEMIES_IMG, enemyAndItemsColor, cameraPosition, textureRect,
                            onMapRect, soundManager);
                    newEnemy->loadAnimations("../external/animations/lizard.yml");
                    newEnemy->setAnimation("Walk");
                    newEnemy->setDirection(enemy.direction);
                    enemies.emplace(enemy.id, newEnemy);
                }
            }
            for (const auto& projectile: snapshot.projectiles) {
                auto it = projectiles.find(projectile.id);
                if (it != projectiles.end()) {
                    it->second->setPosition(projectile.pos_x, projectile.pos_y);
                } else {
                    // Crear un nuevo proyectil
                    SDL2pp::Rect textureRect(0, 0, 32, 32);
                    SDL2pp::Rect onMapRect(projectile.pos_x, projectile.pos_y, 32, 32);
                    ShiftingDrawable* newProjectile = new ShiftingDrawable(
                            renderer, PROJECTILES_IMG, enemyAndItemsColor, cameraPosition,
                            textureRect, onMapRect, soundManager);
                    WeaponData::loadAnimationsToProjectile(projectile.weapon, newProjectile);
                    newProjectile->setAnimation("Move");
                    projectiles.emplace(projectile.id, newProjectile);
                }
            }
            for (const auto& valuable: snapshot.supplies) {
                auto it = supplies.find(valuable.id);
                if (it != supplies.end()) {
                    it->second->setPosition(valuable.pos_x, valuable.pos_y);
                } else {
                    // Crear un nuevo objeto valioso
                    SDL2pp::Rect textureRect(0, 0, 32, 32);
                    SDL2pp::Rect onMapRect(valuable.pos_x, valuable.pos_y, 32, 32);
                    ShiftingDrawable* newValuable = new ShiftingDrawable(
                            renderer, ITEMS_IMG, enemyAndItemsColor, cameraPosition, textureRect,
                            onMapRect, soundManager);
                    newValuable->loadAnimations("../external/animations/valuables/coin.yml");
                    newValuable->setAnimation("Flip");
                    supplies.emplace(valuable.id, newValuable);
                }
            }
        }

        // UPDATE ENTITIES

        for (auto& tilePtr: mapComponents) {
            tilePtr->update();
        }
        client_rabbit->update();
        for (auto& rabbit: rabbits) {
            rabbit.second->update();
        }
        for (auto& enemy: enemies) {
            enemy.second->update();
        }
        for (auto& projectile: projectiles) {
            projectile.second->update();
        }
        for (auto& supply: supplies) {
            supply.second->update();
        }

        // Clear screen
        renderer.Clear();
        renderer.Copy(background, SDL2pp::NullOpt, SDL2pp::NullOpt);

        // Map render
        for (auto& tilePtr: mapComponents) {
            tilePtr->render();
        }

        client_rabbit->render();
        for (auto& rabbit: rabbits) {
            rabbit.second->render();
        }
        for (auto& enemy: enemies) {
            enemy.second->render();
        }
        for (auto& projectile: projectiles) {
            projectile.second->render();
        }
        for (auto& suply: supplies) {
            suply.second->render();
        }

        banner.render();
        //       ammoLeft.render(); //<--consume muchisimo tiempo

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
        std::cout << "Expected frame time: " << expectedFrameTime << std::endl;
        std::cout << "Frame time: " << realFrameTime << std::endl;

        if (realFrameTime > expectedFrameTime) {
            // Calculate how many frames we are behind
            int framesBehind = realFrameTime / expectedFrameTime;
            // Adjust the current frame
            client_rabbit->reajustFrame(framesBehind);
            for (auto& rabbit: rabbits) {
                rabbit.second->reajustFrame(framesBehind);
            }
            for (auto& enemy: enemies) {
                enemy.second->reajustFrame(framesBehind);
            }
            for (auto& projectile: projectiles) {
                projectile.second->reajustFrame(framesBehind);
            }
            for (auto& supply: supplies) {
                supply.second->reajustFrame(framesBehind);
            }

            // Calculate the next frame start time
            frameStart += framesBehind * expectedFrameTime;
            Uint32 newFrameStart = frameStart + expectedFrameTime;

            // Wait until the start of the next frame
            Uint32 delayTime = newFrameStart - SDL_GetTicks();
            if (delayTime > 0) {
                SDL_Delay(delayTime);
            }
            frameStart = newFrameStart;  // Set new frame start time
        } else {
            Uint32 restTime = expectedFrameTime - realFrameTime;
            SDL_Delay(restTime);
            frameStart += expectedFrameTime;
        }
    }

    return 0;
} catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}
