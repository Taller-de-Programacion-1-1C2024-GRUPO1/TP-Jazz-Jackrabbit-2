#ifndef CLIENT_MAP_LOADER_H
#define CLIENT_MAP_LOADER_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

#include "client_drawable.h"
#include "client_textures_provider.h"

const int TILE_WIDTH = 10;
const int BLOCK_SIZE = 32;

class MapLoader {
private:
    Renderer& renderer;
    std::shared_ptr<SDL2pp::Texture> clean_texture;
    std::shared_ptr<SDL2pp::Texture> default_texture;
    int map_width;
    int map_heigth;

public:
    explicit MapLoader(Renderer& renderer, const int map_texture, const int map_width,
                       const int map_heigth):
            renderer(renderer), map_width(map_width), map_heigth(map_heigth) {
        switch (map_texture) {
            case JUNGLE:
                clean_texture = TexturesProvider::getTexture("Clean-Jungle");
                default_texture = TexturesProvider::getTexture("Default-Jungle");
                break;
            case CARROTUS:
                clean_texture = TexturesProvider::getTexture("Clean-Carrotus");
                default_texture = TexturesProvider::getTexture("Default-Carrotus");
                break;
            default:
                throw std::invalid_argument("Invalid map texture");
        }
    }

    std::vector<std::unique_ptr<Drawable>> loadMap(const DynamicMap& map,
                                                   SDL2pp::Point& cameraPosition) {
        std::vector<std::unique_ptr<Drawable>> tiles;
        const auto& data = map.map_data;
        for (int key = 0; key <= 4; key++) {
            auto it = data.find(key);
            if (it != data.end()) {
                auto& matrix = it->second;
                int x = 0;
                int y = 0;
                for (int j = 0; j < map_heigth; j++) {
                    for (int k = 0; k < map_width; k++) {
                        int id = matrix[k][j];
                        if (id != 65535) {
                            SDL2pp::Rect srcRect;
                            srcRect.x = (id % TILE_WIDTH) * 32;
                            srcRect.y = (id / TILE_WIDTH) * 32;
                            srcRect.w = BLOCK_SIZE;
                            srcRect.h = BLOCK_SIZE;

                            SDL2pp::Rect destRect;
                            destRect.x = x * BLOCK_SIZE;
                            destRect.y = y * BLOCK_SIZE;
                            destRect.w = BLOCK_SIZE;
                            destRect.h = BLOCK_SIZE;

                            std::unique_ptr<Drawable> drawable = std::make_unique<Drawable>(
                                    renderer, cameraPosition, srcRect, destRect);
                            if (key == BACKGROUND_LAYER) {
                                drawable->setTexture(default_texture);
                            } else {
                                drawable->setTexture(clean_texture);
                            }
                            tiles.push_back(std::move(drawable));
                        }
                        x++;
                    }
                    x = 0;
                    y++;
                }
            }
        }

        return tiles;
    }
};

#endif  // CLIENT_MAP_LOADER_H
