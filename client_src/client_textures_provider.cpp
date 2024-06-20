#include "client_textures_provider.h"

std::map<std::string, std::shared_ptr<SDL2pp::Texture>> TexturesProvider::textures;

void TexturesProvider::init(SDL2pp::Renderer& renderer) {
    SDL2pp::Color characterColor = {44, 102, 150, 255};
    loadTexture(renderer, "Jazz", JAZZ_IMG, characterColor);
    loadTexture(renderer, "Spaz", SPAZ_IMG, characterColor);
    loadTexture(renderer, "Lori", LORI_IMG, characterColor);

    SDL2pp::Color elseColor = {0, 128, 255, 1};  // enemies, items, projectiles, etc
    loadTexture(renderer, "Enemies", ENEMIES_PNG, elseColor);
    loadTexture(renderer, "Turtle", TURTLE_PNG, elseColor);
    loadTexture(renderer, "Items", ITEMS_PNG, elseColor);
    loadTexture(renderer, "Projectiles", PROJECTILES_PNG, elseColor);
    loadTexture(renderer, "Font", FONTS_PNG, elseColor);

    SDL2pp::Color mapColor = {87, 0, 203, 0};
    loadTexture(renderer, "Carrotus", CARROTUS_TILES_PNG, mapColor);
    loadTexture(renderer, "Jungle", JUNGLE_TILES_PNG, mapColor);
}

void TexturesProvider::loadTexture(SDL2pp::Renderer& renderer, const std::string& name,
                                   const std::string& path, SDL2pp::Color colorKey) {
    SDL2pp::Surface surface(path);
    Uint32 mappedColorKey = SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b);
    SDL_SetColorKey(surface.Get(), SDL_TRUE, mappedColorKey);
    textures[name] = std::make_shared<SDL2pp::Texture>(renderer, surface);
}

std::shared_ptr<SDL2pp::Texture> TexturesProvider::getTexture(const std::string& name) {
    return textures[name];
}
