#ifndef CLIENT_SOUND_MANAGER_H
#define CLIENT_SOUND_MANAGER_H

#include <map>
#include <memory>
#include <string>

#include <SDL2pp/SDL2pp.hh>

class SoundManager {
private:
    SDL2pp::Mixer mixer;
    SDL2pp::Music music;
    std::map<std::string, std::unique_ptr<SDL2pp::Chunk>> soundEffects;

public:
    SoundManager();
    std::string getPathForSound(const std::string& name);
    void loadSoundEffect(const std::string& name);
    void playSoundEffect(const std::string& name);
    void stopSound();
};

#endif  // CLIENT_SOUND_MANAGER_H
