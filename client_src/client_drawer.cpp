#include "client_drawer.h"

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

void ClientDrawer::showFinalScreen(Renderer& renderer, Snapshot& lastSnapshot) {
    const int initial_offset = 100;
    Font font(FONT_TTF_04B_30, 24);
    std::vector<RabbitSnapshot> rabbits = lastSnapshot.rabbits;

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

    // order rabbits vector
    std::sort(rabbits.begin(), rabbits.end(),
              [](const RabbitSnapshot& a, const RabbitSnapshot& b) { return a.score > b.score; });

    // Find the player with the highest score
    RabbitSnapshot winner = rabbits[0];
    std::string winnerText;
    if (winner.id == client_id) {
        // If the winner is the client, show a different message
        winnerText = "Winner: YOU! Congratulations";
    } else {
        winnerText = "Winner: " + winner.player_name;
    }
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

    for (int i = 0; i < static_cast<int>(rabbits.size()); i++) {
        std::string playerText;
        playerText = std::to_string(i + 1) + ". " + rabbits[i].player_name + " - " +
                     std::to_string(rabbits[i].score) + " points";
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

    renderer.SetDrawColor(135, 206, 235);
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


int ClientDrawer::run(int player_id) try {
    client_id = player_id;
    keyboard_handler.setId(player_id);

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
    TexturesProvider::init(renderer);

    // Read first snapshot!
    Snapshot initial_snapshot;
    while (!q_snapshots.try_pop(initial_snapshot)) {
        std::cout << "Waiting for initial snapshot..." << std::endl;
        showLoadingScreen(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    showLoadingScreen(renderer);

    int map_width = initial_snapshot.map_dimensions.height;
    int map_height = initial_snapshot.map_dimensions.width;
    int map_texture = initial_snapshot.map_dimensions.map_texture_id;


    MapLoader mapLoader(renderer, map_texture, map_width, map_height);

    // Number images
    FontPrinter fontPrinter(renderer);
    fontPrinter.setCorner(0);

    // Heart banner
    HeartsBanner banner(renderer);
    AmmoLeft ammoLeft(renderer);
    FoodProvider foodProvider;
    TopScores topScores(renderer, player_id);
    Clock clock(renderer);

    SDL2pp::Point playerPosition(10, 10);
    SDL2pp::Point cameraPosition(0, 0);
    SDL2pp::Point desiredCameraPosition(0, 0);


    game_running = !initial_snapshot.get_end_game();
    clock.update(initial_snapshot.get_match_time());
    std::vector<std::unique_ptr<Drawable>> mapComponents =
            mapLoader.loadMap(initial_snapshot.map_dimensions.map_data, cameraPosition);

    rabbit_width = initial_snapshot.map_dimensions.rabbit_width;
    rabbit_height = initial_snapshot.map_dimensions.rabbit_height;

    for (auto& rabbit: initial_snapshot.rabbits) {
        topScores.addCurrentSnapshotScore(rabbit.id, rabbit.player_name, rabbit.score);
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
        } else if (supply.supply_type == SNIPER_AMMO || supply.supply_type == MACHINEGUN_AMMO ||
                   supply.supply_type == RAYGUN_AMMO) {
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
            newFood->setTexture(TexturesProvider::getTexture("Items"));
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

            clock.update(snapshot.get_match_time());

            // RABBITS UPDATE

            std::set<int> rabbitIds;
            for (const auto& pair: rabbits) {
                rabbitIds.insert(pair.first);
            }
            for (const auto& rabbit: snapshot.rabbits) {
                topScores.addCurrentSnapshotScore(rabbit.id, rabbit.player_name, rabbit.score);
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
                    projectile->resize(BLOCK_DIVISION * 2, BLOCK_DIVISION * 2);
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
                if (ammo.supply_type == MACHINEGUN_AMMO || ammo.supply_type == SNIPER_AMMO ||
                    ammo.supply_type == RAYGUN_AMMO) {
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
                        newFood->setTexture(TexturesProvider::getTexture("Items"));
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

        // Actualizar la posición de la cámara para que siga al jugador
        cameraPosition.x = static_cast<int>(playerPosition.x - SCREEN_WIDTH / 2);
        cameraPosition.y = static_cast<int>(playerPosition.y - SCREEN_HEIGHT / 2);

        if (cameraPosition.x < 0)
            cameraPosition.x = 0;
        if (cameraPosition.y < 0)
            cameraPosition.y = 0;
        if (cameraPosition.x > map_width * BLOCK_DIVISION - SCREEN_WIDTH)
            cameraPosition.x = map_width * BLOCK_DIVISION - SCREEN_WIDTH;
        if (cameraPosition.y > map_height * BLOCK_DIVISION - SCREEN_HEIGHT)
            cameraPosition.y = map_height * BLOCK_DIVISION - SCREEN_HEIGHT;

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
        clock.render();

        std::string scoreStr = std::to_string(score);
        int offset = 32;  // Start position

        for (char c: scoreStr) {
            int number = c - '0';  // Convert char to int
            fontPrinter.renderNumber(number, offset, 0, 32);
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
