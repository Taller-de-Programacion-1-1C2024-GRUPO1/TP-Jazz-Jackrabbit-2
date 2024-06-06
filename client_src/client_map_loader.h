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
        const auto& data = map.map_data;  // Use const reference to avoid copying the map
        std::cout << "DATA SIZE: " << data.size() << std::endl;
        for (int key = 0; key <= 4; key++) {
            auto it = data.find(key);  // Use find to check if key exists in the map
            if (it != data.end()) {  // Key exists in the map
                std::cout << "Reading layer " << key << std::endl;
                auto& matrix = it->second;  // Use iterator to access the value associated with the key
                int x = 0;
                int y = 0;
                for (int j = 0; j < MAP_HEIGHT_DEFAULT; j++) {
                    for (int k = 0; k < MAP_WIDTH_DEFAULT; k++) {
                        int id = matrix[k][j];
                        if (id != 65535) {  // Ignore empty tiles, but they count in the iteration
                            // Calculate srcRect based on the texture id
                            std::cout << "ID: " << id << std::endl;
                            SDL2pp::Rect srcRect;
                            srcRect.x = (id % TILE_WIDTH) * 32;
                            srcRect.y = (id / TILE_WIDTH) * 32;
                            srcRect.w = BLOCK_SIZE;
                            srcRect.h = BLOCK_SIZE;

                            // Calculate destRect based on the position in the layer
                            SDL2pp::Rect destRect;
                            destRect.x = x * BLOCK_SIZE;
                            destRect.y = y * BLOCK_SIZE;
                            destRect.w = BLOCK_SIZE;
                            destRect.h = BLOCK_SIZE;

                            tiles.push_back(std::make_unique<Drawable>(
                                    renderer, texturePath, colorKey, cameraPosition,
                                    srcRect, destRect));
                        }
                        x++;
                    }
                    x = 0;
                    y++;
                }
            }
            else{
                std::cout << "Layer " << key << " not found" << std::endl;
            }
        }

        return tiles;
    }
};

#endif  // CLIENT_MAP_LOADER_H
