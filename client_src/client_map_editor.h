#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm> // Para std::max
#include <yaml-cpp/yaml.h> // Para guardar el mapa en un archivo .yml
#include <fstream> // Para std::ofstream
#include <map> // Para std::map

#include <iostream>
#include "../common_src/constants.h"
#include "../game_src/constants_game.h"
#include <SDL2pp/SDL2pp.hh>

enum Tool { PAINT, ERASE };
enum Mode { TEXTURE, ENTITY };

// g++ main.cpp -lyaml-cpp -lSDL2 -lSDL2_image -lSDL2_ttf -o myprogram

#define FONT "../client_src/resources/fonts/04B_30__.ttf"
#define JAZZ "../client_src/resources/characters/Jazz.png"
#define ITEMS "../client_src/resources/items/items.png"
#define ENEMIES "../client_src/resources/enemies/Enemies.png"

#define CASTLE_IMG "../client_src/resources/tiles/castle.png"
#define CARROTUS_IMG "../client_src/resources/tiles/carrotus.png"
#define BEACH_IMG "../client_src/resources/tiles/beach.png"

//Donde se va a colocar el mapa resultante
#define DEST_PATH "../external/maps/"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 700;

struct Entity {
    int who;
    Rect rect;
};

class Editor {
public:
    Editor(const int map, const int mapWidth, const int mapHeight, const std::string& nameByUser, const int max_players) :
        sdl(SDL_INIT_VIDEO),
        image(IMG_INIT_PNG),
        ttf(),
        window("Map editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        width(mapWidth),
        height(mapHeight),
        name(nameByUser),
        maxPlayers(max_players),
        currentRabbitSpawns(0),
        font(FONT, 15)
    {
        const char* textureImg[] = {CASTLE_IMG, BEACH_IMG, CARROTUS_IMG};
        
        Surface surface(textureImg[map]);
        SDL2pp::Color colorKey = {87, 0, 203, 0};
        Uint32 mappedColorKey = SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b);
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
                SDL2pp::Texture texture(renderer, destSurface);
                textures.push_back(std::make_shared<Texture>(std::move(texture)));
            }
        }
        grid = std::vector<std::vector<std::vector<std::shared_ptr<SDL2pp::Texture>>>>(height, std::vector<std::vector<std::shared_ptr<SDL2pp::Texture>>>(width, std::vector<std::shared_ptr<SDL2pp::Texture>>(5, nullptr)));
        entities_grid = std::vector<std::vector<Entity>>(height, std::vector<Entity>(width, {-1, {0, 0, 0, 0}}));

        //Cargar texturas de entidades
        std::vector<std::string> imagePaths = {JAZZ, ENEMIES, ENEMIES, ENEMIES, ITEMS, ITEMS};
        std::vector<Rect> entityRects;

        for (const auto& path : imagePaths) {
            Surface entitySurface(path);
            Texture entityTexture(renderer, entitySurface);
            entitiesTextures.push_back(std::move(entityTexture));
        }

        jazz_src = {1, 12, 35, 49};
        jazz_dst = {0, 64, 64, 64};

        crab_src = {734, 310, 40, 32};
        crab_dst = {0, 128, 64, 64};

        lizard_src = {18, 15, 64, 52};
        lizard_dst = {64, 128, 64, 64};

        coin_src = {481, 1218, 28, 27};
        coin_dst = {0, 256, 32, 32};

        diamond_src = {147, 1241, 29, 30};
        diamond_dst = {32, 256, 32, 32};
    }

    void run() {
        bool running = true;
        SDL_Event event;
        Rect selectedEntityDst;

        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    // Click en el botón de guardar y salir
                    if (x >= 1200 && x < 1280 && y >= 10 && y < 50) {
                        saveMap();
                        running = false;
                    }
                    // Click en el botón de texturas
                    else if (x >= 730 && x < 810 && y >= 10 && y < 50) {
                        mode = TEXTURE;
                    }
                    // Click en el botón de entidades
                    else if (x >= 820 && x < 900 && y >= 10 && y < 50) {
                        mode = ENTITY;
                    }
                    // Click en el botón de pintar
                    else if (x >= 10 && x < 90 && y >= 10 && y < 50) {
                        currentTool = PAINT;
                    }
                    // Click en el botón de borrar
                    else if (x >= 100 && x < 180 && y >= 10 && y < 50) {
                        currentTool = ERASE;
                    }
                    // Click en los botones de capas

                    else if (x >= 190 && x < 270 && y >= 10 && y < 50) {
                        currentLayer = BACKGROUND_LAYER;
                    } else if (x >= 280 && x < 360 && y >= 10 && y < 50) {
                        currentLayer = DIAG_LEFT_LAYER;
                    } else if (x >= 370 && x < 450 && y >= 10 && y < 50) {
                        currentLayer = DIAG_RIGHT_LAYER;
                    } else if (x >= 460 && x < 540 && y >= 10 && y < 50) {
                        currentLayer = COLLIDER_LAYER;
                    } else if (x >= 550 && x < 630 && y >= 10 && y < 50) {
                        currentLayer = DECORATION_LAYER;
                    }

                    // Click en la grilla de texturas
                    else if (mode == TEXTURE && (x < 320 && y >= 60 && y < 640)) {
                        y += scrollOffset - 60;  // Ajustar para el desplazamiento vertical y la posición de los botones

                        if (x < 32 * 10 && y < 32 * (static_cast<int>((textures.size() + 9) / 10))) {
                            int index = (y / 32) * 10 + (x / 32);
                            if (index < static_cast<int>(textures.size())) {
                                selectedTextureIndex = index;
                            }
                        }
                    }

                    else if (mode == ENTITY && x < 320 && y >= 60 && y < 640) {
                        if (x > jazz_dst.x && x < jazz_dst.x + jazz_dst.w && y > jazz_dst.y && y < jazz_dst.y + jazz_dst.h) {
                            selectedEntityIndex = RABBIT_SPAWN;
                            selectedEntityDst = jazz_dst;
                        } else if (x > crab_dst.x && x < crab_dst.x + crab_dst.w && y > crab_dst.y && y < crab_dst.y + crab_dst.h) {
                            selectedEntityIndex = CRAB_SPAWN;
                            selectedEntityDst = crab_dst;
                        } else if (x > lizard_dst.x && x < lizard_dst.x + lizard_dst.w && y > lizard_dst.y && y < lizard_dst.y + lizard_dst.h) {
                            selectedEntityIndex = LIZARD_SPAWN;
                            selectedEntityDst = lizard_dst;
                        } else if (x > coin_dst.x && x < coin_dst.x + coin_dst.w && y > coin_dst.y && y < coin_dst.y + coin_dst.h) {
                            selectedEntityIndex = COIN_SPAWN;
                            selectedEntityDst = coin_dst;
                        } else if (x > diamond_dst.x && x < diamond_dst.x + diamond_dst.w && y > diamond_dst.y && y < diamond_dst.y + diamond_dst.h) {
                            selectedEntityIndex = GEM_SPAWN;
                            selectedEntityDst = diamond_dst;
                        }

                    }

                    // Click en la grilla dibujable
                    else if (x >= 320 && x < BLOCK_DIVISION* width && y >= 60 && y < SCREEN_HEIGHT) {
                        //NOTA: X es absoluto, Y lo toma como relativo (siempre entre 0 y SCREEN_HEIGHT)
                        if (mode == ENTITY && selectedEntityIndex >= 0 && selectedEntityIndex < static_cast<int>(entitiesTextures.size())) {
                            int gridX = (x - 320 + horizontalScrollOffset) / BLOCK_DIVISION;
                            int gridY = (y - 60 + verticalScrollOffset) / BLOCK_DIVISION;
                            if (currentTool == PAINT){
                                // Verificar si la celda actual, la celda debajo y la celda a la derecha no tienen una capa de tipo COLISIONABLE, DIAGONAL IZQUIERDA o DIAGONAL DERECHA
                                bool canPaint = true;
                                std::vector<int> restrictedLayers = {COLLIDER_LAYER, DIAG_LEFT_LAYER, DIAG_RIGHT_LAYER};
                                for (int layer : restrictedLayers) {
                                    if (grid[gridY][gridX][layer] != nullptr ||
                                        (gridY + 1 < static_cast<int>(grid.size()) && grid[gridY + 1][gridX][layer] != nullptr) ||
                                        (gridX + 1 < static_cast<int>(grid[gridY].size()) && grid[gridY][gridX + 1][layer] != nullptr) ||
                                        (gridY + 1 < static_cast<int>(grid.size()) && gridX + 1 < static_cast<int>(grid[gridY + 1].size()) && grid[gridY + 1][gridX + 1][layer] != nullptr)) {
                                        canPaint = false;
                                        break;
                                        }
                                }

                                if (canPaint) {
                                    switch(selectedEntityIndex){
                                    case RABBIT_SPAWN:
                                        if (currentRabbitSpawns < maxPlayers) {
                                            entities_grid[gridY][gridX] = Entity{RABBIT_SPAWN, jazz_src};
                                            currentRabbitSpawns++;
                                        }
                                        break;
                                    case CRAB_SPAWN:
                                        entities_grid[gridY][gridX] = Entity{CRAB_SPAWN, crab_src};
                                        break;
                                    case LIZARD_SPAWN:
                                        entities_grid[gridY][gridX] = Entity{LIZARD_SPAWN, lizard_src};
                                        break;
                                    case COIN_SPAWN:
                                        entities_grid[gridY][gridX] = Entity{COIN_SPAWN, coin_src};
                                        break;
                                    case GEM_SPAWN:
                                        entities_grid[gridY][gridX] = Entity{GEM_SPAWN, diamond_src};
                                        break;
                                    }
                                }
                            }
                            else if (currentTool == ERASE) {
                                entities_grid[gridY][gridX] = {-1, {0, 0, 0, 0}};
                            }
                        } else if (mode == TEXTURE) {
                            int gridX = (x - 320 + horizontalScrollOffset) / BLOCK_DIVISION;
                            int gridY = (y - 60 + verticalScrollOffset) / BLOCK_DIVISION;
                            if (currentTool == PAINT && selectedTextureIndex >= 0 && selectedTextureIndex < static_cast<int>(textures.size())) {
                                if (currentLayer == DIAG_LEFT_LAYER || currentLayer == DIAG_RIGHT_LAYER || currentLayer == COLLIDER_LAYER) {
                                    if (grid[gridY][gridX][DIAG_LEFT_LAYER] != nullptr && currentLayer != DIAG_LEFT_LAYER) {
                                        grid[gridY][gridX][DIAG_LEFT_LAYER] = nullptr;
                                    }
                                    if (grid[gridY][gridX][DIAG_RIGHT_LAYER] != nullptr && currentLayer != DIAG_RIGHT_LAYER) {
                                        grid[gridY][gridX][DIAG_RIGHT_LAYER] = nullptr;
                                    }
                                    if (grid[gridY][gridX][COLLIDER_LAYER] != nullptr && currentLayer != COLLIDER_LAYER) {
                                        grid[gridY][gridX][COLLIDER_LAYER] = nullptr;
                                    }
                                }
                                grid[gridY][gridX][currentLayer] = textures[selectedTextureIndex];
                            } else if (currentTool == ERASE) {
                                grid[gridY][gridX][currentLayer] = nullptr;
                            }
                        }
                    }
                } else if (event.type == SDL_MOUSEWHEEL) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    // Scroll solo sobre la grilla de texturas
                    if (x < 320 && y >= 60) {
                        scrollOffset -= event.wheel.y * 10;  // Se desplaza 10 píxeles por unidad de la rueda
                        if (scrollOffset < 0) scrollOffset = 0;  // Limito el desplazamiento hacia arriba
                        int maxScrollOffset = std::max(0, static_cast<int>(((textures.size() + 9) / 10) * 32 - 640));
                        if (scrollOffset > maxScrollOffset) scrollOffset = maxScrollOffset;  // Limito el desplazamiento hacia abajo
                    }
                    // Scroll horizontal para la grilla dibujable
                    else if (x >= 320 && y >= 60) {
                        horizontalScrollOffset -= event.wheel.x * 10;  // Se desplaza 10 píxeles por unidad de la rueda
                        if (horizontalScrollOffset < 0) horizontalScrollOffset = 0;  // Limito el desplazamiento hacia la izquierda
                        int maxHorizontalScrollOffset = std::max(0, 32 * width - 960);
                        if (horizontalScrollOffset > maxHorizontalScrollOffset) horizontalScrollOffset = maxHorizontalScrollOffset;  // Limito el desplazamiento hacia la derecha

                        verticalScrollOffset -= event.wheel.y * 10;  // Se desplaza 10 píxeles por unidad de la rueda
                        if (verticalScrollOffset < 0) verticalScrollOffset = 0;  // Limito el desplazamiento hacia arriba
                        int maxVerticalScrollOffset = std::max(0, 32 * height - 640);
                        if (verticalScrollOffset > maxVerticalScrollOffset) verticalScrollOffset = maxVerticalScrollOffset;  // Limito el desplazamiento hacia abajo
                    }
                }
            }

            renderer.SetDrawColor(0, 0, 0, 255);
            renderer.Clear();

            drawButton(10, 10, 80, 40, "Paint", currentTool == PAINT);
            drawButton(100, 10, 80, 40, "Erase", currentTool == ERASE);
            if (mode == TEXTURE) {
                drawButton(190, 10, 80, 40, "Back", currentLayer == BACKGROUND_LAYER);
                drawButton(280, 10, 80, 40, "DiagL", currentLayer == DIAG_LEFT_LAYER);
                drawButton(370, 10, 80, 40, "DiagR", currentLayer == DIAG_RIGHT_LAYER);
                drawButton(460, 10, 80, 40, "Coll", currentLayer == COLLIDER_LAYER);
                drawButton(550, 10, 80, 40, "Dec", currentLayer == DECORATION_LAYER);
            }
            drawButton(730, 10, 80, 40, "Tile", mode == TEXTURE);
            drawButton(820, 10, 80, 40, "Entity", mode == ENTITY);

            drawButton(1200, 10, 80, 40, "Exit", false);

            // Renderizo la grilla de texturas
            if (mode == TEXTURE) {
                Rect textureClipRect = { 0, 60, 320, 640 };
                renderer.SetClipRect(textureClipRect);
                for (int i = 0; i < static_cast<int>(textures.size()); ++i) {
                    Rect dst;
                    dst.x = (i % 10) * 32;
                    dst.y = 60 + (i / 10) * 32 - scrollOffset;
                    dst.w = 32;
                    dst.h = 32;

                    renderer.Copy(*textures[i], SDL2pp::NullOpt, dst);

                    if (i == selectedTextureIndex) {
                        renderer.SetDrawColor(255, 0, 0, 255);
                        renderer.DrawRect(dst);
                        renderer.SetDrawColor(255, 0, 0, 255);
                    }
                }
                renderer.SetClipRect(SDL2pp::NullOpt);  // Limpiar el recorte
            } else if (mode == ENTITY) {
                renderer.Copy(entitiesTextures[RABBIT_SPAWN], jazz_src, jazz_dst);
                renderer.Copy(entitiesTextures[CRAB_SPAWN], crab_src, crab_dst);
                renderer.Copy(entitiesTextures[LIZARD_SPAWN], lizard_src, lizard_dst);
                renderer.Copy(entitiesTextures[COIN_SPAWN], coin_src, coin_dst);
                renderer.Copy(entitiesTextures[GEM_SPAWN], diamond_src, diamond_dst);

                // Dibujo un rectángulo rojo alrededor de la entidad seleccionada
                if (selectedEntityIndex != -1) {
                    renderer.SetDrawColor(255, 0, 0, 255);
                    renderer.DrawRect(selectedEntityDst);
                    renderer.SetDrawColor(255, 0, 0, 255);
                }
            }

            // Renderizo la grilla dibujable
            Rect gridClipRect = { 320, 60, 960, 640 };
            renderer.SetClipRect(gridClipRect);
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    Rect dst;
                    dst.x = 320 + j * 32 - horizontalScrollOffset;
                    dst.y = 60 + i * 32 - verticalScrollOffset;  // Ajustar para la posición de los botones
                    dst.w = 32;
                    dst.h = 32;

                    for (int layer = 0; layer < 5; ++layer) {
                        if (grid[i][j][layer] != nullptr) {
                            renderer.Copy(*grid[i][j][layer], SDL2pp::NullOpt, dst);
                        }
                    }
                    Entity entity = entities_grid[i][j];
                    if (entity.who != -1) {
                        renderer.Copy(entitiesTextures[entity.who], entity.rect, dst);
                    }
                    renderer.SetDrawColor(255, 255, 255, 255);
                    renderer.DrawRect(dst);
                    renderer.SetDrawColor(0, 0, 0, 255);
                }
            }
            renderer.SetClipRect(SDL2pp::NullOpt);  // Limpiar el recorte
            renderer.Present();
        }
    }

