#ifndef CONFIG_SINGLETON_H
#define CONFIG_SINGLETON_H

#include <filesystem>
#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>

class ConfigSingleton {
public:
    static ConfigSingleton& getInstance(const std::string& filePath = "") {
        static ConfigSingleton instance(filePath);
        return instance;
    }

    int getMaxPlayers() const { return max_players; }
    int getStartingLife() const { return starting_life; }
    int getNullState() const { return null_state; }
    int getRabbitSpeed() const { return rabbit_speed; }
    int getRabbitRunSpeed() const { return rabbit_run_speed; }
    int getRabbitJumpSpeed() const { return rabbit_jump_speed; }
    int getRabbitJumpHeight() const { return rabbit_jump_height; }
    int getBlasterDamage() const { return blaster_damage; }
    int getBlasterSpeed() const { return blaster_speed; }
    bool getBlasterInfiniteAmmo() const { return blaster_infinite_ammo; }
    int getEnemyRatSpeed() const { return enemy_rat_speed; }
    int getEnemyRatDamage() const { return enemy_rat_damage; }
    int getEnemyRatLife() const { return enemy_rat_life; }
    int getEnemyRatAttackRange() const { return enemy_rat_attack_range; }
    int getEnemyRatKillPoints() const { return enemy_rat_kill_points; }
    int getEnemyLizardSpeed() const { return enemy_lizard_speed; }
    int getEnemyLizardDamage() const { return enemy_lizard_damage; }
    int getEnemyLizardLife() const { return enemy_lizard_life; }
    int getEnemyLizardAttackSpeed() const { return enemy_lizard_attack_range; }
    int getEnemyLizardKillPoints() const { return enemy_lizard_kill_points; }
    int getEnemyCrabSpeed() const { return enemy_crab_speed; }
    int getEnemyCrabDamage() const { return enemy_crab_damage; }
    int getEnemyCrabLife() const { return enemy_crab_life; }
    int getEnemyCrabAttackRange() const { return enemy_crab_attack_range; }
    int getEnemyCrabKillPoints() const { return enemy_crab_kill_points; }
    int getCantHealthCarrotLife() const { return cant_health_carrot_life; }
    int getKillRabbitPoints() const { return kill_rabbit_points; }
    int getCoinPoints() const { return coin_points; }
    int getGemPoints() const { return gem_points; }

    ConfigSingleton(ConfigSingleton const&) = delete;
    void operator=(ConfigSingleton const&) = delete;

    ~ConfigSingleton() {}

private:
    std::string file_path;

    explicit ConfigSingleton(const std::string& filePath): file_path(filePath) {
        readConfigFromFile();
    }

    void readConfigFromFile() {
        if (file_path.empty()) {
            throw std::runtime_error("Config file path is not set");
        }
        if (!std::filesystem::exists(file_path)) {
            throw std::runtime_error(
                    "Config file does not exist: " + file_path +
                    ". Please create it properly and pass the absolute path to it. E.g. "
                    "/etc/worms/config.yaml. See the README for more information.");
        }
        try {
            std::cout << "Reading config file..." << std::endl;
            YAML::Node config = YAML::LoadFile(file_path);
            max_players = config["max_players"].as<int>();
            starting_life = config["starting_life"].as<int>();
            null_state = config["null_state"].as<int>();
            rabbit_speed = config["rabbit_speed"].as<int>();
            rabbit_run_speed = config["rabbit_run_speed"].as<int>();
            rabbit_jump_speed = config["rabbit_jump_speed"].as<int>();
            rabbit_jump_height = config["rabbit_jump_height"].as<int>();
            blaster_damage = config["blaster_damage"].as<int>();
            blaster_speed = config["blaster_speed"].as<int>();
            blaster_infinite_ammo = config["blaster_infinite_ammo"].as<bool>();
            enemy_rat_speed = config["enemy_rat_speed"].as<int>();
            enemy_rat_damage = config["enemy_rat_damage"].as<int>();
            enemy_rat_life = config["enemy_rat_life"].as<int>();
            enemy_rat_attack_range = config["enemy_rat_attack_range"].as<int>();
            enemy_rat_kill_points = config["enemy_rat_kill_points"].as<int>();
            enemy_lizard_speed = config["enemy_lizard_speed"].as<int>();
            enemy_lizard_damage = config["enemy_lizard_damage"].as<int>();
            enemy_lizard_life = config["enemy_lizard_life"].as<int>();
            enemy_lizard_attack_range = config["enemy_lizard_attack_speed"].as<int>();
            enemy_lizard_kill_points = config["enemy_lizard_kill_points"].as<int>();
            enemy_crab_speed = config["enemy_crab_speed"].as<int>();
            enemy_crab_damage = config["enemy_crab_damage"].as<int>();
            enemy_crab_life = config["enemy_crab_life"].as<int>();
            enemy_crab_attack_range = config["enemy_crab_attack_range"].as<int>();
            enemy_crab_kill_points = config["enemy_crab_kill_points"].as<int>();
            cant_health_carrot_life = config["cant_health_carrot_life"].as<int>();
            kill_rabbit_points = config["kill_rabbit_points"].as<int>();
            coin_points = config["coin_points"].as<int>();
            gem_points = config["gem_points"].as<int>();
        } catch (const YAML::Exception& e) {
            std::cerr << "Error reading YAML file: " << e.what() << std::endl;
            std::cerr << "In column " << e.mark.column << " and line " << e.mark.line << std::endl;
        } catch (...) {
            std::cerr << "Something went wrong and an unknown exception was caught in the "
                         "ConfigSingleton"
                      << std::endl;
        }
    }
    // Game
    int max_players;

    // World
    int starting_life;
    int null_state;

    // Physics
    int rabbit_speed;
    int rabbit_run_speed;
    int rabbit_jump_speed;
    int rabbit_jump_height;

    // Weapons
    int blaster_damage;
    int blaster_speed;
    bool blaster_infinite_ammo;

    // Enemies
    /*
     RAT:
        - speed
        - damage
        - life
        - attack_range
        - points
    */
    int enemy_rat_speed;
    int enemy_rat_damage;
    int enemy_rat_life;
    int enemy_rat_attack_range;
    int enemy_rat_kill_points;

    /*
     LIZARD:
        - speed
        - damage
        - life
        - attack_range
        - points
    */
    int enemy_lizard_speed;
    int enemy_lizard_damage;
    int enemy_lizard_life;
    int enemy_lizard_attack_range;
    int enemy_lizard_kill_points;

    /*
     CRAB:
        - speed
        - damage
        - life
        - attack_range
        - points
    */
    int enemy_crab_speed;
    int enemy_crab_damage;
    int enemy_crab_life;
    int enemy_crab_attack_range;
    int enemy_crab_kill_points;

    // Health Items
    int cant_health_carrot_life;

    // Points
    int kill_rabbit_points;
    int coin_points;
    int gem_points;
};

#endif
