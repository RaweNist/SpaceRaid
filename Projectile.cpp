#include "Projectile.h"

Projectile::Projectile():type('E'),pr_damage(0), speed(1) {}

Projectile::Projectile(char _type, sf::Vector2f _pos, int dmg, float _speed, sf::Texture& texture)
{
    type = _type;
    pos = _pos;
    sprite.setPosition(pos);
    pr_damage = dmg;
    sprite.setTexture(texture);
    sprite.setOrigin(TILE_SIZE / 8, TILE_SIZE / 8);
    speed = _speed;
}

char Projectile::getType() const
{
    return type;
}

int Projectile::getDamage() const
{
    return pr_damage;
}

float Projectile::getSpeed() const
{
    return speed;
}

sf::Sprite& Projectile::getSprite()
{
    return sprite;
}

sf::Vector2f Projectile::getPosition() const
{
    return pos;
}

void Projectile::setDamage(int dmg)
{
    pr_damage = dmg;
}

void Projectile::setPos(sf::Vector2f _pos)
{
    pos = _pos;
}

void Projectile::Update(sf::RenderWindow& window, sf::Vector2f vector, float time)
{
    sprite.move(vector);
    pos = sprite.getPosition();
    window.draw(sprite);
}

int Projectile::checkCollision(std::string* map, float time)
{
	int i = pos.y / 64;
	int j = pos.x / 64;

    if (map[i][j] == '2') {
        return 2;
    }
	else if (map[i][j] == '4') {
        int chance = rand() % 5;
        if (rand() % 5 == 0)
            map[i][j] = 'A';
        else 
		    map[i][j] = '1';
        return 2;
	}
    return 0;
}

bool Projectile::dealDamage(std::vector <Character*>& chars)
{
    for (int i = 0; i < chars.size(); ++i) {
        if (sprite.getGlobalBounds().intersects(chars[i]->getSprite().getGlobalBounds())) {
            if ((type == 'P' && chars[i]->getType() == 'e') || (type == 'E' && chars[i]->getType() == 'p')) {
                chars[i]->takeDamage(pr_damage);
                return true;
            }
        }
    }
    return false;
}
