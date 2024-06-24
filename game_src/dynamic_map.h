#ifndef DYNAMIC_MAP_H
#define DYNAMIC_MAP_H

#include <map>
#include <vector>

class DynamicMap {

public:
    int width = MAP_WIDTH_DEFAULT;
    int height = MAP_HEIGHT_DEFAULT;
    std::map<int, std::vector<std::vector<int>>> map_data;
    explicit DynamicMap(int width, int height,
                        const std::map<int, std::vector<std::vector<int>>>& map_data):
            map_data(map_data) {}
    DynamicMap() = default;
};


#endif
