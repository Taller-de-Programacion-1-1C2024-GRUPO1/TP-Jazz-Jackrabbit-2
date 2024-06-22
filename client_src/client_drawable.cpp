#include "client_drawable.h"

#include <fstream>
#include <memory>

#include <yaml-cpp/yaml.h>

#include "client_shifting_drawable.h"

Drawable::Drawable(SDL2pp::Renderer& renderer, SDL2pp::Point& cp, SDL2pp::Rect& textureRect,
                   SDL2pp::Rect& onMapRect):
        renderer(renderer),
        texture(nullptr),
        cameraPosition(cp),
        textureRect(textureRect),
        onMapRect(onMapRect),
        position(onMapRect.x, onMapRect.y),
        mapWidth(1120),
        mapHeight(608) {}

void Drawable::setTexture(std::shared_ptr<SDL2pp::Texture> texture) { this->texture = texture; }

void Drawable::setSourceRect(const SDL2pp::Rect& rect) { textureRect = rect; }

void Drawable::update() {
    onMapRect.x = position.x - cameraPosition.x;
    onMapRect.y = position.y - cameraPosition.y;
}

void Drawable::render() { renderer.Copy(*texture, textureRect, onMapRect); }

void Drawable::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void Drawable::resize(int w, int h) {
    onMapRect.w = w;
    onMapRect.h = h;
}
