#ifndef CLIENT_MAP_LOADER_H
#define CLIENT_MAP_LOADER_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

#include "client_drawable.h"

const int TILE_WIDTH = 10;
const int BLOCK_SIZE = 32;

class MapLoader {
private:
    Renderer& renderer;

public:
    explicit MapLoader(Renderer& renderer): renderer(renderer) {}

    std::vector<std::unique_ptr<Drawable>> loadMap(const DynamicMap& map,
                                                   const std::string& texturePath,
                                                   const SDL2pp::Color& colorKey,
                                                   SDL2pp::Point& cameraPosition) {
        std::vector<std::unique_ptr<Drawable>> tiles;
        const auto& data = map.map_data;
        for (int key = 0; key <= 4; key++) {
            auto it = data.find(key);
            if (it != data.end()) {
                auto& matrix = it->second;
                int x = 0;
                int y = 0;
                for (int j = 0; j < MAP_HEIGHT_DEFAULT; j++) {
                    for (int k = 0; k < MAP_WIDTH_DEFAULT; k++) {
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
                            drawable->setTexture(texturePath, colorKey);
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
