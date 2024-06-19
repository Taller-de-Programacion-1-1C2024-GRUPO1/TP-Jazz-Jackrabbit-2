#ifndef CLIENT_CONFIG_SINGLETON_H
#define CLIENT_CONFIG_SINGLETON_H

#include <filesystem>
#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>

class ClientConfigSingleton {
public:
    static ClientConfigSingleton& getInstance(const std::string& file_config_path = "") {
        static ClientConfigSingleton instance(file_config_path);
        return instance;
    }

    std::string getBasePath() const { return base_path; }
    std::string getResourcesPath() const { return resources_path; }
    std::string getBackgroundPath() const { return background_path; }
    std::string getCharactersPath() const { return characters_path; }
    std::string getEnemiesPath() const { return enemies_path; }
    std::string getFontPath() const { return font_path; }
    std::string getTexturesMapsPath() const { return maps_textures_path; }
    std::string getProjectilesPath() const { return projectiles_path; }
    std::string getSoundsPath() const { return sounds_path; }
    std::string getTilesPath() const { return tiles_path; }
    std::string getItemsPath() const { return items_path; }
    std::string getAnimationsPath() const { return animations_path; }
    std::string getAmmoAnimationsPath() const { return ammo_animations_path; }
    std::string getProjectilesAnimationsPath() const { return projectiles_animations_path; }
    std::string getValuablesAnimationsPath() const { return valuables_animations_path; }
    int getMusicVolume() const { return music_volume; }

    ClientConfigSingleton(ClientConfigSingleton const&) = delete;
    void operator=(ClientConfigSingleton const&) = delete;

    ~ClientConfigSingleton() {}

private:
    std::string file_config_path;

    explicit ClientConfigSingleton(const std::string& file_config_path):
            file_config_path(file_config_path) {
        readConfigFromFile();
    }

    void readConfigFromFile() {
        if (file_config_path.empty()) {
            throw std::runtime_error("Config file path is not set");
        }
        if (!std::filesystem::exists(file_config_path)) {
            throw std::runtime_error("Config file does not exist: " + file_config_path);
        }
        try {
            std::cout << "Reading client config file: " << file_config_path << std::endl;
            YAML::Node config = YAML::LoadFile(file_config_path);
            base_path = config["base_path"].as<std::string>();
            resources_path = config["resources_path"].as<std::string>();
            background_path = config["background_path"].as<std::string>();
            characters_path = config["characters_path"].as<std::string>();
            enemies_path = config["enemies_path"].as<std::string>();
            font_path = config["fonts_path"].as<std::string>();
            maps_textures_path = config["maps_textures_path"].as<std::string>();
            projectiles_path = config["projectiles_path"].as<std::string>();
            sounds_path = config["sounds_path"].as<std::string>();
            tiles_path = config["tiles_path"].as<std::string>();
            items_path = config["items_path"].as<std::string>();
            animations_path = config["animations_path"].as<std::string>();
            ammo_animations_path = config["ammo_animations_path"].as<std::string>();
            projectiles_animations_path = config["projectiles_animations_path"].as<std::string>();
            valuables_animations_path = config["valuables_animations_path"].as<std::string>();
            music_volume = config["music_volume"].as<int>();

        } catch (const YAML::Exception& e) {
            std::cerr << "Error reading YAML file: " << e.what() << std::endl;
            std::cerr << "In column " << e.mark.column << " and line " << e.mark.line << std::endl;
        } catch (...) {
            std::cerr << "Something went wrong and an unknown exception was caught in the "
                         "ClientConfigSingleton"
                      << std::endl;
        }
    }
    // Game paths
    std::string base_path;
    std::string resources_path;
    std::string background_path;
    std::string characters_path;
    std::string enemies_path;
    std::string font_path;
    std::string maps_textures_path;
    std::string projectiles_path;
    std::string sounds_path;
    std::string tiles_path;
    std::string items_path;
    std::string animations_path;
    std::string ammo_animations_path;
    std::string projectiles_animations_path;
    std::string valuables_animations_path;
    int music_volume;
};

#endif
