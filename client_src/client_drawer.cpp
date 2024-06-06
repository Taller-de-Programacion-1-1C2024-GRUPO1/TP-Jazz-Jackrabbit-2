#include "client_drawer.h"

#include <algorithm>
#include <memory>
#include <utility>

#include "client_drawable.h"
#include "client_food_provider.h"
#include "client_map_loader.h"
#include "client_sound_manager.h"

enum  { None=0, JAZZ, SPAZ, LORI};
enum  { RABBITT=0, LIZARDD, CRABB, TURTLEE};
enum  { ALIVEE, RECIEVED_DAMAGEE, INTOXICATEDD, DEADD };
enum  { STANDD, RUNN, RUN_FASTT, FALLINGG, JUMPINGG };

ClientDrawer::ClientDrawer(std::shared_ptr<Queue<Command*>> q_cmds, Queue<Snapshot>& q_snapshots):
        q_cmds(q_cmds),
        q_snapshots(q_snapshots),
        game_running(false),
        client_id(0),
        score(0),
        lives(0),
        client_rabbit(nullptr),
        rabbit_width(0),
        rabbit_height(0),
        keyboard_handler(q_cmds) {}

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
            std::cout << "INtoxicado " << std::endl;
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

void loadAnimationsForCharacter(std::string &animationsPath, std::string &texturePath,const int character_id) {
    switch(character_id){
        case JAZZ:
            animationsPath = "../external/animations/jazz.yml";
            texturePath = JAZZ_IMG;
            break;
        case SPAZ:
            animationsPath = "../external/animations/spaz.yml";
            texturePath = SPAZ_IMG;
            break;
        case LORI:
            animationsPath = "../external/animations/lori.yml";
            texturePath = LORI_IMG;
            break;  
    }
}

void loadAnimationForEnemy(std::string &animationsPath, std::string &texturePath, const int enemy_id) {
    switch(enemy_id){
        case LIZARDD:
            animationsPath = "../external/animations/lizard.yml";
            texturePath = ENEMIES_IMG;
            break;
        case CRABB:
            animationsPath = "../external/animations/crab.yml";
            texturePath = ENEMIES_IMG;
            break;
        case TURTLEE:
            animationsPath = "../external/animations/turtle.yml";
            texturePath = TURTLE_IMG;
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

    } else if (state[SDL_SCANCODE_LEFT]) {

    }
}


