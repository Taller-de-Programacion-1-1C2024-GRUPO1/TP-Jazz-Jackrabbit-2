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

    std::vector<std::unique_ptr<Drawable>> loadMap(const std::string& filename,
                                                   const std::string& texturePath,
                                                   SDL2pp::Point& cameraPosition) {
        YAML::Node map = YAML::LoadFile(filename);
        std::vector<std::unique_ptr<Drawable>> tiles;

        for (const auto& layerNode: map["layers"]) {
            int x = 0;
            int y = 0;
            for (const auto& row: layerNode["data"]) {
                for (const auto& block: row) {
                    int id = block.as<int>();
                    if (id != -1) {  // Ignore empty tiles, but they count in the iteration

                        // Calculate srcRect based on the texture id
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

                        tiles.push_back(std::move(std::unique_ptr<Drawable>(new Drawable(
                                renderer, texturePath, cameraPosition, srcRect, destRect))));
                    }
                    x++;
                }
                x = 0;
                y++;
            }
        }

        return tiles;
    }
};

#endif  // CLIENT_MAP_LOADER_H
