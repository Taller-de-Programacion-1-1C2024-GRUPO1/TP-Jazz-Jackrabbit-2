#include "client_drawer.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

ClientDrawer::ClientDrawer(Queue<std::unique_ptr<Command>>& q_cmds, Queue<Snapshot>& q_snapshots):
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

void ClientDrawer::showFinalScreen(Renderer& renderer, const Snapshot& snapshot) {
    const int initial_offset = 100;
    Font font(FONT_TTF_04B_30, 24);
    renderer.SetDrawColor(200, 200, 200);
    renderer.Clear();

    std::string titleText = "Game Over!";
    Texture titleTexture(renderer, font.RenderText_Solid(titleText, SDL_Color{255, 255, 255, 255}));

    int titleWidth = titleTexture.GetWidth();
    int titleHeight = titleTexture.GetHeight();

    Rect titleRect;
    titleRect.x = (SCREEN_WIDTH - titleWidth) / 2;
    titleRect.y = initial_offset;  // Offset from top of the screen for the title
    titleRect.w = titleWidth;
    titleRect.h = titleHeight;

    renderer.Copy(titleTexture, NullOpt, titleRect);

    // Find the player with the highest score
    auto winner = std::max_element(
            snapshot.rabbits.begin(), snapshot.rabbits.end(),
            [](const RabbitSnapshot& a, const RabbitSnapshot& b) { return a.score < b.score; });

    std::string winnerText = "Winner: Player " + std::to_string(winner->id);
    Texture winnerTexture(renderer,
                          font.RenderText_Solid(winnerText, SDL_Color{255, 255, 255, 255}));

    int winnerWidth = winnerTexture.GetWidth();
    int winnerHeight = winnerTexture.GetHeight();

    Rect winnerRect;
    winnerRect.x = (SCREEN_WIDTH - winnerWidth) / 2;
    winnerRect.y = titleHeight + initial_offset * 2;  // Offset from title for the winner
    winnerRect.w = winnerWidth;
    winnerRect.h = winnerHeight;

    renderer.Copy(winnerTexture, NullOpt, winnerRect);

    int yOffset = titleHeight + winnerHeight +
                  initial_offset * 2;  // Initial offset from top of the screen for the players

    for (const auto& player: snapshot.rabbits) {
        std::string playerText = "Player " + std::to_string(player.id) + ": " +
                                 std::to_string(player.score) + " points";
        Texture texture(renderer, font.RenderText_Solid(playerText, SDL_Color{255, 255, 255, 255}));

        int textWidth = texture.GetWidth();
        int textHeight = texture.GetHeight();

        Rect textRect;
        textRect.x = (SCREEN_WIDTH - textWidth) / 2;
        textRect.y = yOffset;
        textRect.w = textWidth;
        textRect.h = textHeight;

        renderer.Copy(texture, NullOpt, textRect);

        yOffset += textHeight + 20;  // Move offset down for the next player
    }

    renderer.Present();
}

void ClientDrawer::showLoadingScreen(Renderer& renderer) {
    Font font(FONT_TTF_04B_30, 24);
    Texture texture(renderer,
                    font.RenderText_Solid("Cargando partida...", SDL_Color{255, 255, 255, 255}));

    renderer.SetDrawColor(0, 63, 63);
    renderer.Clear();

    int textWidth = texture.GetWidth();
    int textHeight = texture.GetHeight();

    Rect textRect;
    textRect.x = (SCREEN_WIDTH - textWidth) / 2;
    textRect.y = (SCREEN_HEIGHT - textHeight) / 2;
    textRect.w = textWidth;
    textRect.h = textHeight;

    renderer.Copy(texture, NullOpt, textRect);
    renderer.Present();
}

