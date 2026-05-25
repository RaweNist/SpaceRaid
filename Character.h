#pragma once
#include "Constants.h"
#include "Projectile.h"
#include "Timer.h"

enum class DirectionX : int {
	LEFT = -1,
	STOP = 0,
	RIGHT = 1,
};
enum class DirectionY : int {
	UP = -1,
	STOP = 0,
	DOWN = 1,
};
class Projectile;
class Character {
protected:
	bool _isAlive;
	char c_type;
	int c_health;
	float c_speed;
	unsigned c_cooldown;
	float c_atcrange;
	float c_rotation;
	Timer c_timer;
	sf::Vector2f c_size;
	sf::Vector2f c_pos;
	sf::Sprite c_sprite;
	DirectionX c_direction_x = DirectionX::STOP;
	DirectionY c_direction_y = DirectionY::STOP;

	std::vector<Projectile> bullets;
	std::vector<float> angles;
	bool canShoot;

public:
	virtual ~Character();

	virtual void Update(sf::RenderWindow& window, std::string* map, std::vector <Character*>& chars, float time) = 0;
	virtual int checkCollision(std::string* map, float time) = 0;
	virtual void Attack(sf::RenderWindow& window, std::string* map, std::vector<Character*>& chars, float time) = 0;
	void takeDamage(float damage);

	void setType(char type);
	void setHp(int hp);
	void setCanShoot(bool can);
	void setPosition(sf::Vector2f& pos);
	void setRotation(float rot);
	void setDirectionX(DirectionX direction_x);
	void setDirectionY(DirectionY direction_y);

	bool isAlive() const;
	bool getCanShoot() const;
	int getHP() const;
	float getRotation() const;
	float getSpeed() const;
	char getType() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	sf::Sprite& getSprite();
	DirectionX getDirectionX() const;
	DirectionY getDirectionY() const;

	float calcAngle(float cx, float cy);

	std::vector<Projectile>& getBullets();
	std::vector<float>& getBulletsAngles();
	void addBullet(Projectile bul);
	void addBulletAngle(float ang);
	Projectile getBullet(int i) const;

	Timer& getTimer();
	void checkProjectiles(sf::RenderWindow& window, std::vector <Character*>& chars, std::string* map, float time);
	void deleteProjectile(int index);
};
