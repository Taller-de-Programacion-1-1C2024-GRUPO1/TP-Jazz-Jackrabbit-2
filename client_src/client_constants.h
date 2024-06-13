#ifndef CLIENT_CONSTANTS_H
#define CLIENT_CONSTANTS_H

#include <string>
#include "client_config.h"

#define CLOSE_MAP_CREATOR -3

enum /*Map Textures*/ {
    CASTLE = 0,
    CARROTUS
};

// Music & Game Constants
#define MUSIC_VOLUME 5
#define GAME_TITLE "Jack Jazzrabbit 2"

// Paths

#define BASE_PATH ClientConfigSingleton::getInstance().getBasePath() 

#define RESOURCES_PATH ClientConfigSingleton::getInstance().getResourcesPath()

#define BACKGROUND_PATH ClientConfigSingleton::getInstance().getBackgroundPath()

#define CHARACTERS_PATH ClientConfigSingleton::getInstance().getCharactersPath()

#define ENEMIES_PATH ClientConfigSingleton::getInstance().getEnemiesPath()

#define FONTS_PATH ClientConfigSingleton::getInstance().getFontPath()

#define MAPS_PATH ClientConfigSingleton::getInstance().getMapsPath()

#define PROJECTILES_PATH ClientConfigSingleton::getInstance().getProjectilesPath()

#define SOUNDS_PATH ClientConfigSingleton::getInstance().getSoundsPath()

#define TILES_PATH ClientConfigSingleton::getInstance().getTilesPath()

#define ITEMS_PATH ClientConfigSingleton::getInstance().getItemsPath()

#define ANIMATIONS_PATH ClientConfigSingleton::getInstance().getAnimationsPath()

#define PROJECTILES_ANIMATIONS_PATH ClientConfigSingleton::getInstance().getProjectilesAnimationsPath()

#define VALUABLES_ANIMATIONS_PATH ClientConfigSingleton::getInstance().getValuablesAnimationsPath()

// Backgrounds

#define FONDO_PNG BACKGROUND_PATH + "/fondo.png"
#define LOBBY_PNG BACKGROUND_PATH + "/lobby.png"
#define MATCH_LOBBY_PNG BACKGROUND_PATH + "/match_lobby.png"

// Characters

#define JAZZ_CHARACTER_PNG CHARACTERS_PATH + "/jazz_character.png"
#define JAZZ_IMG CHARACTERS_PATH + "/Jazz.png"
#define LORI_CHARACTER_PNG CHARACTERS_PATH + "/lori_character.png"
#define LORI_IMG CHARACTERS_PATH + "/Lori.png"
#define SPAZ_CHARACTER_PNG CHARACTERS_PATH + "/spaz_character.png"
#define SPAZ_IMG CHARACTERS_PATH + "/Spaz.png"

// Enemies

#define ENEMIES_PNG ENEMIES_PATH + "/Enemies.png"
#define TURTLE_PNG ENEMIES_PATH + "/turtle.png"

// Fonts

#define FONT_TTF_04B_30 FONTS_PATH + "/04B_30__.ttf"
#define FONTS_PNG FONTS_PATH + "/Fonts.png"
#define FONT_JJ2 FONTS_PATH + "/Jazz_Jackrabbit_2.ttf"

// Items

#define ITEMS_PNG ITEMS_PATH + "/items.png"

// Maps

#define CARROTUS_MAP MAPS_PATH + "/carrotus.png"
#define CASTLE_MAP MAPS_PATH + "/castle.png"
#define CREATE_A_MAP MAPS_PATH + "/create_a_map.png"

// Projectiles

#define PROJECTILES_PNG PROJECTILES_PATH + "/Projectiles.png"

// Sounds

#define SOUND_AUCH SOUNDS_PATH + "/auch.wav"
#define SOUND_DASHING SOUNDS_PATH + "/dashing.wav"
#define SOUND_EXPLOSION SOUNDS_PATH + "/explosion.wav"
#define SOUND_MUSIC SOUNDS_PATH + "/music.wav"
#define SOUND_SHOOTING SOUNDS_PATH + "/shooting.wav"

// Tiles

#define CARROTUS_TILES_PNG TILES_PATH + "/carrotus.png"
#define CASTLE_TILES_PNG TILES_PATH + "/castle.png"

// Animations

#define JAZZ_ANIMATIONS ANIMATIONS_PATH + "/jazz.yml"
#define LORI_ANIMATIONS ANIMATIONS_PATH + "/lori.yml"
#define SPAZ_ANIMATIONS ANIMATIONS_PATH + "/spaz.yml"
#define TURTLE_ANIMATIONS ANIMATIONS_PATH + "/turtle.yml"
#define CRAB_ANIMATIONS ANIMATIONS_PATH + "/crab.yml"
#define LIZARD_ANIMATIONS ANIMATIONS_PATH + "/lizard.yml"

// Projectiles Animations

#define BLUE_RAY_ANIMATIONS PROJECTILES_ANIMATIONS_PATH + "/blue_ray.yml"
#define REGULAR_ANIMATIONS PROJECTILES_ANIMATIONS_PATH + "/regular.yml"

// Valuables Animations

#define COIN_ANIMATIONS VALUABLES_ANIMATIONS_PATH + "/coin.yml"
#define GEM_ANIMATIONS VALUABLES_ANIMATIONS_PATH + "/gem.yml"

#endif
