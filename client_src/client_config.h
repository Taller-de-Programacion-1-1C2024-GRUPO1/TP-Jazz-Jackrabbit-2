#ifndef CLIENT_CONFIG_SINGLETON_H
#define CLIENT_CONFIG_SINGLETON_H

#include <filesystem>
#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>

class ClientConfigSingleton {
public:
    static ClientConfigSingleton& getInstance(const std::string& filePath = "") {
        static ClientConfigSingleton instance(filePath);
        return instance;
    }

    std::string getCharactersPath() const { return characters_path; }


    ClientConfigSingleton(ClientConfigSingleton const&) = delete;
    void operator=(ClientConfigSingleton const&) = delete;

    ~ClientConfigSingleton() {}

private:
    std::string file_path;

    explicit ClientConfigSingleton(const std::string& filePath): file_path(filePath) {
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
            characters_path = config["characters_path"].as<std::string>();

        } catch (const YAML::Exception& e) {
            std::cerr << "Error reading YAML file: " << e.what() << std::endl;
            std::cerr << "In column " << e.mark.column << " and line " << e.mark.line << std::endl;
        } catch (...) {
            std::cerr << "Something went wrong and an unknown exception was caught in the "
                         "ClientConfigSingleton"
                      << std::endl;
        }
    }
    // Game
    std::string characters_path;

};

#endif
