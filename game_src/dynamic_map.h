#ifndef DYNAMIC_MAP_H
#define DYNAMIC_MAP_H

#include <map>

class DynamicMap {

public:
    std::map<int, int[MAP_WIDTH_DEFAULT][MAP_HEIGHT_DEFAULT]> map_data;
    explicit DynamicMap(const std::map<int, int[MAP_WIDTH_DEFAULT][MAP_HEIGHT_DEFAULT]>& map_data):
            map_data(map_data) {}
    DynamicMap() = default;
    ~DynamicMap() = default;
};


#endif
