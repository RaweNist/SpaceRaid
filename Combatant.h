#pragma once
#include "Enemy.h"

class Combatant : public Enemy {
public:
    Combatant(sf::Texture& texture, sf::Vector2f start_pos, float health, float speed,
        unsigned cooldown, Character& _player)
        : Enemy(texture, start_pos, health, speed, cooldown, _player) {
        c_atcrange = 10;
    }

    void Update(sf::RenderWindow& window, std::string* map, std::vector <Character*>& chars, float time) override;

    void moveToPlayer(sf::RenderWindow& window, std::string* map, std::vector <Character*>& chars, float time);
    void Attack(sf::RenderWindow& window, std::string* map, std::vector <Character*>& chars, float time) override;
};