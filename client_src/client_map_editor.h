#include <algorithm>  // Para std::max
#include <fstream>    // Para std::ofstream
#include <iostream>
#include <map>  // Para std::map
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>  // Para guardar el mapa en un archivo .yml

#include "../common_src/constants.h"
#include "../game_src/constants_game.h"

#include "client_constants.h"
#include "client_textures_provider.h"

class Editor {
public:
    // Constructor for precharged map
    explicit Editor(const std::string& map_name):
            sdl(SDL_INIT_VIDEO),
            image(IMG_INIT_PNG),
            ttf(),
            window("Map editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                   EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT, 0),
            renderer(window, -1, SDL_RENDERER_ACCELERATED),
            font(FONT_TTF_04B_30, 15) {
        loadEntityTextures();
        loadMapData(map_name);
    }

    // Constructor for new map
    Editor(const int map, const int mapWidth, const int mapHeight, const std::string& nameByUser,
           const int max_players):
            sdl(SDL_INIT_VIDEO),
            image(IMG_INIT_PNG),
            ttf(),
            window("Map editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                   EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT, 0),
            renderer(window, -1, SDL_RENDERER_ACCELERATED),
            width(mapWidth),
            height(mapHeight),
            name(nameByUser),
            maxPlayers(max_players),
            texture(map),
            currentRabbitSpawns(0),
            font(FONT_TTF_04B_30, 15) {
        loadTileTextures(map);
        loadEntityTextures();
        initializeGrids();
    }

    void run() {
        bool running = true;
        bool mouseIsBeingClicked = false;
        int last_x = 0;
        int last_y = 0;
        SDL_Event event;
        Rect selectedEntityDst;

        while (running) {
            while (SDL_PollEvent(&event) || mouseIsBeingClicked) {
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        handleMouseClick(event, mouseIsBeingClicked, last_x, last_y,
                                         selectedEntityDst);
                        break;
                    case SDL_MOUSEMOTION:
                        handleMouseMotion(event, mouseIsBeingClicked, last_x, last_y);
                        break;
                    case SDL_MOUSEWHEEL:
                        handleMouseWheel(event);
                        break;
                    case SDL_MOUSEBUTTONUP:
                        mouseIsBeingClicked = false;
                        break;
                }
            }

            // Update the renderer's color based on save status
            if (wrongSave) {
                renderer.SetDrawColor(255, 0, 0, 0);
                wrongSave = false;
            } else if (correctSave) {
                renderer.SetDrawColor(0, 255, 0, 0);
                correctSave = false;
            } else {
                renderer.SetDrawColor(0, 0, 0, 255);
            }

            renderer.Clear();
            renderDrawableGrid();
            renderButtons();
            if (mode == TEXTURE) {
                renderTextureGrid();
            } else if (mode == ENTITY) {
                renderEntities(selectedEntityDst);
            }
            renderer.Present();
            SDL_Delay(200);
        }
    }

    void handleMouseClick(SDL_Event& event, bool& mouseIsBeingClicked, int& last_x, int& last_y,
                          Rect& selectedEntityDst) {
        mouseIsBeingClicked = true;
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (x >= SAVE_BUTTON_POS_X && x < SAVE_BUTTON_POS_X + BUTTON_WIDTH && y >= BUTTON_POS_Y &&
            y < BUTTON_END_Y) {
            // Click en el botón de guardar
            if (currentRabbitSpawns == maxPlayers) {
                saveMap();
                correctSave = true;
            } else {
                wrongSave = true;
            }
        } else if (x >= TILE_BUTTON_POS_X && x < TILE_BUTTON_POS_X + BUTTON_WIDTH &&
                   y >= BUTTON_POS_Y && y < BUTTON_END_Y) {
            // Click en el botón de texturas
            mode = TEXTURE;
        } else if (x >= ENTITY_BUTTON_POS_X && x < ENTITY_BUTTON_POS_X + BUTTON_WIDTH &&
                   y >= BUTTON_POS_Y && y < BUTTON_END_Y) {
            // Click en el botón de entidades
            mode = ENTITY;
        } else if (x >= PAINT_BUTTON_POS_X && x < PAINT_BUTTON_POS_X + BUTTON_WIDTH &&
                   y >= BUTTON_POS_Y && y < BUTTON_END_Y) {
            // Click en el botón de pintar
            currentTool = PAINT;
        } else if (x >= ERASE_BUTTON_POS_X && x < ERASE_BUTTON_POS_X + BUTTON_WIDTH &&
                   y >= BUTTON_POS_Y && y < BUTTON_END_Y) {
            // Click en el botón de borrar
            currentTool = ERASE;
        } else if (x >= MOVE_BUTTON_POS_X && x < MOVE_BUTTON_POS_X + BUTTON_WIDTH &&
                   y >= BUTTON_POS_Y && y < BUTTON_END_Y) {
            // Click en el botón para moverse en pantalla
            currentTool = MOVE;
            last_x = x;
            last_y = y;
        } else if (x >= BACKGROUND_BUTTON_POS_X && x < BACKGROUND_BUTTON_POS_X + BUTTON_WIDTH &&
                   y >= BUTTON_POS_Y && y < BUTTON_END_Y) {
            // Click en los botones de capas
            currentLayer = BACKGROUND_LAYER;
        } else if (x >= DIAG_LEFT_BUTTON_POS_X && x < DIAG_LEFT_BUTTON_POS_X + BUTTON_WIDTH &&
                   y >= BUTTON_POS_Y && y < BUTTON_END_Y) {
            currentLayer = DIAG_LEFT_LAYER;
        } else if (x >= DIAG_RIGHT_BUTTON_POS_X && x < DIAG_RIGHT_BUTTON_POS_X + BUTTON_WIDTH &&
                   y >= BUTTON_POS_Y && y < BUTTON_END_Y) {
            currentLayer = DIAG_RIGHT_LAYER;
        } else if (x >= COLLIDER_BUTTON_POS_X && x < COLLIDER_BUTTON_POS_X + BUTTON_WIDTH &&
                   y >= BUTTON_POS_Y && y < BUTTON_END_Y) {
            currentLayer = COLLIDER_LAYER;
        } else if (x >= DECORATION_BUTTON_POS_X && x < DECORATION_BUTTON_POS_X + BUTTON_WIDTH &&
                   y >= BUTTON_POS_Y && y < BUTTON_END_Y) {
            currentLayer = DECORATION_LAYER;
        } else if (mode == TEXTURE && (x < SPACE_BEFORE_DRAWABLE_GRID && y >= BUTTONS_AREA_HEIGHT &&
                                       y < EDITOR_SCREEN_WIDTH - BUTTONS_AREA_HEIGHT)) {
            // Click en la grilla de texturas
            y += tileVerticalOffset - BUTTONS_AREA_HEIGHT;  // Ajustar para el desplazamiento
                                                            // vertical y la posición de los botones

            if (y < BLOCK_DIVISION * (static_cast<int>((textures.size() + 9) / TILE_WIDTH))) {
                int index = (y / BLOCK_DIVISION) * TILE_WIDTH + (x / BLOCK_DIVISION);
                if (index < static_cast<int>(textures.size())) {
                    selectedTextureIndex = index;
                }
            }
        } else if (mode == ENTITY && x < SPACE_BEFORE_DRAWABLE_GRID && y >= BUTTONS_AREA_HEIGHT &&
                   y < EDITOR_SCREEN_WIDTH - BUTTONS_AREA_HEIGHT) {
            // Click en la grilla de entidades
            for (auto& entity: entities_dst) {
                int entityX = entity.second.GetX();
                int entityY = entity.second.GetY();
                int entityWidth = entity.second.GetW();
                int entityHeight = entity.second.GetH();

                if (x >= entityX && x < entityX + entityWidth && y >= entityY &&
                    y < entityY + entityHeight) {
                    selectedEntityIndex = entity.first;
                    selectedEntityDst = entity.second;
                    break;
                }
            }
        } else if (x >= SPACE_BEFORE_DRAWABLE_GRID &&
                   x < std::min(BLOCK_DIVISION * width + SPACE_BEFORE_DRAWABLE_GRID,
                                EDITOR_SCREEN_WIDTH) &&
                   y >= BUTTONS_AREA_HEIGHT &&
                   y < std::min(EDITOR_SCREEN_HEIGHT,
                                BUTTONS_AREA_HEIGHT + BLOCK_DIVISION * height)) {
            // Click en la grilla dibujable
            int gridX = (x - SPACE_BEFORE_DRAWABLE_GRID + gridHorizontalOffset) / BLOCK_DIVISION;
            int gridY = (y - BUTTONS_AREA_HEIGHT + gridVerticalOffset) / BLOCK_DIVISION;
            if (mode == ENTITY) {
                handleEntityGridClick(gridX, gridY);
            } else if (mode == TEXTURE) {
                handleTextureGridClick(gridX, gridY);
            }
        }
    }

    void handleEntityGridClick(int gridX, int gridY) {
        if (currentTool == PAINT && selectedEntityIndex >= 0 &&
            selectedEntityIndex < static_cast<int>(entities_textures.size())) {
            bool canPaint = true;
            std::vector<int> restrictedLayers = {COLLIDER_LAYER, DIAG_LEFT_LAYER, DIAG_RIGHT_LAYER};
            auto isRestrictedLayer = [&](int layer) {
                return grid[gridY][gridX][layer] != nullptr ||
                       (gridY + 1 < static_cast<int>(grid.size()) &&
                        grid[gridY + 1][gridX][layer] != nullptr) ||
                       (gridX + 1 < static_cast<int>(grid[gridY].size()) &&
                        grid[gridY][gridX + 1][layer] != nullptr) ||
                       (gridY + 1 < static_cast<int>(grid.size()) &&
                        gridX + 1 < static_cast<int>(grid[gridY + 1].size()) &&
                        grid[gridY + 1][gridX + 1][layer] != nullptr);
            };
            canPaint = !std::any_of(restrictedLayers.begin(), restrictedLayers.end(),
                                    isRestrictedLayer);

            if (selectedEntityIndex == GEM_SPAWN || selectedEntityIndex == COIN_SPAWN) {
                auto restLayer = [&](int layer) {
                    return grid[gridY][gridX][layer] == nullptr &&
                           (gridY + 1 >= static_cast<int>(grid.size()) ||
                            grid[gridY + 1][gridX][layer] == nullptr) &&
                           (gridX + 1 >= static_cast<int>(grid[gridY].size()) ||
                            grid[gridY][gridX + 1][layer] == nullptr) &&
                           (gridY + 1 >= static_cast<int>(grid.size()) ||
                            gridX + 1 >= static_cast<int>(grid[gridY + 1].size()) ||
                            grid[gridY + 1][gridX + 1][layer] == nullptr);
                };
                canPaint = std::any_of(restrictedLayers.begin(), restrictedLayers.end(), restLayer);
            }

            if (canPaint) {
                if (selectedEntityIndex == RABBIT_SPAWN) {
                    if (currentRabbitSpawns == maxPlayers) {
                        return;
                    }
                    currentRabbitSpawns++;
                }
                entities_grid[gridY][gridX] = selectedEntityIndex;
            }
        } else if (currentTool == ERASE) {
            if (entities_grid[gridY][gridX] == RABBIT_SPAWN) {
                currentRabbitSpawns--;
            }
            entities_grid[gridY][gridX] = -1;
        }
    }

    void handleTextureGridClick(int gridX, int gridY) {
        if (currentTool == PAINT && selectedTextureIndex >= 0 &&
            selectedTextureIndex < static_cast<int>(textures.size())) {
            grid[gridY][gridX][currentLayer] = textures[selectedTextureIndex];
        } else if (currentTool == ERASE) {
            grid[gridY][gridX][currentLayer] = nullptr;
        }
    }

    void handleMouseMotion(SDL_Event& event, bool mouseIsBeingClicked, int& last_x, int& last_y) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x >= SPACE_BEFORE_DRAWABLE_GRID &&
            x < std::min(BLOCK_DIVISION * width + SPACE_BEFORE_DRAWABLE_GRID,
                         EDITOR_SCREEN_WIDTH) &&
            y >= BUTTONS_AREA_HEIGHT &&
            y < std::min(EDITOR_SCREEN_HEIGHT, BUTTONS_AREA_HEIGHT + BLOCK_DIVISION * height) &&
            mouseIsBeingClicked) {
            // Motion en la grilla dibujable
            if (currentTool == MOVE) {
                updateScrollOffsets(x - last_x, y - last_y, gridHorizontalOffset,
                                    gridVerticalOffset);
                last_x = x;
                last_y = y;
            } else if (currentTool == PAINT || currentTool == ERASE) {
                int gridX =
                        (x - SPACE_BEFORE_DRAWABLE_GRID + gridHorizontalOffset) / BLOCK_DIVISION;
                int gridY = (y - BUTTONS_AREA_HEIGHT + gridVerticalOffset) / BLOCK_DIVISION;
                if (mode == TEXTURE) {
                    handleTextureGridClick(gridX, gridY);
                }
            }
        }
    }

    void handleMouseWheel(SDL_Event& event) {
        if (mode == TEXTURE) {
            tileVerticalOffset = std::max(
                    std::min((tileVerticalOffset + event.wheel.y * SCROLL_SPEED),
                             static_cast<int>((((textures.size() + 9) / 10) * BLOCK_DIVISION) +
                                              BUTTONS_AREA_HEIGHT - 640)),
                    0);
        }
    }

    void renderButtons() {
        renderer.SetClipRect(SDL2pp::NullOpt);
        drawButton(PAINT_BUTTON_POS_X, BUTTON_POS_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "Paint",
                   currentTool == PAINT);
        drawButton(ERASE_BUTTON_POS_X, BUTTON_POS_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "Erase",
                   currentTool == ERASE);
        drawButton(MOVE_BUTTON_POS_X, BUTTON_POS_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "Move",
                   currentTool == MOVE);
        if (mode == TEXTURE) {
            drawButton(BACKGROUND_BUTTON_POS_X, BUTTON_POS_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "Backg",
                       currentLayer == BACKGROUND_LAYER);
            drawButton(DIAG_LEFT_BUTTON_POS_X, BUTTON_POS_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "DiagL",
                       currentLayer == DIAG_LEFT_LAYER);
            drawButton(DIAG_RIGHT_BUTTON_POS_X, BUTTON_POS_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "DiagR",
                       currentLayer == DIAG_RIGHT_LAYER);
            drawButton(COLLIDER_BUTTON_POS_X, BUTTON_POS_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "Coll",
                       currentLayer == COLLIDER_LAYER);
            drawButton(DECORATION_BUTTON_POS_X, BUTTON_POS_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "Decor",
                       currentLayer == DECORATION_LAYER);
        }
        drawButton(890, 10, BUTTON_WIDTH, BUTTON_HEIGHT, "Tile", mode == TEXTURE);
        drawButton(980, 10, BUTTON_WIDTH, BUTTON_HEIGHT, "Entity", mode == ENTITY);
        drawButton(1200, 10, BUTTON_WIDTH, BUTTON_HEIGHT, "Save", false);
    }

    void renderTextureGrid() {
        // Renderizo la grilla de texturas
        Rect textureClipRect = {0, 60, 320, 640};
        renderer.SetClipRect(textureClipRect);
        for (int i = 0; i < static_cast<int>(textures.size()); ++i) {
            Rect dst;
            dst.x = (i % TILE_WIDTH) * BLOCK_DIVISION;
            dst.y = BUTTONS_AREA_HEIGHT + (i / TILE_WIDTH) * BLOCK_DIVISION - tileVerticalOffset;
            dst.w = BLOCK_DIVISION;
            dst.h = BLOCK_DIVISION;

            renderer.Copy(*textures[i], SDL2pp::NullOpt, dst);

            if (i == selectedTextureIndex) {
                renderer.SetDrawColor(255, 0, 0, 255);
                renderer.DrawRect(dst);
                renderer.SetDrawColor(255, 0, 0, 255);
            }
        }
        renderer.SetClipRect(SDL2pp::NullOpt);  // Limpip el recorte
    }

    void renderEntities(SDL2pp::Rect selectedEntityDst) {
        Rect entityClipRect = {0, BUTTONS_AREA_HEIGHT, SPACE_BEFORE_DRAWABLE_GRID,
                               EDITOR_SCREEN_HEIGHT - BUTTONS_AREA_HEIGHT};
        renderer.SetClipRect(entityClipRect);
        renderer.Copy(entities_textures[RABBIT_SPAWN], entities_src[RABBIT_SPAWN],
                      entities_dst[RABBIT_SPAWN]);
        renderer.Copy(entities_textures[CRAB_SPAWN], entities_src[CRAB_SPAWN],
                      entities_dst[CRAB_SPAWN]);
        renderer.Copy(entities_textures[LIZARD_SPAWN], entities_src[LIZARD_SPAWN],
                      entities_dst[LIZARD_SPAWN]);
        renderer.Copy(entities_textures[TURTLE_SPAWN], entities_src[TURTLE_SPAWN],
                      entities_dst[TURTLE_SPAWN]);
        renderer.Copy(entities_textures[COIN_SPAWN], entities_src[COIN_SPAWN],
                      entities_dst[COIN_SPAWN]);
        renderer.Copy(entities_textures[GEM_SPAWN], entities_src[GEM_SPAWN],
                      entities_dst[GEM_SPAWN]);

        // Dibujo un rectángulo rojo alrededor de la entidad seleccionada
        if (selectedEntityIndex != -1) {
            renderer.SetDrawColor(255, 0, 0, 255);
            renderer.DrawRect(selectedEntityDst);
            renderer.SetDrawColor(255, 0, 0, 255);
        }
        renderer.SetClipRect(SDL2pp::NullOpt);  // Limpio el recorte
    }

    void renderDrawableGrid() {
        // Renderizo la grilla dibujable
        Rect gridClipRect = {SPACE_BEFORE_DRAWABLE_GRID, BUTTONS_AREA_HEIGHT, 960, 640};
        renderer.SetClipRect(gridClipRect);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                Rect dst;
                dst.x = SPACE_BEFORE_DRAWABLE_GRID + j * BLOCK_DIVISION - gridHorizontalOffset;
                dst.y = BUTTONS_AREA_HEIGHT + i * BLOCK_DIVISION - gridVerticalOffset;
                dst.w = BLOCK_DIVISION;
                dst.h = BLOCK_DIVISION;

                for (int layer = 0; layer < TEXTURE_LAYERS; ++layer) {
                    if (grid[i][j][layer] != nullptr) {
                        renderer.Copy(*grid[i][j][layer], SDL2pp::NullOpt, dst);
                    }
                }
                int entity = entities_grid[i][j];
                if (entity != -1) {
                    renderer.Copy(entities_textures[entity], entities_src[entity], dst);
                }
                renderer.SetDrawColor(255, 255, 255, 255);
                renderer.DrawRect(dst);
                renderer.SetDrawColor(0, 0, 0, 255);
            }
        }
    }

    void updateScrollOffsets(int x, int y, int& gridHorizontalOffset, int& gridVerticalOffset) {
        gridHorizontalOffset =
                std::max(std::min(gridHorizontalOffset - x,
                                  (width * BLOCK_DIVISION) -
                                          (EDITOR_SCREEN_WIDTH - SPACE_BEFORE_DRAWABLE_GRID)),
                         0);
        gridVerticalOffset = std::max(
                std::min(gridVerticalOffset - y,
                         (height * BLOCK_DIVISION) - (EDITOR_SCREEN_HEIGHT - BUTTONS_AREA_HEIGHT)),
                0);
    }

