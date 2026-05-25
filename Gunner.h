#pragma once
#include "Enemy.h"
class Gunner : public Enemy {
public:
    Gunner(sf::Texture& texture, sf::Vector2f start_pos, float health, float speed,
        unsigned cooldown, Character& _player) 
        : Enemy(texture, start_pos, health, speed, cooldown, _player) {
        c_atcrange = 2048;
    }

    void Update(sf::RenderWindow& window, std::string* map, std::vector <Character*>& chars, float time) override;

    void Attack(sf::RenderWindow& window, std::string* map, std::vector<Character*>& chars, float time) override;
};