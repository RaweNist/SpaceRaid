#pragma once
#include <SFML/Graphics.hpp>

namespace textures {
    static sf::Texture player_texture;
    static sf::Texture combatant_texture;
    static sf::Texture gunner_texture;
    static sf::Texture boss_texture;
    static sf::Texture dead_boss_texture;
    static sf::Texture bullet_texture;
    static sf::Texture enemy_bullet_texture;
    static sf::Texture boss_bullet_texture;
    static sf::Texture crosshair_texture;
    static sf::Texture tiles_texture;

    static void setTextures() {
        player_texture.loadFromFile("player_pistol.png");
        combatant_texture.loadFromFile("Combatant.png");
        gunner_texture.loadFromFile("Gunner.png");
        boss_texture.loadFromFile("Boss.png");
        dead_boss_texture.loadFromFile("Boss_dead.png");
        bullet_texture.loadFromFile("bullet.png");
        enemy_bullet_texture.loadFromFile("enemy_bullet.png");
        boss_bullet_texture.loadFromFile("boss_bullet.png");
        crosshair_texture.loadFromFile("crosshair.png");
        tiles_texture.loadFromFile("tileset.png");
    }
    static void setBulletTexture() {
        bullet_texture.loadFromFile("bullet.png");
        enemy_bullet_texture.loadFromFile("enemy_bullet.png");
        boss_bullet_texture.loadFromFile("boss_bullet.png");
    }
}