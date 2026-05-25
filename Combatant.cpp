#include "Combatant.h"
#include "Textures.h"

void Combatant::Update(sf::RenderWindow& window, std::string* map, std::vector<Character*>& chars, float time)
{
    
    if (isAlive()) {
        calcAngle(getTarget().getPosition().x, getTarget().getPosition().y);
        moveToPlayer(window, map, chars, time);
        checkCollision(map, time);
        c_sprite.setPosition(c_pos);
        c_sprite.setRotation(c_rotation);
        window.draw(getSprite());
    }
    if (_isAlive && getHP() <= 0) {
        _isAlive = 0;
        c_type = 'd';
    }
}
void Combatant::moveToPlayer(sf::RenderWindow& window, std::string* map, std::vector<Character*>& chars, float time)
{
    sf::Vector2f updated_pos = getPosition();
    sf::Vector2f player_pos = getTarget().getPosition();

    if (updated_pos.x > player_pos.x) {
        setDirectionX(DirectionX::LEFT);
        updated_pos.x -= getSpeed() * time;
    }
    else if (updated_pos.x < player_pos.x)
    {
        setDirectionX(DirectionX::RIGHT);
        updated_pos.x += getSpeed() * time;
    }
    else 
        setDirectionX(DirectionX::STOP);

    if (updated_pos.y > player_pos.y)
    {
        setDirectionY(DirectionY::UP);
        updated_pos.y -= getSpeed() * time;
    }
    else if (updated_pos.y < player_pos.y)
    {
        setDirectionY(DirectionY::DOWN);
        updated_pos.y += getSpeed() * time;
    }
    else
        setDirectionY(DirectionY::STOP);

    float d = sqrt(abs(updated_pos.x - player_pos.x) + abs(updated_pos.y - player_pos.y));
    if (d <= getAtcRange()) {
        Attack(window, map, chars, time);
    }
    setPosition(updated_pos);
}

void Combatant::Attack(sf::RenderWindow& window, std::string* map, std::vector<Character*>& chars, float time)
{
    textures::setBulletTexture();
    if (getCanShoot()) {
        setCanShoot(false);
        if (getTimer().getActive() == 0) {
    	    getTimer().start(c_cooldown, [=]() { setCanShoot(true); });
        }
        addBullet(Projectile('E', getPosition(), 10, 50, textures::enemy_bullet_texture));
        addBulletAngle((getRotation() - 90) / 180 * PI);
    }
    
    checkProjectiles(window, chars, map, time);
}