int ClientDrawer::run(int player_id, int map_texture) try {
    client_id = player_id;
    keyboard_handler.setId(player_id);
    std::cout << "My id is: " << client_id << std::endl;
    std::cout << "Map texture: " << map_texture << std::endl;

    // Initialize SDL library
    SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    // Initialize SDL_ttf library
    SDLTTF ttf;

    SoundManager soundManager;  // pasarle parametros??

    // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
    Window window(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Create accelerated video renderer with default driver
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Background image
    Texture background(renderer, SDL2pp::Surface(FONDO_PNG));

    SDL_Color enemyAndItemsColor = {0, 128, 255, 1};  // Color en formato RGBA
    SDL_Color mapColor = {87, 0, 203, 0};
    MapLoader mapLoader(renderer);

    SDL2pp::Point playerPosition(10, 10);
    SDL2pp::Point cameraPosition(0, 0);
    SDL2pp::Point desiredCameraPosition(0, 0);
    float lerpFactor = 0.1f;

    std::string map_texture_path;
    switch (map_texture) {
        case CASTLE:
            map_texture_path = CASTLE_TILES_PNG;
            break;
        case CARROTUS:
            map_texture_path = CARROTUS_TILES_PNG;
            break;
    }

    // Number images
    NumberImages numberImages(renderer);
    numberImages.setCorner(0);

    // Heart banner
    HeartsBanner banner(renderer);
    AmmoLeft ammoLeft(renderer);
    FoodProvider foodProvider;
    TopScores topScores(renderer);

    // Read first snapshot!
    Snapshot initial_snapshot;
    while (!q_snapshots.try_pop(initial_snapshot)) {
        std::cout << "Waiting for initial snapshot..." << std::endl;
        showLoadingScreen(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    showLoadingScreen(renderer);

    game_running = !initial_snapshot.get_end_game();
    std::vector<std::unique_ptr<Drawable>> mapComponents = mapLoader.loadMap(
            initial_snapshot.map_dimensions.map_data, map_texture_path, mapColor, cameraPosition);

    rabbit_width = initial_snapshot.map_dimensions.rabbit_width;
    rabbit_height = initial_snapshot.map_dimensions.rabbit_height;

    for (auto& rabbit: initial_snapshot.rabbits) {
        topScores.addCurrentSnapshotScore(rabbit.id, rabbit.score);
        SDL2pp::Rect textureRect(0, 0, rabbit_width, rabbit_height);
        SDL2pp::Rect onMapRect(rabbit.pos_x, rabbit.pos_y, rabbit_width, rabbit_height);
        DrawableRabbit* newRabbit =
                new DrawableRabbit(renderer, cameraPosition, textureRect, onMapRect, soundManager);

        newRabbit->setCharacterFromSnapshot(rabbit.champion_type);
        newRabbit->setAnimationFromSnapshot(rabbit);
        newRabbit->setDirection(rabbit.direction);
        if (rabbit.id == client_id) {
            score = rabbit.score;

            banner.setCurrentLives(rabbit.lives);
            ammoLeft.setWeapon(rabbit.weapon);
            ammoLeft.setAmmo(rabbit.ammo);
            playerPosition.x = rabbit.pos_x;
            playerPosition.y = rabbit.pos_y;
            client_rabbit = newRabbit;
        } else {
            rabbits.emplace(rabbit.id, newRabbit);
        }
    }
    for (auto& enemy: initial_snapshot.enemies) {
        SDL2pp::Rect textureRect(0, 0, rabbit_width, rabbit_height);
        SDL2pp::Rect onMapRect(enemy.pos_x, enemy.pos_y, rabbit_width, rabbit_height);
        DrawableEnemy* newEnemy =
                new DrawableEnemy(renderer, cameraPosition, textureRect, onMapRect, soundManager);
        newEnemy->setEnemyFromSnapshot(enemy.enemy_type);
        newEnemy->setAnimation("Walk");
        newEnemy->setDirection(enemy.direction);
        enemies.emplace(enemy.id, newEnemy);
    }
    for (auto& projectile: initial_snapshot.projectiles) {
        SDL2pp::Rect textureRect(0, 0, 0, 0);
        SDL2pp::Rect onMapRect(projectile.pos_x, projectile.pos_y, rabbit_width / 2,
                               rabbit_height / 2);
        DrawableProjectile* newProjectile = new DrawableProjectile(
                renderer, cameraPosition, textureRect, onMapRect, soundManager);
        newProjectile->setProjectileFromSnapshot(projectile.weapon);
        newProjectile->setAnimation("Move");
        projectiles.emplace(projectile.id, newProjectile);
    }
    for (auto& supply: initial_snapshot.supplies) {
        SDL2pp::Rect onMapRect(supply.pos_x, supply.pos_y, rabbit_width / 2, rabbit_height / 2);
        if (supply.supply_type == COIN || supply.supply_type == GEM) {
            SDL2pp::Rect textureRect(0, 0, 0, 0);
            DrawableValuable* newValuable = new DrawableValuable(
                    renderer, cameraPosition, textureRect, onMapRect, soundManager);
            newValuable->setValuableFromSnapshot(supply.supply_type);
            newValuable->setAnimation("Flip");
            valuables.emplace(supply.id, newValuable);
        } else if (supply.supply_type == SNIPER_AMMO || supply.supply_type == MACHINEGUN_AMMO
                   || supply.supply_type == RAYGUN_AMMO) {
            SDL2pp::Rect textureRect(0, 0, 0, 0);
            DrawableAmmo* newAmmo = new DrawableAmmo(renderer, cameraPosition, textureRect,
                                                     onMapRect, soundManager);
            newAmmo->setAmmoFromSnapshot(supply.supply_type);
            newAmmo->setAnimation("Flip");
            ammo_drops.emplace(supply.id, newAmmo);
        } else if (supply.supply_type == HEALTH_CARROT || supply.supply_type == HOTDOG ||
                   supply.supply_type == HAMBURGER || supply.supply_type == ROTTEN_CHEESE) {
            SDL2pp::Rect textureRect = foodProvider.getFood(supply.supply_type);
            Drawable* newFood = new Drawable(renderer, cameraPosition, textureRect, onMapRect);
            newFood->setTexture(ITEMS_PNG, enemyAndItemsColor);
            food.emplace(supply.id, newFood);
        }
    }

    // Game state
    const int FPS = 60;
    const int expectedFrameTime = 1000 / FPS;
    Uint32 frameStart = SDL_GetTicks();

    // Main loop

    Snapshot snapshot;
    while (game_running) {

        // EVENTS HANDLER
        keyboard_handler.listenForCommands(game_running);

        desiredCameraPosition.x = playerPosition.x - (window.GetWidth() / 2);
        desiredCameraPosition.y = playerPosition.y - (window.GetHeight() / 2);

        // Interpolación lineal para suavizar el movimiento
        cameraPosition.x += (desiredCameraPosition.x - cameraPosition.x) * lerpFactor;
        cameraPosition.y += (desiredCameraPosition.y - cameraPosition.y) * lerpFactor;

        // SNAPSHOT RECEIVER

        if (q_snapshots.try_pop(snapshot)) {

            // Got a snapshot? Good
            while (q_snapshots.try_pop(snapshot)) {
                // Oh, more?
                // OK, let's keep the last one
            }
            if (game_running)
                // Before updating this variable,
                // we need to check if it is true
                // because user could have pressed ESC, Q or clicked on X
                // and the snapshot could overwritte the variable
                game_running = !snapshot.get_end_game();

            // RABBITS UPDATE
            //topScores.clearCurrentSnapshotScores();

            std::set<int> rabbitIds;
            for (const auto& pair: rabbits) {
                rabbitIds.insert(pair.first);
            }
            for (const auto& rabbit: snapshot.rabbits) {
                topScores.addCurrentSnapshotScore(rabbit.id, rabbit.score);
                if (rabbit.id == client_id) {
                    score = rabbit.score;
                    ammoLeft.setAmmo(rabbit.ammo);
                    ammoLeft.setWeapon(rabbit.weapon);
                    banner.setCurrentLives(rabbit.lives);
                    client_rabbit->setPosition(rabbit.pos_x, rabbit.pos_y);
                    client_rabbit->setAnimationFromSnapshot(rabbit);
                    client_rabbit->setDirection(rabbit.direction);
                    playerPosition.x = rabbit.pos_x;
                    playerPosition.y = rabbit.pos_y;
                    rabbitIds.erase(rabbit.id);
                } else {
                    auto it = rabbits.find(rabbit.id);
                    if (it != rabbits.end()) {
                        it->second->setPosition(rabbit.pos_x, rabbit.pos_y);
                        it->second->setAnimationFromSnapshot(rabbit);
                        it->second->setDirection(rabbit.direction);
                        rabbitIds.erase(rabbit.id);
                    } else {
                        // Crear un nuevo conejo
                        SDL2pp::Rect textureRect(0, 0, 0, 0);
                        SDL2pp::Rect onMapRect(rabbit.pos_x, rabbit.pos_y, rabbit_width,
                                               rabbit_height);
                        DrawableRabbit* newRabbit = new DrawableRabbit(
                                renderer, cameraPosition, textureRect, onMapRect, soundManager);
                        newRabbit->setCharacterFromSnapshot(rabbit.champion_type);
                        newRabbit->setAnimationFromSnapshot(rabbit);
                        newRabbit->setDirection(rabbit.direction);
                        rabbits.emplace(rabbit.id, newRabbit);
                    }
                }
            }
            for (const auto& id: rabbitIds) {
                delete rabbits[id];
                rabbits.erase(id);
            }

            // ENEMIES UPDATE
            std::set<int> enemyIds;
            for (const auto& pair: enemies) {
                enemyIds.insert(pair.first);
            }
            for (const auto& enemy: snapshot.enemies) {
                auto it = enemies.find(enemy.id);
                if (it != enemies.end()) {
                    if (enemy.enemy_type != NULL_ENEMY) {
                        it->second->setPosition(enemy.pos_x, enemy.pos_y);
                        it->second->setDirection(enemy.direction);
                        enemyIds.erase(enemy.id);
                    }
                } else {
                    // Creando un nuevo enemigo
                    if (enemy.enemy_type != NULL_ENEMY) {
                        SDL2pp::Rect textureRect(0, 0, 0, 0);
                        SDL2pp::Rect onMapRect(enemy.pos_x, enemy.pos_y, rabbit_width,
                                               rabbit_height);
                        DrawableEnemy* newEnemy = new DrawableEnemy(
                                renderer, cameraPosition, textureRect, onMapRect, soundManager);
                        newEnemy->setEnemyFromSnapshot(enemy.enemy_type);
                        newEnemy->setAnimation("Walk");
                        newEnemy->setDirection(enemy.direction);
                        enemies.emplace(enemy.id, newEnemy);
                    }
                }
            }
            for (const auto& id: enemyIds) {
                delete enemies[id];
                enemies.erase(id);
            }

            // PROJECTILES UPDATE
            std::set<int> projectilesIds;
            for (const auto& pair: projectiles) {
                projectilesIds.insert(pair.first);
            }
            for (const auto& projectile: snapshot.projectiles) {
                auto it = projectiles.find(projectile.id);
                if (it != projectiles.end()) {
                    it->second->setPosition(projectile.pos_x, projectile.pos_y);
                    projectilesIds.erase(projectile.id);
                } else {
                    // Creo un nuevo proyectil
                    SDL2pp::Rect textureRect(0, 0, 0, 0);
                    SDL2pp::Rect onMapRect(projectile.pos_x, projectile.pos_y, rabbit_width / 2,
                                           rabbit_height / 2);
                    DrawableProjectile* newProjectile = new DrawableProjectile(
                            renderer, cameraPosition, textureRect, onMapRect, soundManager);
                    newProjectile->setProjectileFromSnapshot(projectile.weapon);
                    newProjectile->setAnimation("Move");
                    projectiles.emplace(projectile.id, newProjectile);
                }
            }
            for (const auto& id: projectilesIds) {
                DrawableProjectile* projectile = projectiles[id];
                if (projectile->requiresExplosion()) {
                    projectile->resize(BLOCK_DIVISION*2, BLOCK_DIVISION*2);
                    projectile->playSoundOnDeath();
                    projectile->setAnimation("Explode");
                    projectile->setRequiresExplosion(false);
                } else if (projectile->isExploding()) {
                    projectile->keepExploding();
                } else {
                    delete projectiles[id];
                    projectiles.erase(id);
                }
            }

            // SUPPLIES UPDATE
            std::set<int> valuablesIds;
            for (const auto& pair: valuables) {
                valuablesIds.insert(pair.first);
            }

            // VALUABLES (COIN AND GEMS)
            for (const auto& supply: snapshot.supplies) {
                if (supply.supply_type == COIN || supply.supply_type == GEM) {
                    auto it = valuables.find(supply.id);
                    if (it == valuables.end()) {
                        valuablesIds.erase(supply.id);
                        // Creo un nuevo item
                        SDL2pp::Rect onMapRect(supply.pos_x, supply.pos_y, rabbit_width / 2,
                                               rabbit_height / 2);
                        SDL2pp::Rect textureRect(0, 0, 0, 0);
                        DrawableValuable* newValuable = new DrawableValuable(
                                renderer, cameraPosition, textureRect, onMapRect, soundManager);
                        newValuable->setValuableFromSnapshot(supply.supply_type);
                        newValuable->setAnimation("Flip");
                        valuables.emplace(supply.id, newValuable);
                    } else {
                        valuablesIds.erase(supply.id);
                    }
                }
            }
            for (const auto& id: valuablesIds) {
                valuables[id]->playSoundOnDeath();
                delete valuables[id];
                valuables.erase(id);
            }

            // AMMO
            std::set<int> ammoIds;
            for (const auto& pair: ammo_drops) {
                ammoIds.insert(pair.first);
            }
            for (const auto& ammo: snapshot.supplies) {
                if (ammo.supply_type == MACHINEGUN_AMMO || ammo.supply_type == SNIPER_AMMO 
                || ammo.supply_type == RAYGUN_AMMO) {
                    auto it = ammo_drops.find(ammo.id);
                    if (it == ammo_drops.end()) {
                        ammoIds.erase(ammo.id);
                        // Creo un nuevo item
                        SDL2pp::Rect onMapRect(ammo.pos_x, ammo.pos_y, rabbit_width / 2,
                                               rabbit_height / 2);
                        SDL2pp::Rect textureRect(0, 0, 0, 0);
                        DrawableAmmo* newAmmo = new DrawableAmmo(
                                renderer, cameraPosition, textureRect, onMapRect, soundManager);
                        newAmmo->setAmmoFromSnapshot(ammo.supply_type);
                        newAmmo->setAnimation("Flip");
                        ammo_drops.emplace(ammo.id, newAmmo);
                    } else {
                        ammoIds.erase(ammo.id);
                    }
                }
            }
            for (const auto& id: ammoIds) {
                ammo_drops[id]->playSoundOnDeath();
                delete ammo_drops[id];
                ammo_drops.erase(id);
            }

            // FOOD
            std::set<int> foodIds;
            for (const auto& pair: food) {
                foodIds.insert(pair.first);
            }

            // Second loop for food
            for (const auto& supply: snapshot.supplies) {
                // NOTA: LAS MUNICIONES ESTÁ SIENDO TRATADAS COMO COMIDA POR SER ESTATICAS
                // PROVISARIOMANETE LUEGO TENDRAN ANIMACIONES
                if (supply.supply_type == HEALTH_CARROT || supply.supply_type == HOTDOG ||
                    supply.supply_type == HAMBURGER || supply.supply_type == ROTTEN_CHEESE) {
                    auto it = food.find(supply.id);
                    if (it == food.end()) {
                        foodIds.erase(supply.id);
                        SDL2pp::Rect onMapRect(supply.pos_x, supply.pos_y, rabbit_width / 2,
                                               rabbit_height / 2);
                        SDL2pp::Rect textureRect = foodProvider.getFood(supply.supply_type);
                        Drawable* newFood =
                                new Drawable(renderer, cameraPosition, textureRect, onMapRect);
                        newFood->setTexture(ITEMS_PNG, enemyAndItemsColor);
                        food.emplace(supply.id, newFood);
                    } else {
                        foodIds.erase(supply.id);
                    }
                }
            }
            for (const auto& id: foodIds) {
                soundManager.playSoundEffect("Eating");
                delete food[id];
                food.erase(id);
            }
        }

        // UPDATE ENTITIES

        topScores.update();

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
        for (auto& valuable: valuables) {
            valuable.second->update();
        }
        for (auto& ammo: ammo_drops) {
            ammo.second->update();
        }
        for (auto& f: food) {
            f.second->update();
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
        for (auto& valuable: valuables) {
            valuable.second->render();
        }
        for (auto& ammo: ammo_drops) {
            ammo.second->render();
        }
        for (auto& f: food) {
            f.second->render();
        }

        banner.render();
        ammoLeft.render();  
        topScores.render();

        std::string scoreStr = std::to_string(score);
        int offset = 32;  // Start position

        for (char c: scoreStr) {
            int number = c - '0';  // Convert char to int
            numberImages.renderNumber(number, offset, 0, 32);
            offset += 24;  // Move position to the left for the next digit
        }

        // Show rendered frame
        renderer.Present();

        // Frame limiter: sleep for a little bit to not eat 100% of CPU
        Uint32 realFrameTime = SDL_GetTicks() - frameStart;
        // std::cout << "Expected frame time: " << expectedFrameTime << std::endl;
        // std::cout << "Frame time: " << realFrameTime << std::endl;

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
            for (auto& valuable: valuables) {
                valuable.second->reajustFrame(framesBehind);
            }
            for (auto& ammo: ammo_drops) {
                ammo.second->reajustFrame(framesBehind);
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
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + std::chrono::seconds(5);
    while (std::chrono::high_resolution_clock::now() < end) {
        showFinalScreen(renderer, snapshot);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
} catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}
