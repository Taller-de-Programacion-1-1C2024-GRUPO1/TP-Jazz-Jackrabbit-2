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
    int getRabbitSpeed() const { return rabbit_speed; }
    int getRabbitJumpSpeed() const { return rabbit_jump_speed; }
    int getRabbitRevivalTime() const { return rabbit_revival_time; }
    int getRabbitDeintoxicateTime() const { return rabbit_desintoxicate_time; }
    int getBasicGunFireCooldown() const { return basic_gun_fire_cooldown; }
    int getBasicGunMaxAmmo() const { return basic_gun_max_ammo; }
    int getBasicGunDamage() const { return basic_gun_damage; }
    int getBasicGunRange() const { return basic_gun_range; }
    int getBasicGunBulletSpeed() const { return basic_gun_bullet_speed; }
    int getMachinegunFireCooldown() const { return machinegun_fire_cooldown; }
    int getMachinegunMaxAmmo() const { return machinegun_max_ammo; }
    int getMachinegunDamage() const { return machinegun_damage; }
    int getMachinegunRange() const { return machinegun_range; }
    int getMachinegunBulletSpeed() const { return machinegun_bullet_speed; }
    int getMachinegunAmmoAmount() const { return machinegun_ammo_amount; }
    int getSniperFireCooldown() const { return sniper_fire_cooldown; }
    int getSniperMaxAmmo() const { return sniper_max_ammo; }
    int getSniperDamage() const { return sniper_damage; }
    int getSniperRange() const { return sniper_range; }
    int getSniperBulletSpeed() const { return sniper_bullet_speed; }
    int getSniperAmmoAmount() const { return sniper_ammo_amount; }
    int getRaygunFireCooldown() const { return raygun_fire_cooldown; }
    int getRaygunMaxAmmo() const { return raygun_max_ammo; }
    int getRaygunDamage() const { return raygun_damage; }
    int getRaygunRange() const { return raygun_range; }
    int getRaygunBulletSpeed() const { return raygun_bullet_speed; }
    int getRaygunAmmoAmount() const { return raygun_ammo_amount; }
    int getPlayerStartingLife() const { return player_starting_life; }
    int getPlayerDamage() const { return player_damage; }
    int getEnemyTurtleLife() const { return enemy_turtle_life; }
    int getEnemyTurtleDamage() const { return enemy_turtle_damage; }
    int getEnemyTurtleKillPoints() const { return enemy_turtle_kill_points; }
    int getEnemyTurtleReviveSeconds() const { return enemy_turtle_revive_seconds; }
    int getEnemyTurtleDropAmount() const { return enemy_turtle_drop_amount; }
    int getEnemyLizardLife() const { return enemy_lizard_life; }
    int getEnemyLizardDamage() const { return enemy_lizard_damage; }
    int getEnemyLizardKillPoints() const { return enemy_lizard_kill_points; }
    int getEnemyLizardReviveSeconds() const { return enemy_lizard_revive_seconds; }
    int getEnemyLizardDropAmount() const { return enemy_lizard_drop_amount; }
    int getEnemyCrabLife() const { return enemy_crab_life; }
    int getEnemyCrabDamage() const { return enemy_crab_damage; }
    int getEnemyCrabKillPoints() const { return enemy_crab_kill_points; }
    int getEnemyCrabReviveSeconds() const { return enemy_crab_revive_seconds; }
    int getEnemyCrabDropAmount() const { return enemy_crab_drop_amount; }
    int getHotdogDropProbability() const { return hotdog_drop_probability; }
    int getHamburgerDropProbability() const { return hamburger_drop_probability; }
    int getHealthcarrotDropProbability() const { return healthcarrot_drop_probability; }
    int getCoinDropProbability() const { return coin_drop_probability; }
    int getGemDropProbability() const { return gem_drop_probability; }
    int getRottencheeseDropProbability() const { return rottencheese_drop_probability; }
    int getMachinegunammoDropProbability() const { return machinegunammo_drop_probability; }
    int getSniperammoDropProbability() const { return sniperammo_drop_probability; }
    int getRaygunammoDropProbability() const { return raygunammo_drop_probability; }
    int getNothingDropProbability() const { return nothing_drop_probability; }
    int getCantHealthCarrotLife() const { return cant_health_carrot_life; }
    int getKillRabbitPoints() const { return kill_rabbit_points; }
    int getCoinPoints() const { return coin_points; }
    int getGemPoints() const { return gem_points; }
    int getHotDogPoints() const { return hot_dog_points; }
    int getHamburgerPoints() const { return hamburger_points; }

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
            throw std::runtime_error("Config file does not exist: " + file_path);
        }
        try {
            std::cout << "Reading config file: " << file_path << std::endl;
            YAML::Node config = YAML::LoadFile(file_path);
            max_players = config["max_players"].as<int>();
            rabbit_speed = config["rabbit_speed"].as<int>();
            rabbit_jump_speed = config["rabbit_jump_speed"].as<int>();
            rabbit_revival_time = config["rabbit_revival_time"].as<int>();
            rabbit_desintoxicate_time = config["rabbit_desintoxicate_time"].as<int>();
            basic_gun_fire_cooldown = config["basic_gun_fire_cooldown"].as<int>();
            basic_gun_max_ammo = config["basic_gun_max_ammo"].as<int>();
            basic_gun_damage = config["basic_gun_damage"].as<int>();
            basic_gun_range = config["basic_gun_range"].as<int>();
            basic_gun_bullet_speed = config["basic_gun_bullet_speed"].as<int>();
            machinegun_fire_cooldown = config["machinegun_fire_cooldown"].as<int>();
            machinegun_max_ammo = config["machinegun_max_ammo"].as<int>();
            machinegun_damage = config["machinegun_damage"].as<int>();
            machinegun_range = config["machinegun_range"].as<int>();
            machinegun_bullet_speed = config["machinegun_bullet_speed"].as<int>();
            machinegun_ammo_amount = config["machinegun_ammo_amount"].as<int>();
            sniper_fire_cooldown = config["sniper_fire_cooldown"].as<int>();
            sniper_max_ammo = config["sniper_max_ammo"].as<int>();
            sniper_damage = config["sniper_damage"].as<int>();
            sniper_range = config["sniper_range"].as<int>();
            sniper_bullet_speed = config["sniper_bullet_speed"].as<int>();
            sniper_ammo_amount = config["sniper_ammo_amount"].as<int>();
            raygun_fire_cooldown = config["raygun_fire_cooldown"].as<int>();
            raygun_max_ammo = config["raygun_max_ammo"].as<int>();
            raygun_damage = config["raygun_damage"].as<int>();
            raygun_range = config["raygun_range"].as<int>();
            raygun_bullet_speed = config["raygun_bullet_speed"].as<int>();
            raygun_ammo_amount = config["raygun_ammo_amount"].as<int>();
            player_starting_life = config["player_starting_life"].as<int>();
            player_damage = config["player_damage"].as<int>();
            enemy_turtle_life = config["enemy_turtle_life"].as<int>();
            enemy_turtle_damage = config["enemy_turtle_damage"].as<int>();
            enemy_turtle_kill_points = config["enemy_turtle_kill_points"].as<int>();
            enemy_turtle_revive_seconds = config["enemy_turtle_revive_seconds"].as<int>();
            enemy_turtle_drop_amount = config["enemy_turtle_drop_amount"].as<int>();
            enemy_lizard_life = config["enemy_lizard_life"].as<int>();
            enemy_lizard_damage = config["enemy_lizard_damage"].as<int>();
            enemy_lizard_kill_points = config["enemy_lizard_kill_points"].as<int>();
            enemy_lizard_revive_seconds = config["enemy_lizard_revive_seconds"].as<int>();
            enemy_lizard_drop_amount = config["enemy_lizard_drop_amount"].as<int>();
            enemy_crab_life = config["enemy_crab_life"].as<int>();
            enemy_crab_damage = config["enemy_crab_damage"].as<int>();
            enemy_crab_kill_points = config["enemy_crab_kill_points"].as<int>();
            enemy_crab_revive_seconds = config["enemy_crab_revive_seconds"].as<int>();
            enemy_crab_drop_amount = config["enemy_crab_drop_amount"].as<int>();
            hotdog_drop_probability = config["hotdog_drop_probability"].as<int>();
            hamburger_drop_probability = config["hamburger_drop_probability"].as<int>();
            healthcarrot_drop_probability = config["healthcarrot_drop_probability"].as<int>();
            coin_drop_probability = config["coin_drop_probability"].as<int>();
            gem_drop_probability = config["gem_drop_probability"].as<int>();
            rottencheese_drop_probability = config["rottencheese_drop_probability"].as<int>();
            machinegunammo_drop_probability = config["machinegunammo_drop_probability"].as<int>();
            sniperammo_drop_probability = config["sniperammo_drop_probability"].as<int>();
            raygunammo_drop_probability = config["raygunammo_drop_probability"].as<int>();
            nothing_drop_probability = config["nothing_drop_probability"].as<int>();

            cant_health_carrot_life = config["cant_health_carrot_life"].as<int>();
            kill_rabbit_points = config["kill_rabbit_points"].as<int>();
            coin_points = config["coin_points"].as<int>();
            gem_points = config["gem_points"].as<int>();
            hot_dog_points = config["hot_dog_points"].as<int>();
            hamburger_points = config["hamburger_points"].as<int>();

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

    // Physics
    int rabbit_speed;
    int rabbit_jump_speed;
    int rabbit_revival_time;
    int rabbit_desintoxicate_time;


    // Basic gun
    int basic_gun_fire_cooldown;
    int basic_gun_max_ammo;
    int basic_gun_damage;
    int basic_gun_range;
    int basic_gun_bullet_speed;

    // Machine gun (Flamethrower)
    int machinegun_fire_cooldown;
    int machinegun_max_ammo;
    int machinegun_damage;
    int machinegun_range;
    int machinegun_bullet_speed;
    int machinegun_ammo_amount;

    // Sniper (Rocket Launcher)
    int sniper_fire_cooldown;
    int sniper_max_ammo;
    int sniper_damage;
    int sniper_range;
    int sniper_bullet_speed;
    int sniper_ammo_amount;

    // Raygun
    int raygun_fire_cooldown;
    int raygun_max_ammo;
    int raygun_damage;
    int raygun_range;
    int raygun_bullet_speed;
    int raygun_ammo_amount;

    // Players
    int player_starting_life;
    int player_damage;

    // Enemies
    int enemy_turtle_life;
    int enemy_turtle_damage;
    int enemy_turtle_kill_points;
    int enemy_turtle_revive_seconds;
    int enemy_turtle_drop_amount;

    int enemy_lizard_life;
    int enemy_lizard_damage;
    int enemy_lizard_kill_points;
    int enemy_lizard_revive_seconds;
    int enemy_lizard_drop_amount;

    int enemy_crab_life;
    int enemy_crab_damage;
    int enemy_crab_kill_points;
    int enemy_crab_revive_seconds;
    int enemy_crab_drop_amount;

    // Enemy drop probabilities
    
    int hotdog_drop_probability;
    int hamburger_drop_probability;
    int healthcarrot_drop_probability;
    int coin_drop_probability;
    int gem_drop_probability;
    int rottencheese_drop_probability;
    int machinegunammo_drop_probability;
    int sniperammo_drop_probability;
    int raygunammo_drop_probability;
    int nothing_drop_probability;

    // Health Items
    int cant_health_carrot_life;

    // Points
    int kill_rabbit_points;
    int coin_points;
    int gem_points;
    int hot_dog_points;
    int hamburger_points;
};

#endif
