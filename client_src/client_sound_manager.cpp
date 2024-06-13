#include "client_sound_manager.h"

SoundManager::SoundManager():
        mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096),
        music(SOUND_MUSIC) {
    mixer.SetMusicVolume(MUSIC_VOLUME);
    mixer.PlayMusic(music, -1);
    mixer.SetVolume(-1, 3);
}

std::string SoundManager::getPathForSound(const std::string& name) {
    if (name == "Jazz-Auch") {
        return SOUND_AUCH;
    } else if (name == "Shooting") {
        return SOUND_SHOOTING;
    } else if (name == "Explosion") {
        return SOUND_EXPLOSION;
    } else {
        // Handle the case where the name does not match any known sound
        throw std::invalid_argument("Unknown sound name: " + name);
    }
}

void SoundManager::loadSoundEffect(const std::string& name) {
    soundEffects[name] = std::make_unique<SDL2pp::Chunk>(getPathForSound(name));
}

void SoundManager::playSoundEffect(const std::string& name) {
    mixer.PlayChannel(-1, *soundEffects[name]);
}

void SoundManager::stopSound() { mixer.HaltChannel(-1); }
