#ifndef CLIENT_TEXTURES_PROVIDER
#define CLIENT_TEXTURES_PROVIDER

#include <SDL2pp/SDL2pp.hh>

#include "client_constants.h"
#include <map>
#include <string>
#include <memory>

class TexturesProvider {
private:
    static std::map<std::string, std::shared_ptr<SDL2pp::Texture>> textures;
    TexturesProvider() = delete; // Prevent instantiation

public:
    static void init(SDL2pp::Renderer& renderer);
    static void loadTexture(SDL2pp::Renderer &renderer, const std::string &name, const std::string& path, SDL2pp::Color colorKey);
    static std::shared_ptr<SDL2pp::Texture> getTexture(const std::string &name);
};

#endif  // CLIENT_TEXTURES_PROVIDER