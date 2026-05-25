#include "Character.h"

Character::~Character() { }

void Character::takeDamage(float damage) {
    c_health -= damage;
}

void Character::setType(char type)
{
    c_type = type;
}

void Character::setHp(int hp)
{
    c_health = hp;
}

void Character::setCanShoot(bool can)
{
	canShoot = can;
}

void Character::setPosition(sf::Vector2f& pos) {
    c_pos = pos;
}

void Character::setRotation(float rot)
{
    c_rotation = rot;
}

void Character::setDirectionX(DirectionX direction_x) {
    c_direction_x = direction_x;
}

void Character::setDirectionY(DirectionY direction_y)
{
	c_direction_y = direction_y;
}

bool Character::isAlive() const
{
    return _isAlive;
}

bool Character::getCanShoot() const
{
	return canShoot;
}

int Character::getHP() const {
    return c_health;
}

float Character::getRotation() const
{
    return c_rotation;
}

float Character::getSpeed() const
{
	return c_speed;
}

char Character::getType() const
{
    return c_type;
}

sf::Vector2f Character::getSize() const {
    return c_size;
}

sf::Vector2f Character::getPosition() const {
    return c_pos;
}

sf::Sprite& Character::getSprite(){
    return c_sprite;
}

DirectionX Character::getDirectionX() const
{
	return c_direction_x;
}

DirectionY Character::getDirectionY() const
{
	return c_direction_y;
}

float Character::calcAngle(float x, float y)
{
    float atg = 0;
    float angle = 0;
    sf::Vector2f pos = getPosition();
    if (y < pos.y) {
        atg = atan((x - pos.x) / (pos.y - y));
        angle = atg * 180 / PI;
    }
    else {
        atg = PI - atan((x - pos.x) / (y - pos.y));
        angle = atg * 180 / PI;
    }

    setRotation(angle);
    return angle;
}

std::vector<Projectile>& Character::getBullets()
{
    return bullets;
}

std::vector<float>& Character::getBulletsAngles()
{
    return angles;
}

void Character::addBullet(Projectile bul)
{
    bullets.push_back(bul);
}

void Character::addBulletAngle(float ang)
{
    angles.push_back(ang);
}

Projectile Character::getBullet(int i) const
{
    return bullets[i];
}

Timer& Character::getTimer()
{
    return c_timer;
}

void Character::checkProjectiles(sf::RenderWindow& window, std::vector <Character*>& chars, std::string* map, float time)
{
    for (int i = 0; i < bullets.size(); ++i) {
        sf::Vector2f vector = sf::Vector2f(bullets[i].getSpeed() * cos(angles[i]), bullets[i].getSpeed() * sin(angles[i]));
        bullets[i].Update(window, vector, time);
        if (bullets[i].dealDamage(chars) || bullets[i].checkCollision(map, time) == 2) {
            deleteProjectile(i);
            break;
        }
        if (angles.size() > 512 || abs(bullets[i].getPosition().x - getPosition().x) > c_atcrange || abs(bullets[i].getPosition().y - getPosition().y) > 2048) {
            deleteProjectile(0);
            break;
        }
    }
}

void Character::deleteProjectile(int index)
{
    bullets.erase(bullets.begin() + index);
    angles.erase(angles.begin() + index);
}
