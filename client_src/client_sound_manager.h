#ifndef CLIENT_SOUND_MANAGER_H
#define CLIENT_SOUND_MANAGER_H

#include <map>
#include <memory>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "client_constants.h"

class SoundManager {
private:
    SDL2pp::Mixer mixer;
    SDL2pp::Music music;
    std::unique_ptr<SDL2pp::Chunk> currentSound;

public:
    SoundManager();
    std::string getPathForSound(const std::string& name);
    void playSoundEffect(const std::string& name);
    void stopSound();
    ~SoundManager();
};

#endif  // CLIENT_SOUND_MANAGER_H
