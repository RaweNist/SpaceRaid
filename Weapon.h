#pragma once
#include "Projectile.h"
class Weapon {
private:
    std::string name;
    Projectile pr;
    unsigned cooldown;
    unsigned ammo;
public:
    Weapon(std::string name, sf::Vector2f pos, int damage, float speed, unsigned cooldown, unsigned ammo);

    Projectile& getProjectile();
    unsigned getAmmo();
    unsigned getCooldown();
    std::string getName();
    void setAmmo(unsigned newammo);
};