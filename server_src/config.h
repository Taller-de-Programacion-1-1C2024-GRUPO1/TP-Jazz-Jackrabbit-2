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
    int getPlayerStartingLife() const { return player_starting_life; }
    int getPlayerDamage() const { return player_damage; }
    int getEnemyReviveCooldown() const { return enemy_revive_cooldown; }
    int getEnemyTurtleSpeed() const { return enemy_turtle_speed; }
    int getEnemyTurtleDamage() const { return enemy_turtle_damage; }
    int getEnemyTurtleLife() const { return enemy_turtle_life; }
    int getEnemyTurtleAttackRange() const { return enemy_turtle_attack_range; }
    int getEnemyTurtleKillPoints() const { return enemy_turtle_kill_points; }
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
    int getEnemyKillPoints() const { return enemy_kill_points; }
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
            player_starting_life = config["player_starting_life"].as<int>();
            player_damage = config["player_damage"].as<int>();
            enemy_revive_cooldown = config["enemy_revive_cooldown"].as<int>();
            enemy_turtle_speed = config["enemy_turtle_speed"].as<int>();
            enemy_turtle_damage = config["enemy_turtle_damage"].as<int>();
            enemy_turtle_life = config["enemy_turtle_life"].as<int>();
            enemy_turtle_attack_range = config["enemy_turtle_attack_range"].as<int>();
            enemy_turtle_kill_points = config["enemy_turtle_kill_points"].as<int>();
            enemy_lizard_speed = config["enemy_lizard_speed"].as<int>();
            enemy_lizard_damage = config["enemy_lizard_damage"].as<int>();
            enemy_lizard_life = config["enemy_lizard_life"].as<int>();
            enemy_lizard_attack_range = config["enemy_lizard_attack_range"].as<int>();
            enemy_lizard_kill_points = config["enemy_lizard_kill_points"].as<int>();
            enemy_crab_speed = config["enemy_crab_speed"].as<int>();
            enemy_crab_damage = config["enemy_crab_damage"].as<int>();
            enemy_crab_life = config["enemy_crab_life"].as<int>();
            enemy_crab_attack_range = config["enemy_crab_attack_range"].as<int>();
            enemy_crab_kill_points = config["enemy_crab_kill_points"].as<int>();
            cant_health_carrot_life = config["cant_health_carrot_life"].as<int>();
            kill_rabbit_points = config["kill_rabbit_points"].as<int>();
            enemy_kill_points = config["enemy_kill_points"].as<int>();
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

    // Machine gun
    int machinegun_fire_cooldown;
    int machinegun_max_ammo;
    int machinegun_damage;
    int machinegun_range;
    int machinegun_bullet_speed;
    int machinegun_ammo_amount;

    // Sniper
    int sniper_fire_cooldown;
    int sniper_max_ammo;
    int sniper_damage;
    int sniper_range;
    int sniper_bullet_speed;
    int sniper_ammo_amount;

    // Players
    int player_starting_life;
    int player_damage;

    // Enemies
    int enemy_revive_cooldown;
    /*
     turtle:
        - speed
        - damage
        - life
        - attack_range
        - points
    */
    int enemy_turtle_speed;
    int enemy_turtle_damage;
    int enemy_turtle_life;
    int enemy_turtle_attack_range;
    int enemy_turtle_kill_points;

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
    int enemy_kill_points;
    int coin_points;
    int gem_points;
    int hot_dog_points;
    int hamburger_points;
};

#endif
