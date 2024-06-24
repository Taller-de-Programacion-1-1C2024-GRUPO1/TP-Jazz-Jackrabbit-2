#ifndef CLIENT_CONSTANTS_H
#define CLIENT_CONSTANTS_H

#include <string>

#include "client_config.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define CLOSE_MAP_CREATOR -3
#define PLAY_MAP -4
#define EDIT_MAP -5

enum /*Map Textures*/ { JUNGLE = 0, CARROTUS };

// Map editor constants

enum Tool { PAINT, ERASE, MOVE };
enum Mode { TEXTURE, ENTITY };

// Destination for new maps
#define DEST_PATH "../external/maps/"

#define EDITOR_SCREEN_WIDTH 1280
#define EDITOR_SCREEN_HEIGHT 700
#define BUTTON_WIDTH 80
#define BUTTON_HEIGHT 40
#define BUTTONS_AREA_HEIGHT 60
#define TEXTURE_GRID 320
#define SPACE_BEFORE_DRAWABLE_GRID 380
#define SCROLL_SPEED 10
#define TILE_WIDTH 10
#define TILE_HEIGHT 66
#define TEXTURE_LAYERS 5

#define BUTTON_POS_Y 10
#define BUTTON_END_Y 50
#define SAVE_BUTTON_POS_X 1200
#define TILE_BUTTON_POS_X 890
#define ENTITY_BUTTON_POS_X 980
#define PAINT_BUTTON_POS_X 10
#define ERASE_BUTTON_POS_X 100
#define MOVE_BUTTON_POS_X 190
#define BACKGROUND_BUTTON_POS_X 370
#define DIAG_LEFT_BUTTON_POS_X 460
#define DIAG_RIGHT_BUTTON_POS_X 550
#define COLLIDER_BUTTON_POS_X 640
#define DECORATION_BUTTON_POS_X 730

// Music & Game Constants

#define MUSIC_VOLUME ClientConfigSingleton::getInstance().getMusicVolume()
#define GAME_TITLE "Jack Jazzrabbit 2"

// Paths

#define BASE_PATH ClientConfigSingleton::getInstance().getBasePath()

#define MAPS_TEXTURES_PATH ClientConfigSingleton::getInstance().getMapsPath()

#define RESOURCES_PATH ClientConfigSingleton::getInstance().getResourcesPath()

#define BACKGROUND_PATH ClientConfigSingleton::getInstance().getBackgroundPath()

#define CHARACTERS_PATH ClientConfigSingleton::getInstance().getCharactersPath()

#define ENEMIES_PATH ClientConfigSingleton::getInstance().getEnemiesPath()

#define FONTS_PATH ClientConfigSingleton::getInstance().getFontPath()

#define PROJECTILES_PATH ClientConfigSingleton::getInstance().getProjectilesPath()

#define SOUNDS_PATH ClientConfigSingleton::getInstance().getSoundsPath()

#define TILES_PATH ClientConfigSingleton::getInstance().getTilesPath()

#define ITEMS_PATH ClientConfigSingleton::getInstance().getItemsPath()

#define ANIMATIONS_PATH ClientConfigSingleton::getInstance().getAnimationsPath()

#define AMMO_ANIMATIONS_PATH ClientConfigSingleton::getInstance().getAmmoAnimationsPath()

#define PROJECTILES_ANIMATIONS_PATH \
    ClientConfigSingleton::getInstance().getProjectilesAnimationsPath()

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
#define JUNGLE_MAP MAPS_PATH + "/jungle.png"
#define CREATE_A_MAP MAPS_PATH + "/create_a_map.png"

// Projectiles

#define PROJECTILES_PNG PROJECTILES_PATH + "/Projectiles.png"

// Sounds

#define SOUND_AUCH SOUNDS_PATH + "/auch.wav"
#define SOUND_DASHING SOUNDS_PATH + "/dashing.wav"
#define SOUND_EXPLOSION SOUNDS_PATH + "/explosion.wav"
#define SOUND_MUSIC SOUNDS_PATH + "/music.wav"
#define SOUND_SHOOTING SOUNDS_PATH + "/shooting.wav"
#define SOUND_COIN_PICKUP SOUNDS_PATH + "/coin-pickup.wav"
#define SOUND_AMMO_PICKUP SOUNDS_PATH + "/ammo-pickup.wav"
#define SOUND_EATING SOUNDS_PATH + "/eating.wav"

// Tiles

#define CARROTUS_TILES_PNG TILES_PATH + "/carrotus.png"
#define JUNGLE_TILES_PNG TILES_PATH + "/jungle.png"

// Animations

#define JAZZ_ANIMATIONS ANIMATIONS_PATH + "/jazz.yml"
#define LORI_ANIMATIONS ANIMATIONS_PATH + "/lori.yml"
#define SPAZ_ANIMATIONS ANIMATIONS_PATH + "/spaz.yml"
#define TURTLE_ANIMATIONS ANIMATIONS_PATH + "/turtle.yml"
#define CRAB_ANIMATIONS ANIMATIONS_PATH + "/crab.yml"
#define LIZARD_ANIMATIONS ANIMATIONS_PATH + "/lizard.yml"

// Ammo Animations

#define MACHINE_GUN_ANIMATIONS AMMO_ANIMATIONS_PATH + "/machine_gun.yml"
#define SNIPER_ANIMATIONS AMMO_ANIMATIONS_PATH + "/sniper.yml"
#define RAY_GUN_ANIMATIONS AMMO_ANIMATIONS_PATH + "/ray_gun.yml"
#define ROCKET_LAUCHER_ANIMATIONS AMMO_ANIMATIONS_PATH + "/rocket_launcher.yml"

// Projectiles Animations

#define BLUE_RAY_ANIMATIONS PROJECTILES_ANIMATIONS_PATH + "/blue_ray.yml"
#define REGULAR_ANIMATIONS PROJECTILES_ANIMATIONS_PATH + "/regular.yml"
#define ROCKET_ANIMATIONS PROJECTILES_ANIMATIONS_PATH + "/rocket.yml"
#define RAY_ANIMATIONS PROJECTILES_ANIMATIONS_PATH + "/ray.yml"

// Valuables Animations

#define COIN_ANIMATIONS VALUABLES_ANIMATIONS_PATH + "/coin.yml"
#define GEM_ANIMATIONS VALUABLES_ANIMATIONS_PATH + "/gem.yml"

#endif
