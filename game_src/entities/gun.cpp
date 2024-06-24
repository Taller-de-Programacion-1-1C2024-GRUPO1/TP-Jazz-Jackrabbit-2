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
        owner.set_action_shoot();
    }
}

void Gun::execute_max_ammo() { ammo = max_ammo; }

void Gun::add_bullet_to_map(int pos_x, int pos_y, int direction, int type, int cooldown) {
    int direction_variable = 0;
    if (direction == LEFT) {
        direction_variable = -1;
    } else if (direction == RIGHT) {
        direction_variable = 1;
    }
    manager.add_bullet(new Bullet(
            manager.get_projectile_id(), type, pos_x - (direction_variable * (BLOCK_DIVISION / 4)),
            pos_y - (BLOCK_DIVISION / 8), direction_variable * bullet_speed, damage, range, owner));
    fire_cooldown = cooldown;
    owner.set_action_shoot();
}

void Gun::reset_ammo_amount() { ammo = 0; }

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

FlameThrower::FlameThrower(Rabbit& owner, Map& manager):
        Gun(FLAMETHROWER_MAX_AMMO, FLAMETHROWER_DAMAGE, FLAMETHROWER_RANGE,
            FLAMETHROWER_BULLET_SPEED, owner, manager) {}

bool FlameThrower::has_ammo() { return ammo > 0; }

void FlameThrower::fire(int pos_x, int pos_y, int direction) {
    if (can_fire()) {
        Gun::add_bullet_to_map(pos_x, pos_y, direction, FLAMETHROWER, FLAMETHROWER_FIRE_COOLDOWN);
        ammo--;
    }
}

RocketLauncher::RocketLauncher(Rabbit& owner, Map& manager):
        Gun(ROCKETLAUNCHER_MAX_AMMO, ROCKETLAUNCHER_DAMAGE, ROCKETLAUNCHER_RANGE,
            ROCKETLAUNCHER_BULLET_SPEED, owner, manager) {}

bool RocketLauncher::has_ammo() { return ammo > 0; }

void RocketLauncher::fire(int pos_x, int pos_y, int direction) {
    if (can_fire()) {
        Gun::add_bullet_to_map(pos_x, pos_y, direction, ROCKETLAUNCHER,
                               ROCKETLAUNCHER_FIRE_COOLDOWN);
        ammo--;
    }
}

RayGun::RayGun(Rabbit& owner, Map& manager):
        Gun(RAYGUN_MAX_AMMO, RAYGUN_DAMAGE, RAYGUN_RANGE, RAYGUN_BULLET_SPEED, owner, manager) {}

bool RayGun::has_ammo() { return ammo > 0; }

void RayGun::fire(int pos_x, int pos_y, int direction) {
    if (can_fire()) {
        Gun::add_bullet_to_map(pos_x, pos_y, direction, RAYGUN, RAYGUN_FIRE_COOLDOWN);
        ammo--;
    }
}
