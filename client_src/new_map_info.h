#ifndef NEWMAPINFO_H
#define NEWMAPINFO_H

#include <iostream>
#include <string>


struct NewMapInfo {
    std::string map_name;
    int width;
    int height;
    int texture;
    int max_players;

    // Constructor predeterminado que inicializa con valores nulos
    NewMapInfo(): map_name(""), width(-1), height(-1), texture(-1), max_players(-1) {}

    NewMapInfo(const std::string& name, int w, int h, int t, int max_p):
            map_name(name), width(w), height(h), texture(t), max_players(max_p) {}

    void printMapInfo() const {
        std::cout << "Map Name: " << map_name << "\n"
                  << "Width: " << width << "\n"
                  << "Height: " << height << "\n"
                  << "Texture: " << texture << "\n"
                  << "Max Players: " << max_players << std::endl;
    }
};

#endif
