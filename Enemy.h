#pragma once
#include "Character.h"
#include "Projectile.h"
#include "Textures.h"

class EnemyController;

class Enemy : public Character {
private:
    Character& target;
public:
    Enemy() = delete;
    Enemy(sf::Texture& texture, sf::Vector2f start_pos, float health, float speed, 
        unsigned cooldown, Character& _player);
    ~Enemy();

    int checkCollision(std::string* map, float time) override;
    virtual void Attack(sf::RenderWindow& window, std::string* map, std::vector <Character*>& chars, float time) = 0;

    void setTarget(Character& tgt);
    Character& getTarget();

    float getAtcRange();
};
