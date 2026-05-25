#include "Weapon.h"
#include "Textures.h"

Weapon::Weapon(std::string _name, sf::Vector2f pos, int damage, float speed, unsigned cd, unsigned startammo)
{
    textures::setBulletTexture();
    name = _name;
    pr = Projectile('P', pos, damage, speed, textures::bullet_texture);
    cooldown = cd;
    ammo = startammo;
}

Projectile& Weapon::getProjectile()
{
    return pr;
}

unsigned Weapon::getAmmo()
{
    return ammo;
}

unsigned Weapon::getCooldown()
{
    return cooldown;
}

std::string Weapon::getName()
{
    return name;
}

void Weapon::setAmmo(unsigned newammo)
{
    ammo = newammo;
}