private:
    SDL2pp::SDL sdl;
    SDL2pp::SDLImage image;
    SDL2pp::SDLTTF ttf;
    Window window;
    Renderer renderer;
    std::vector<std::shared_ptr<SDL2pp::Texture>> textures;
    std::vector<std::vector<std::vector<std::shared_ptr<SDL2pp::Texture>>>> grid;
    std::vector<Texture> entitiesTextures;  // Grilla de entidades
    std::vector<std::vector<Entity>> entities_grid;

    int selectedTextureIndex = -1;
    int selectedEntityIndex = -1;
    int scrollOffset = 0;  // Desplazamiento vertical para la grilla de texturas
    int horizontalScrollOffset = 0;  // Desplazamiento horizontal para la grilla dibujable
    int verticalScrollOffset = 0;  // Desplazamiento vertical para la grilla dibujable
    int width;
    int height;
    std::string name;
    int maxPlayers;
    int currentRabbitSpawns;

    Tool currentTool = PAINT;  // Herramienta actual
    int currentLayer = BACKGROUND_LAYER;  // Capa actual
    Mode mode = TEXTURE;  // Modo actual
    Font font;
    Rect jazz_src, jazz_dst, crab_src, crab_dst, lizard_src, lizard_dst, coin_src, coin_dst, diamond_src, diamond_dst;

    void drawButton(int x, int y, int w, int h, const char* label, bool selected) {
        Rect rect = { x, y, w, h };
        if (selected) {
            renderer.SetDrawColor(0, 255, 0, 255);  // Verde si está seleccionada
        } else {
            renderer.SetDrawColor(255, 255, 255, 255);  // Blanco si no está seleccionada
        }
        renderer.FillRect(rect);
        renderer.SetDrawColor(0, 0, 0, 255);
        renderer.DrawRect(rect);

        // Renderizar el texto del botón
        SDL2pp::Color textColor(0, 0, 0, 255);  // Color del texto
        Surface textSurface = font.RenderText_Solid(label, textColor);
        Texture textTexture(renderer, textSurface);

        Rect textRect;
        textRect.x = x + (w - textSurface.GetWidth()) / 2;  // Centrar el texto horizontalmente
        textRect.y = y + (h - textSurface.GetHeight()) / 2;  // Centrar el texto verticalmente
        textRect.w = textSurface.GetWidth();
        textRect.h = textSurface.GetHeight();

        renderer.Copy(textTexture, SDL2pp::NullOpt, textRect);
    }

    void saveMap() {
        std::map<std::shared_ptr<Texture>, int> textureIndices;
        for (int i = 0; i < static_cast<int>(textures.size()); ++i) {
            textureIndices[textures[i]] = i;
        }

        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "name" << YAML::Value << name;
        out << YAML::Key << "max_players" << YAML::Value << maxPlayers;
        out << YAML::Key << "width" << YAML::Value << width;
        out << YAML::Key << "height" << YAML::Value << height;

        out << YAML::Key << "layers";
        out << YAML::Value << YAML::BeginSeq;

        for (int layer = 0; layer < 5; ++layer) {
            out << YAML::BeginMap;
            out << YAML::Key << "id" << YAML::Value << layer;
            out << YAML::Key << "data" << YAML::Value << YAML::BeginSeq;

            for (const auto& row : grid) {
                std::vector<int> textureRow;
                for (const auto& cell : row) {
                    // Obtener el índice de la textura
                    std::shared_ptr<SDL2pp::Texture> texture = cell[layer];
                    int index = texture ? textureIndices[texture] : -1;
                    textureRow.push_back(index);
                }
                out << YAML::Flow << textureRow;
            }

            out << YAML::EndSeq;
            out << YAML::EndMap;
        }

        // Agregar una sexta matriz para las entidades
        out << YAML::BeginMap;
        out << YAML::Key << "id" << YAML::Value << 5;  // ID 5 para la capa de entidades
        out << YAML::Key << "data" << YAML::Value << YAML::BeginSeq;

        for (const auto& row : entities_grid) {
            std::vector<int> entityRow;
            for (const auto& entity : row) {
                entityRow.push_back(entity.who);
            }
            out << YAML::Flow << entityRow;
        }

        out << YAML::EndSeq;
        out << YAML::EndMap;

        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::string outputPath = DEST_PATH + name + ".yml";
        std::ofstream fout(outputPath);
        fout << out.c_str();
    }
};


