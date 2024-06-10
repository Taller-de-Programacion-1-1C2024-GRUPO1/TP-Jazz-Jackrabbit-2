#include "gun.h"

#include "../map.h"

#include "rabbit.h"

Gun::Gun(int max_ammo, int damage, int range, int bullet_speed, Rabbit& owner, Map& manager):
        ammo(0),
        max_ammo(max_ammo),
        manager(manager),
        owner(owner),
        damage(damage),
        fire_cooldown(0),
        range(range),
        bullet_speed(bullet_speed) {}

void Gun::update() {
    if (fire_cooldown > 0) {
        fire_cooldown--;
    }
}

void Gun::add_bullet_to_map(int pos_x, int pos_y, int direction, int type, int cooldown) {
    int direction_variable = 0;
    if (direction == LEFT) {
        direction_variable = -1;
    } else if (direction == RIGHT) {
        direction_variable = 1;
    }
    manager.add_bullet(new Bullet(manager.get_projectile_id(), type, pos_x, pos_y,
                                  direction_variable * bullet_speed, damage, owner));
    fire_cooldown = cooldown;
    owner.set_action_shoot();
}

int Gun::get_ammo() { return ammo; }

bool Gun::can_fire() { return fire_cooldown == 0 && has_ammo(); }

void Gun::add_ammo(int amount_ammo) {
    ammo += amount_ammo;
    if (ammo > max_ammo) {
        ammo = max_ammo;
    }
}

BasicGun::BasicGun(Rabbit& owner, Map& manager):
        Gun(BASIC_GUN_MAX_AMMO, BASIC_GUN_DAMAGE, BASIC_GUN_RANGE, BASIC_GUN_BULLET_SPEED, owner,
            manager) {
    add_ammo(BASIC_GUN_MAX_AMMO);
}

bool BasicGun::has_ammo() { return true; }

void BasicGun::fire(int pos_x, int pos_y, int direction) {
    if (can_fire()) {
        Gun::add_bullet_to_map(pos_x, pos_y, direction, BASIC_GUN, BASIC_GUN_FIRE_COOLDOWN);
    }
}

MachineGun::MachineGun(Rabbit& owner, Map& manager):
        Gun(MACHINEGUN_MAX_AMMO, MACHINEGUN_DAMAGE, MACHINEGUN_RANGE, MACHINEGUN_BULLET_SPEED,
            owner, manager) {}

bool MachineGun::has_ammo() { return ammo > 0; }

void MachineGun::fire(int pos_x, int pos_y, int direction) {
    if (can_fire()) {
        Gun::add_bullet_to_map(pos_x, pos_y, direction, MACHINE_GUN, MACHINEGUN_FIRE_COOLDOWN);
        ammo--;
    }
}

Sniper::Sniper(Rabbit& owner, Map& manager):
        Gun(SNIPER_MAX_AMMO, SNIPER_DAMAGE, SNIPER_RANGE, SNIPER_BULLET_SPEED, owner, manager) {}

bool Sniper::has_ammo() { return ammo > 0; }

void Sniper::fire(int pos_x, int pos_y, int direction) {
    if (can_fire()) {
        Gun::add_bullet_to_map(pos_x, pos_y, direction, SNIPER, SNIPER_FIRE_COOLDOWN);
        ammo--;
    }
}
