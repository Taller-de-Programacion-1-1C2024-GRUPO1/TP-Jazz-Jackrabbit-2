#ifndef DYNAMIC_MAP_H
#define DYNAMIC_MAP_H

class DynamicMap {

    std::unordered_map<int, int[MAP_WIDTH_DEFAULT][MAP_HEIGHT_DEFAULT]> map_data;

public:

    explicit DynamicMap(const std::unordered_map<int, int[MAP_WIDTH_DEFAULT][MAP_HEIGHT_DEFAULT]>& map_data) : map_data(map_data) {}
    DynamicMap() = default;
    ~DynamicMap() = default;

};


#endif
