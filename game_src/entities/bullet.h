#ifndef BULLET_H
#define BULLET_H

#include "../../physics_src/physical_objects.h"

class Bullet: public PhysicalObject {
private:
    const int damage;

public:
    Bullet(int init_pos_x, int init_pos_y, int bullet_speed, int damage);

    void update();

    /*

    -->>> Directamente podríamos chequearlo con el objeto base
    void check_colision(Character& character);


    -->>> aca estarías especificando para cada uno de los objetos que colisiona con el bullet.
    -->>> No es necesario, ya que el objeto base ya tiene la función check_colision (creo)

    void check_colision (Player& player){
        player.check_colision_with_bullet(pos_x, pos_y, width, height, damage);
    };

    void check_colision (Enemy& enemy){
        enemy.check_colision_with_bullet(pos_x, pos_y, width, height, damage);
    };

    */
};

#endif
