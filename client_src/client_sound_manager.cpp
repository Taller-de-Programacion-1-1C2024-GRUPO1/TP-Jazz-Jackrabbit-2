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
    } else if (name == "Coin-Pickup") {
        return SOUND_COIN_PICKUP;
    } else if (name == "Ammo-Pickup") {
        return SOUND_AMMO_PICKUP;
    } else if (name == "Eating") {
        return SOUND_EATING;
    } else {
        throw std::invalid_argument("Unknown sound name: " + name);
    }
}

void SoundManager::playSoundEffect(const std::string& name) {
    currentSound = std::make_unique<SDL2pp::Chunk>(getPathForSound(name));
    try {
        mixer.PlayChannel(-1, *currentSound);
    } catch (const SDL2pp::Exception& e) {
        std::cerr << "All channels are busy" << std::endl;
    }
}

void SoundManager::stopSound() { mixer.HaltChannel(-1); }

SoundManager::~SoundManager() {
    mixer.HaltMusic();
    mixer.HaltChannel(-1);
}
