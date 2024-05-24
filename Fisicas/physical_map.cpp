#include "physical_map.h" 
#include "character.h"
void PhysicalMap::position_on_map(int &pos_x, int &pos_y){
    pos_x = pos_x/BLOCK_DIVISION;
    pos_y = pos_y/BLOCK_DIVISION;
};

void PhysicalMap::load_map(int* map){
    for(int i = 0; i < MAP_WIDTH; i++){
        for(int j = 0; j < MAP_HEIGHT; j++){
            phisicaMap[i][j] = map[i*MAP_HEIGHT+j];
        }
    }
};

void PhysicalMap::check_colision_with_map(int pos_x, int pos_y, int width, int height, Character* character){
    int x0 = trunc(pos_x/BLOCK_DIVISION);
    int y0 = trunc(pos_y/BLOCK_DIVISION);
    int x1 = trunc((pos_x+(width/2))/BLOCK_DIVISION);
    int y1 = trunc((pos_y+(height/2))/BLOCK_DIVISION);
    int x2 = trunc((pos_x+width)/BLOCK_DIVISION);
    int y2 = trunc((pos_y+height)/BLOCK_DIVISION);
};
