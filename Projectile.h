#pragma once
#include "Character.h"

class Character;
class Projectile{
private:
	char type;
	float speed;
	sf::Vector2f pos;
	sf::Sprite sprite;
	int pr_damage;
public:
	Projectile();
	Projectile(char type, sf::Vector2f pos, int dmg, float speed, sf::Texture& texture);

	char getType() const;
	int getDamage() const;
	float getSpeed() const;
	sf::Sprite& getSprite();
	sf::Vector2f getPosition() const;

	void setDamage(int dmg);
	void setPos(sf::Vector2f pos);

	void Update(sf::RenderWindow& window, sf::Vector2f vector, float time);
	int checkCollision(std::string* map, float time);
	bool dealDamage(std::vector <Character*>& chars);
};
