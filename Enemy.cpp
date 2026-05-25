#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture, sf::Vector2f start_pos, float health, float speed, unsigned cooldown, Character& _player) : target(_player)
{
	_isAlive = true;
	c_type = 'e';
    c_pos = start_pos;
    c_health = health;
    c_rotation = 0;
    c_speed = speed;
	c_cooldown = cooldown;
    canShoot = true;

    c_sprite.setTexture(texture);
    c_sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    c_size = sf::Vector2f(c_sprite.getTextureRect().width, c_sprite.getTextureRect().height);
}

Enemy::~Enemy() {}

int Enemy::checkCollision(std::string* map, float time)
{
	int h = TILE_SIZE;
	int w = TILE_SIZE;
	int dx = (int) getDirectionX();
	int dy = (int) getDirectionY();
	int i = (c_pos.y) / 64;
	int j = (c_pos.x) / 64;
	if (dy > 0 && (map[(int)(c_pos.y + 32) / 64][j] == '2' || map[(int)(c_pos.y + 32) / 64][j] == '4' ||
		map[(int)(c_pos.y + 30) / 64][(int)(c_pos.x + 30) / 64] == '2' || map[(int)(c_pos.y + 30) / 64][(int)(c_pos.x + 30) / 64] == '4' ||
		map[(int)(c_pos.y + 30) / 64][(int)(c_pos.x - 30) / 64] == '2' || map[(int)(c_pos.y + 30) / 64][(int)(c_pos.x - 30) / 64] == '4'))
	{
		c_pos.y -= c_speed * time;
	}
	if (dy < 0 && (map[(int)(c_pos.y - 32) / 64][j] == '2' || map[(int)(c_pos.y - 32) / 64][j] == '4' ||
		map[(int)(c_pos.y - 30) / 64][(int)(c_pos.x + 30) / 64] == '2' || map[(int)(c_pos.y - 30) / 64][(int)(c_pos.x + 30) / 64] == '4' ||
		map[(int)(c_pos.y - 30) / 64][(int)(c_pos.x - 30) / 64] == '2' || map[(int)(c_pos.y - 30) / 64][(int)(c_pos.x - 30) / 64] == '4'))
	{
		c_pos.y += c_speed * time;
	}
	if (dx > 0 && (map[i][(int)(c_pos.x + 32) / 64] == '2' || map[i][(int)(c_pos.x + 32) / 64] == '4' ||
		map[(int)(c_pos.y + 30) / 64][(int)(c_pos.x + 30) / 64] == '2' || map[(int)(c_pos.y + 30) / 64][(int)(c_pos.x + 30) / 64] == '4' ||
		map[(int)(c_pos.y - 30) / 64][(int)(c_pos.x + 30) / 64] == '2' || map[(int)(c_pos.y - 30) / 64][(int)(c_pos.x + 30) / 64] == '4'))
	{
		c_pos.x -= c_speed * time;
	}
	if (dx < 0 && (map[i][(int)(c_pos.x - 32) / 64] == '2' || map[i][(int)(c_pos.x - 32) / 64] == '4' ||
		map[(int)(c_pos.y + 30) / 64][(int)(c_pos.x - 30) / 64] == '2' || map[(int)(c_pos.y + 30) / 64][(int)(c_pos.x - 30) / 64] == '4' ||
		map[(int)(c_pos.y - 30) / 64][(int)(c_pos.x - 30) / 64] == '2' || map[(int)(c_pos.y - 30) / 64][(int)(c_pos.x - 30) / 64] == '2'))
	{
		c_pos.x += c_speed * time;
	}
	return 0;
}

void Enemy::setTarget(Character& tgt)
{
	target = tgt;
}

Character& Enemy::getTarget()
{
	return target;
}

float Enemy::getAtcRange()
{
	return c_atcrange;
}