int ClientDrawer::run(int player_id) try {
    client_id = player_id;
    keyboard_handler.setId(player_id);
    std::cout << "My id is: " << client_id << std::endl;

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

    // Number images
    NumberImages numberImages(renderer);
    numberImages.setCorner(0);

    // Heart banner
    WeaponData::initialize();
    FoodProvider::initialize();
    HeartsBanner banner(renderer);
    AmmoLeft ammoLeft(renderer);

    // Read first snapshot!

    Snapshot initial_snapshot = q_snapshots.pop();
    game_running = !initial_snapshot.get_end_game();

    std::vector<std::unique_ptr<Drawable>> mapComponents = mapLoader.loadMap(initial_snapshot.map_dimensions.map_data, CARROTUS_TILE, mapColor, cameraPosition);

    std::string animationsPath;
    std::string texturePath;
    std::cout << "VOY A SETEAR" << std::endl;
    for (auto& rabbit: initial_snapshot.rabbits) {
        SDL2pp::Rect textureRect(0, 0, rabbit_width * 32, rabbit_height * 32);
        SDL2pp::Rect onMapRect(rabbit.pos_x , rabbit.pos_y , 64, 64);
        std::cout << "RABBIT WIDTH: " << rabbit_width << " RABBIT HEIGHT: " << rabbit_height << std::endl;

        std::cout << "Rabbit pos: " << rabbit.pos_x << " " << rabbit.pos_y << std::endl;
        if (rabbit.id == client_id) {
            score = rabbit.score;

            banner.setCurrentLives(rabbit.lives);
            ammoLeft.setWeapon(rabbit.weapon);
            ammoLeft.setAmmo(rabbit.ammo);
            playerPosition.x = rabbit.pos_x;
            playerPosition.y = rabbit.pos_y;

            loadAnimationsForCharacter(animationsPath, texturePath, 1);
            client_rabbit = new ShiftingDrawable(renderer, texturePath, characterColor, cameraPosition,
                                                 textureRect, onMapRect, soundManager);
                                                 
            client_rabbit->loadAnimations(animationsPath);

            setAnimationFromSnapshot(rabbit, client_rabbit);
            client_rabbit->setDirection(rabbit.direction);

        } else {
            loadAnimationsForCharacter(animationsPath, texturePath, rabbit.champion_type);
            ShiftingDrawable* newRabbit =
                    new ShiftingDrawable(renderer, texturePath, characterColor, cameraPosition,
                                         textureRect, onMapRect, soundManager);
            newRabbit->loadAnimations(animationsPath);
            setAnimationFromSnapshot(rabbit, newRabbit);
            newRabbit->setDirection(rabbit.direction);
            rabbits.emplace(rabbit.id, newRabbit);
        }
    }
    for (auto& enemy: initial_snapshot.enemies) {
        SDL2pp::Rect textureRect(0, 0, rabbit_width, rabbit_height);
        SDL2pp::Rect onMapRect(enemy.pos_x * 32, enemy.pos_y * 32, 64, 64);
        std::cout << "Seteando posicion inicial de enemigo a" << enemy.pos_x << " " << enemy.pos_y<< std::endl;
        loadAnimationForEnemy(animationsPath, texturePath, enemy.enemy_type);
        ShiftingDrawable* newEnemy =
                new ShiftingDrawable(renderer, texturePath, enemyAndItemsColor, cameraPosition,
                                     textureRect, onMapRect, soundManager);
        newEnemy->loadAnimations(animationsPath);
        newEnemy->setAnimation("Walk");
        newEnemy->setDirection(enemy.direction);
        enemies.emplace(enemy.id, newEnemy);
    }
    for (auto& projectile: initial_snapshot.projectiles) {
        SDL2pp::Rect textureRect(0, 0, 32, 32);
        SDL2pp::Rect onMapRect(projectile.pos_x * 32, projectile.pos_y * 32, 32, 32);
        ShiftingDrawable* newProjectile =
                new ShiftingDrawable(renderer, PROJECTILES_IMG, enemyAndItemsColor, cameraPosition,
                                     textureRect, onMapRect, soundManager);
        WeaponData::loadAnimationsToProjectile(projectile.weapon, newProjectile);
        newProjectile->setAnimation("Move");
        projectiles.emplace(projectile.id, newProjectile);
    }
    for (auto& valuable: initial_snapshot.supplies) {
        SDL2pp::Rect textureRect(0, 0, 32, 32);
        SDL2pp::Rect onMapRect(valuable.pos_x * 32, valuable.pos_y * 32, 32, 32);
        ShiftingDrawable* newValuable =
                new ShiftingDrawable(renderer, ITEMS_IMG, enemyAndItemsColor, cameraPosition,
                                     textureRect, onMapRect, soundManager);
        newValuable->loadAnimations("../external/animations/valuables/coin.yml");
        newValuable->setAnimation("Flip");
        supplies.emplace(valuable.id, newValuable);
    }
        std::cout << "TERMINE DE SETEAR" << std::endl;


    // Game state
    const int FPS = 60;
    const int expectedFrameTime = 1000 / FPS;
    Uint32 frameStart = SDL_GetTicks();

    // Main loop

    while (game_running) {

        // EVENTS HANDLER
        //handle_events(game_running);
        keyboard_handler.listenForCommands(game_running);
        // En tu bucle principal o función de actualización de cámara
        desiredCameraPosition.x = playerPosition.x - (window.GetWidth() / 2);
        desiredCameraPosition.y = playerPosition.y - (window.GetHeight() / 2);

        // Interpolación lineal para suavizar el movimiento
        cameraPosition.x += (desiredCameraPosition.x - cameraPosition.x) * lerpFactor;
        cameraPosition.y += (desiredCameraPosition.y - cameraPosition.y) * lerpFactor;

        Snapshot snapshot;
        // SNAPSHOT RECEIVER
        if (q_snapshots.try_pop(snapshot)){
            std::cout << "Popie un snapshot in-game!!!!!!!!!!!!!!!!!!!" << std::endl;
       
            for (const auto& rabbit: snapshot.rabbits) {
                    std::cout << "Seteando posicion de conejo a" << rabbit.pos_x << " " << rabbit.pos_y << std::endl;
                if (rabbit.id == client_id) {
                                                                    std::cout << " es tu  id" << std::endl;

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
                                                std::cout << "no es tu  id" << std::endl;

                        it->second->setPosition(rabbit.pos_x , rabbit.pos_y);
                        setAnimationFromSnapshot(rabbit, it->second);
                        it->second->setDirection(rabbit.direction);
                    } else {
                        // Crear un nuevo conejo
                        std::cout << "Nuevo rabbit" << std::endl;
                        SDL2pp::Rect textureRect(0, 0, rabbit_width, rabbit_height);
                        SDL2pp::Rect onMapRect(rabbit.pos_x * 32, rabbit.pos_y * 32, rabbit_width,
                                               rabbit_height);
                        loadAnimationsForCharacter(animationsPath, texturePath, rabbit.champion_type);
                        ShiftingDrawable* newRabbit = new ShiftingDrawable(
                                renderer, texturePath, characterColor, cameraPosition, textureRect,
                                onMapRect, soundManager);
                        newRabbit->loadAnimations(animationsPath);
                        setAnimationFromSnapshot(rabbit, newRabbit);
                        newRabbit->setDirection(rabbit.direction);
                        rabbits.emplace(rabbit.id, newRabbit);
                    }
                }
            }
            for (const auto& enemy: snapshot.enemies) {
                auto it = enemies.find(enemy.id);
                if (it != enemies.end()) {
                    std::cout << " HOLA" << std::endl;
                    std::cout << "Seteando posicion de enemigo a" << enemy.pos_x << " " << enemy.pos_y << std::endl;
                    it->second->setPosition(enemy.pos_x*32, enemy.pos_y*32);
                    it->second->setDirection(enemy.direction);
                } else {
                    // Crear un nuevo enemigo
                    SDL2pp::Rect textureRect(0, 0, rabbit_width, rabbit_height);
                    SDL2pp::Rect onMapRect(enemy.pos_x * 32, enemy.pos_y * 32, rabbit_width, rabbit_height);
                    loadAnimationForEnemy(animationsPath, texturePath, enemy.enemy_type);
                    ShiftingDrawable* newEnemy = new ShiftingDrawable(
                            renderer, texturePath, enemyAndItemsColor, cameraPosition, textureRect,
                            onMapRect, soundManager);
                    newEnemy->loadAnimations(animationsPath);
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
                    SDL2pp::Rect onMapRect(projectile.pos_x * 32, projectile.pos_y * 32, 32, 32);
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
                    SDL2pp::Rect onMapRect(valuable.pos_x * 32, valuable.pos_y * 32, 32, 32);
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

