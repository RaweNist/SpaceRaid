#include "Gunner.h"
#include "Projectile.h"
#include "Textures.h"

void Gunner::Update(sf::RenderWindow& window, std::string* map, std::vector<Character*>& chars, float time)
{
    if (isAlive()) {
        calcAngle(getTarget().getPosition().x, getTarget().getPosition().y);
        checkCollision(map, time);
        c_sprite.setPosition(c_pos);
        c_sprite.setRotation(c_rotation);
        window.draw(getSprite());
    }
    Attack(window, map, chars, time);
    if (_isAlive && getHP() <= 0) {
        _isAlive = 0;
        c_type = 'd';
    }     	
}

void Gunner::Attack(sf::RenderWindow& window, std::string* map, std::vector<Character*>& chars, float time)
{
    textures::setBulletTexture();
    if (getCanShoot() && isAlive()) {
        setCanShoot(false);
        if (getTimer().getActive() == 0) {
            getTimer().start(c_cooldown, [=]() { setCanShoot(true); });
        }
        addBullet(Projectile('E', getPosition(), 10, 10, textures::enemy_bullet_texture));
        addBulletAngle((getRotation() - 90) / 180 * PI);
    }
    checkProjectiles(window, chars, map, time);
}
