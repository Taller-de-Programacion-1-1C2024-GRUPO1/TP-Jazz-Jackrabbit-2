#include "client_drawable.h"

#include "client_shifting_drawable.h"

#include <fstream>

#include <yaml-cpp/yaml.h>

Drawable::Drawable(SDL2pp::Renderer& renderer, const std::string& path,
                    SDL2pp::Point& cp,
                    SDL2pp::Rect& textureRect, SDL2pp::Rect& onMapRect) :
        renderer(renderer), texture(renderer, SDL2pp::Surface(path)),
        cameraPosition(cp), textureRect(textureRect), onMapRect(onMapRect){}

SDL2pp::Rect Drawable::adjustPosition() {
    SDL2pp::Rect adjustedOnMapRect = onMapRect;
    adjustedOnMapRect.x -= cameraPosition.x;
    adjustedOnMapRect.y -= cameraPosition.y;
    return adjustedOnMapRect;
}

void Drawable::render() {
    renderer.Copy(texture, textureRect, adjustPosition());
}

void Drawable::update() {
    int mapWidth = 1120;
    int mapHeight = 608;

    // Ensure the camera doesn't go outside the map boundaries
    if (cameraPosition.x < 0) {
        cameraPosition.x = 0;
    } else if (cameraPosition.x + 800 > mapWidth) {
        cameraPosition.x = mapWidth - 800;
    }
    if (cameraPosition.y < 0) {
        cameraPosition.y = 0;
    } else if (cameraPosition.y + 600 > mapHeight) {
        cameraPosition.y = mapHeight - 600;
    }
}

void Drawable::setPosition(int x, int y) {
    onMapRect.x = x;
    onMapRect.y = y;
}

void Drawable::setCameraPosition(const SDL2pp::Point& position) {
    cameraPosition = position;
}

