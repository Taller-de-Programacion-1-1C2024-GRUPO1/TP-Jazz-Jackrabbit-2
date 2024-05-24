#include "character.h"
#include "physical_map.h"

Player::Player(int init_pos_x, int init_pos_y, PhysicalMap &map): 
Character(PLAYER_SIDE,PLAYER_SIDE,init_pos_x, init_pos_y,map,PLAYER_INITIAL_HEALTH),action(STAND), acc_y(GRAVITY){};


void Player::update(){
    spe_y += acc_y*DELTA_TIME;
    reset_map_colision_flags();
    map.check_colision_with_map(pos_x, pos_y, width, height,this);
    //CHEQUEO EVENTOS/////////////////////////////////////IMPLEMENTAR

    //DIRECCION
    if (spe_x > 0){
        direction = RIGHT;
    } else if (spe_x < 0){
        direction = LEFT;
    }

    //CAMBIO DE ACCION
    if (!on_floor && spe_y > 0){
        action = FALLING;
    }
    if (action == JUMPING && spe_x != 0){
        action = JUMP_FORWARD;
    }
    else if (action == FALLING && spe_x != 0){
        action = FALL_FORWARD;
    }
    else if (on_floor && spe_x == 0){
        action = STAND;
    }


    //ACTUALIZA POSICIONES
    pos_x += spe_x*DELTA_TIME;
    pos_y += spe_y*DELTA_TIME;
    //NO HAY INERCIA
    spe_x = 0;    
};

void Player::render(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = pos_x * 32;
    rect.y = pos_y * 32;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Color rojo
    SDL_RenderFillRect(renderer, &rect);
}

void Player::imprimir_posicion(){
    printf("X: %d Y: %d\n", pos_x, pos_y);
};


//COLISIONES CON MAPA
void Player::is_on_floor(){
    on_floor = true;
};

void Player::is_on_roof(){
    on_roof = true;
};

void Player::is_on_left_wall(){
    on_left_wall = true;
};

void Player::is_on_right_wall(){
    on_right_wall = true;
};

void Player::reset_map_colision_flags(){
    on_floor = false;
    on_roof = false;
    on_left_wall = false;
    on_right_wall = false;
};

//EVENTS
//JUMP
void Player::jump (){
    if (on_floor){
        action = JUMPING;
        spe_y = -JUMPING_INITIAL_SPEED;
    }
}
//RIGHT
void Player::run_right (){
    if (!on_right_wall){
        spe_x = PLAYER_SPEED;
    }
}

//RIGHT SPRINT
void Player::run_fast_right (){
    if (on_floor && !on_right_wall){
        action = RUN_FAST;
        spe_x = PLAYER_SPEED*2;
    }
}
//LEFT
void Player::run_left (){
    if(!on_left_wall){
        spe_x = -PLAYER_SPEED;
    }
}
//LEFT SPRINT
void Player::run_fast_left (){
    if(on_floor && !on_left_wall){
        action = RUN_FAST;
        spe_x = -(PLAYER_SPEED*2);
    }
}
//SHOOT
void Player::shoot (){
    action = SHOOT;
}
//SPECIAL ATTACK
void Player::special_attack (){
    action = SPECIAL_ATTACK;
}


Enemy::Enemy(int init_pos_x, int init_pos_y, PhysicalMap &map): 
    Character(/*ANCHO ENEMIGO*/PLAYER_SIDE,/*ALTO ENEMIGO*/PLAYER_SIDE,init_pos_x
    , init_pos_y,map,/*VIDA ENEMIGO*/PLAYER_INITIAL_HEALTH), acc_y(GRAVITY){};

//RENDER
void Enemy::render(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = pos_x * 32;
    rect.y = pos_y * 32;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Color verde
    SDL_RenderFillRect(renderer, &rect);
}