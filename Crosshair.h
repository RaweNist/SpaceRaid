#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.h"

class Crosshair{

protected:
	sf::Vector2f c_size;
	sf::Vector2i c_pos;
	sf::Sprite c_sprite;
public:
	Crosshair() = delete;
	Crosshair(sf::Texture& texture, sf::Vector2i c_pos);
	~Crosshair();

	void Update(float time);
	sf::Sprite getSprite();
	void setPosition(sf::Vector2i& pos);
};