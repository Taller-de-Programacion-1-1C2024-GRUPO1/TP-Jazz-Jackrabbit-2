#ifndef NEWMAPINFO_H
#define NEWMAPINFO_H

#include <iostream>
#include <string>

struct NewMapInfo {
    std::string map_name;
    int width;
    int height;
    int texture;

    // Constructor predeterminado que inicializa con valores nulos
    NewMapInfo(): map_name(""), width(-1), height(-1), texture(-1) {}

    NewMapInfo(const std::string& name, int w, int h, int t):
            map_name(name), width(w), height(h), texture(t) {}

    void printMapInfo() const {
        std::cout << "Map Name: " << map_name << "\n"
                  << "Width: " << width << "\n"
                  << "Height: " << height << "\n"
                  << "Texture: " << texture << std::endl;
    }
};

#endif