private:
    SDL2pp::SDL sdl;
    SDL2pp::SDLImage image;
    SDL2pp::SDLTTF ttf;
    Window window;
    Renderer renderer;
    std::vector<std::shared_ptr<SDL2pp::Texture>> textures;
    std::vector<std::vector<std::vector<std::shared_ptr<SDL2pp::Texture>>>> grid;
    std::vector<std::vector<int>> entities_grid;
    std::vector<Texture> entities_textures;

    int selectedTextureIndex = -1;
    int selectedEntityIndex = -1;
    int tileVerticalOffset = 0;    // Desplazamiento vertical para la grilla de texturas
    int gridHorizontalOffset = 0;  // Desplazamiento horizontal para la grilla dibujable
    int gridVerticalOffset = 0;    // Desplazamiento vertical para la grilla dibujable
    int width = 0;
    int height = 0;
    std::string name = "";
    int maxPlayers = 0;
    int texture = CARROTUS;
    int currentRabbitSpawns = 0;
    bool wrongSave = false;
    bool correctSave = false;

    Tool currentTool = PAINT;             // Herramienta actual
    int currentLayer = BACKGROUND_LAYER;  // Capa actual
    Mode mode = TEXTURE;                  // Modo actual
    Font font;

    std::map<int, Rect> entities_src;
    std::map<int, Rect> entities_dst;

    void drawButton(int x, int y, int w, int h, const char* label, bool selected) {
        Rect rect = {x, y, w, h};
        if (selected) {
            renderer.SetDrawColor(0, 255, 0, 255);  // Verde si está seleccionada
        } else {
            renderer.SetDrawColor(128, 128, 128, 255);  // Blanco si no está seleccionada
        }
        renderer.FillRect(rect);
        renderer.SetDrawColor(0, 0, 0, 255);
        renderer.DrawRect(rect);

        // Renderizar el texto del botón
        SDL2pp::Color textColor(0, 0, 0, 255);  // Color del texto
        Surface textSurface = font.RenderText_Solid(label, textColor);
        Texture textTexture(renderer, textSurface);

        Rect textRect;
        textRect.x = x + (w - textSurface.GetWidth()) / 2;   // Centrar el texto horizontalmente
        textRect.y = y + (h - textSurface.GetHeight()) / 2;  // Centrar el texto verticalmente
        textRect.w = textSurface.GetWidth();
        textRect.h = textSurface.GetHeight();

        renderer.Copy(textTexture, SDL2pp::NullOpt, textRect);
    }

    void loadMapData(const std::string& map_name) {
        std::string mapPath = "../external/maps/" + map_name + ".yml";
        YAML::Node map = YAML::LoadFile(mapPath);
        name = map["name"].as<std::string>();
        texture = map["texture"].as<int>();
        maxPlayers = map["max_players"].as<int>();
        width = map["width"].as<int>();
        height = map["height"].as<int>();
        initializeGrids();
        loadTileTextures(texture);
        populateTextureGrid(map);
        populateEntityGrid(map);
    }

    void loadTileTextures(int map = -1) {
        std::string textureImg[] = {JUNGLE_TILES_PNG, CARROTUS_TILES_PNG};
        int textureIndex = (map == -1) ? texture : map;

        std::cout << "Loading texture: " << texture << std::endl;
        processTexture(textureImg[textureIndex]);
    }

    void processTexture(const std::string& path) {
        std::cout << "Loading texture: " << path << std::endl;
        Surface surface(path);
        SDL2pp::Color colorKey = {87, 0, 203, 0};
        Uint32 mappedColorKey =
                SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b);
        SDL_SetColorKey(surface.Get(), SDL_TRUE, mappedColorKey);

        for (int i = 0; i < surface.GetHeight(); i += BLOCK_DIVISION) {
            for (int j = 0; j < surface.GetWidth(); j += BLOCK_DIVISION) {
                Rect src;
                src.x = j;
                src.y = i;
                src.w = BLOCK_DIVISION;
                src.h = BLOCK_DIVISION;

                Surface destSurface(0, BLOCK_DIVISION, BLOCK_DIVISION, BLOCK_DIVISION, 0, 0, 0, 0);
                surface.Blit(src, destSurface, {0, 0, 0, 0});
                SDL2pp::Texture current_texture(renderer, destSurface);
                textures.push_back(std::make_shared<Texture>(std::move(current_texture)));
            }
        }
    }

    void loadEntityTextures() {
        std::vector<std::string> imagePaths = {JAZZ_IMG,   ENEMIES_PNG, ENEMIES_PNG,
                                               TURTLE_PNG, ITEMS_PNG,   ITEMS_PNG};
        for (const auto& path: imagePaths) {
            Surface entitySurface(path);
            Texture entityTexture(renderer, entitySurface);
            entities_textures.push_back(std::move(entityTexture));
        }

        entities_src[RABBIT_SPAWN] = {1, 12, 35, 49};
        entities_src[CRAB_SPAWN] = {734, 310, 40, 32};
        entities_src[LIZARD_SPAWN] = {18, 15, 64, 52};
        entities_src[TURTLE_SPAWN] = {11, 58, 69, 54};
        entities_src[COIN_SPAWN] = {481, 1218, 28, 27};
        entities_src[GEM_SPAWN] = {147, 1241, 29, 30};

        entities_dst[RABBIT_SPAWN] = {0, 64, 64, 64};
        entities_dst[CRAB_SPAWN] = {0, 128, 64, 64};
        entities_dst[LIZARD_SPAWN] = {64, 128, 64, 64};
        entities_dst[TURTLE_SPAWN] = {128, 128, 64, 64};
        entities_dst[COIN_SPAWN] = {0, 256, 32, 32};
        entities_dst[GEM_SPAWN] = {32, 256, 32, 32};
    }

    void initializeGrids() {
        grid = std::vector<std::vector<std::vector<std::shared_ptr<SDL2pp::Texture>>>>(
                height, std::vector<std::vector<std::shared_ptr<SDL2pp::Texture>>>(
                                width, std::vector<std::shared_ptr<SDL2pp::Texture>>(5, nullptr)));
        entities_grid = std::vector<std::vector<int>>(height, std::vector<int>(width, -1));
    }

    void populateTextureGrid(YAML::Node& map) {
        for (int layer = 0; layer < TEXTURE_LAYERS; ++layer) {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    int index = map["layers"][layer]["data"][i][j].as<int>();
                    if (index != -1) {
                        grid[i][j][layer] = textures[index];
                    }
                }
            }
        }
    }

    void populateEntityGrid(YAML::Node& map) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int index = map["layers"][TEXTURE_LAYERS]["data"][i][j].as<int>();
                if (index != -1) {
                    if (index == RABBIT_SPAWN) {
                        currentRabbitSpawns++;
                    }
                    entities_grid[i][j] = index;
                }
            }
        }
    }

    void saveMap() {
        std::map<std::shared_ptr<Texture>, int> textureIndices;
        for (int i = 0; i < static_cast<int>(textures.size()); ++i) {
            textureIndices[textures[i]] = i;
        }

        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "name" << YAML::Value << name;
        out << YAML::Key << "texture" << YAML::Value << texture;
        out << YAML::Key << "max_players" << YAML::Value << maxPlayers;
        out << YAML::Key << "width" << YAML::Value << width;
        out << YAML::Key << "height" << YAML::Value << height;

        out << YAML::Key << "layers";
        out << YAML::Value << YAML::BeginSeq;

        for (int layer = 0; layer < 5; ++layer) {
            out << YAML::BeginMap;
            out << YAML::Key << "id" << YAML::Value << layer;
            out << YAML::Key << "data" << YAML::Value << YAML::BeginSeq;

            for (const auto& row: grid) {
                std::vector<int> textureRow;
                for (const auto& cell: row) {
                    // Obtener el índice de la textura
                    std::shared_ptr<SDL2pp::Texture> current_texture = cell[layer];
                    int index = current_texture ? textureIndices[current_texture] : -1;
                    textureRow.push_back(index);
                }
                out << YAML::Flow << textureRow;
            }

            out << YAML::EndSeq;
            out << YAML::EndMap;
        }

        out << YAML::BeginMap;
        out << YAML::Key << "id" << YAML::Value << 5;  // ID 5 para la capa de entidades
        out << YAML::Key << "data" << YAML::Value << YAML::BeginSeq;

        for (const auto& row: entities_grid) {
            std::vector<int> entityRow(row.size());
            std::transform(row.begin(), row.end(), entityRow.begin(),
                           [](const auto& entity) { return entity; });
            out << YAML::Flow << entityRow;
        }

        out << YAML::EndSeq;
        out << YAML::EndMap;

        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::string outputPath = DEST_PATH + name + ".yml";
        std::ofstream fout(outputPath);
        fout << out.c_str();

        // Agrego el nombre del mapa a maps.txt
        std::ofstream mapsFile("../external/maps/maps.txt", std::ios::app);

        if (mapsFile.is_open()) {
            // Check if the name already exists in the file
            std::ifstream checkFile("../external/maps/maps.txt");
            std::string line;
            bool nameExists = false;

            while (std::getline(checkFile, line)) {
                if (line == name + ".yml") {
                    nameExists = true;
                    break;
                }
            }

            checkFile.close();

            // Write the name if it doesn't exist
            if (!nameExists) {
                mapsFile << name << ".yml" << '\n';
            } else {
                // std::cout << "Name already exists in maps.txt: " << name << ".yml" << '\n';
            }
        } else {
            std::cerr << "Unable to open maps.txt for writing.\n";
        }
    }
};
