#include "Boss.h"

void Boss::Update(sf::RenderWindow& window, std::string* map, std::vector<Character*>& chars, float time)
{
    Attack(window, map, chars, time);
    if (isAlive()) {
        calcAngle(getTarget().getPosition().x, getTarget().getPosition().y);
        checkCollision(map, time);
        c_sprite.setPosition(c_pos);
        c_sprite.setRotation(c_rotation);
    }
    if (_isAlive && getHP() <= 0) {
        _isAlive = 0;
        getTarget().setType('W');
        textures::setTextures();
        c_sprite.setTexture(textures::dead_boss_texture);
        c_type = 'd';
    }
    window.draw(getSprite());
}

void Boss::Attack(sf::RenderWindow& window, std::string* map, std::vector<Character*>& chars, float time)
{
    textures::setBulletTexture();
    if (getCanShoot() && isAlive()) {
        setCanShoot(false);
        if (getTimer().getActive() == 0) {
            getTimer().start(c_cooldown, [=]() { setCanShoot(true); });
        }
        addBulletAngle((getRotation() - 90) / 180 * PI);
        addBullet(Projectile('E', getPosition(), 15, 15, textures::boss_bullet_texture));
    }
    checkProjectiles(window, chars, map, time);
}
