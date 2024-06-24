#ifndef CLIENT_DRAWABLE_H
#define CLIENT_DRAWABLE_H

#include <memory>
#include <string>

#include <SDL2pp/SDL2pp.hh>

class Drawable {
protected:
    SDL2pp::Renderer& renderer;
    std::shared_ptr<SDL2pp::Texture> texture;
    SDL2pp::Point& cameraPosition;

    // Guarda: (x,y,w,h) en el sprite de texturas
    SDL2pp::Rect textureRect;

    // Guarda: (x,y,w,h) en pantalla
    SDL2pp::Rect onMapRect;
    SDL2pp::Point position;

    SDL2pp::Point originalPosition;

    int mapWidth;
    int mapHeight;

public:
    Drawable() = delete;
    Drawable(SDL2pp::Renderer& renderer, SDL2pp::Point& cp, SDL2pp::Rect& textureRect,
             SDL2pp::Rect& onMapRect);
    Drawable(const Drawable& other) = delete;

    void setTexture(std::shared_ptr<SDL2pp::Texture> texture);
    void setSourceRect(const SDL2pp::Rect& rect);
    void render();
    void update();
    void setPosition(int x, int y);
    void resize(int w, int h);
};

#endif  // CLIENT_DRAWABLE_H
