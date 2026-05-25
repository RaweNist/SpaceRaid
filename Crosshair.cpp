#include "Crosshair.h"
#include "Constants.h"

Crosshair::Crosshair(sf::Texture& texture, sf::Vector2i pos) {
	c_sprite.setTexture(texture);
	c_pos = pos;
	c_size = sf::Vector2f(c_sprite.getTextureRect().width, c_sprite.getTextureRect().height);
}
Crosshair::~Crosshair() {}

void Crosshair::setPosition(sf::Vector2i& pos)
{
	c_pos = pos;
}

void Crosshair::Update(float time) {
	c_sprite.setTexture(textures::crosshair_texture);
	
}

sf::Sprite Crosshair::getSprite() {
	return c_sprite;
}
