#include "client_sound_manager.h"

SoundManager::SoundManager():
        mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096),
        music("../client_src/resources/sounds/music.wav") {
    mixer.SetMusicVolume(5);
    mixer.PlayMusic(music, -1);
}

std::string SoundManager::getPathForSound(const std::string& name) {
    if (name == "Jazz-Auch") {
        return "../client_src/resources/sounds/auch.wav";
    } else if (name == "Shooting") {
        return "../client_src/resources/sounds/shooting.wav";
    } else if (name == "Explosion") {
        return "../client_src/resources/sounds/explosion.wav";
    }
}

void SoundManager::loadSoundEffect(const std::string& name) {
    soundEffects[name] = std::make_unique<SDL2pp::Chunk>(getPathForSound(name));
}

void SoundManager::playSoundEffect(const std::string& name) {
    mixer.PlayChannel(-1, *soundEffects[name]);
}

void SoundManager::stopSound() { mixer.HaltChannel(-1); }
