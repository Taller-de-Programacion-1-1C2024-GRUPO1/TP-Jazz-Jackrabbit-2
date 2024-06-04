#include "gun.h"
#include "../map.h"
#include "rabbit.h"

Gun::Gun(int max_ammo, int damage, int range, int bullet_speed, Rabbit& owner, Map& manager): 
max_ammo(max_ammo), manager(manager), owner(owner),damage(damage), range(range), bullet_speed(bullet_speed){}

void Gun::update(){
    if (fire_cooldown > 0){
        fire_cooldown--;
    }
}

bool Gun::can_fire() {
    return fire_cooldown == 0 && has_ammo();
}

void Gun::add_ammo(int amount_ammo){
    ammo += amount_ammo;
    if (ammo > max_ammo){
        ammo = max_ammo;
    }
}

BasicGun::BasicGun(Rabbit& owner, Map& manager): Gun(BASIC_GUN_MAX_AMMO, BASIC_GUN_DAMAGE, BASIC_GUN_RANGE, BASIC_GUN_BULLET_SPEED, owner, manager){
    add_ammo(BASIC_GUN_MAX_AMMO);
}

bool BasicGun::has_ammo() {return true;}

void BasicGun::fire(int pos_x, int pos_y, int direction){
    if (can_fire()){
        manager.add_bullet(new Bullet(pos_x, pos_y, direction * bullet_speed, damage, owner));
        fire_cooldown = BASIC_GUN_FIRE_COOLDOWN;
    }
}

MachineGun::MachineGun(Rabbit& owner, Map& manager): Gun(MACHINEGUN_MAX_AMMO, MACHINEGUN_DAMAGE, MACHINEGUN_RANGE, MACHINEGUN_BULLET_SPEED, owner, manager){}

bool MachineGun::has_ammo() {return ammo > 0;}

void MachineGun::fire(int pos_x, int pos_y, int direction){
    if (can_fire()){
        manager.add_bullet(new Bullet(pos_x, pos_y, direction * bullet_speed, damage, owner));
        fire_cooldown = MACHINEGUN_FIRE_COOLDOWN;
    }
}

Sniper::Sniper(Rabbit& owner, Map& manager): Gun(SNIPER_MAX_AMMO, SNIPER_DAMAGE, SNIPER_RANGE, SNIPER_BULLET_SPEED, owner, manager){}

bool Sniper::has_ammo() {return ammo > 0;}

void Sniper::fire(int pos_x, int pos_y, int direction){
    if (can_fire()){
        manager.add_bullet(new Bullet(pos_x, pos_y, direction * bullet_speed, damage, owner));
        fire_cooldown = SNIPER_FIRE_COOLDOWN;
    }
}
