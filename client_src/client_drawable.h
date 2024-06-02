#ifndef CLIENT_DRAWABLE_H
#define CLIENT_DRAWABLE_H

#include <string>

#include <SDL2pp/SDL2pp.hh>

class Drawable {
protected:
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture texture;
    SDL2pp::Point& cameraPosition;

    // Guarda: (x,y,w,h) en el sprite de texturas
    SDL2pp::Rect textureRect;

    // Guarda: (x,y,w,h) en pantalla
    SDL2pp::Rect onMapRect;

    SDL2pp::Rect adjustPosition();

public:
    Drawable() = delete;
    Drawable(SDL2pp::Renderer& renderer, const std::string& path, SDL2pp::Point& cp,
             SDL2pp::Rect& textureRect, SDL2pp::Rect& onMapRect);
    Drawable(const Drawable& other) = delete;

    void render();
    void update();
    void setPosition(int x, int y);
    void setCameraPosition(const SDL2pp::Point& cameraPosition);
};

#endif  // CLIENT_DRAWABLE_H
