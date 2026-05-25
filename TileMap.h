#pragma once
#include "Character.h";
class TileMap {
private:
    int HEIGHT_MAP;
    int WIDTH_MAP;
    sf::Vector2f player_pos;
    std::string* tileMap;
public:
    TileMap(std::string* TileMap, int h, int w, sf::Vector2f playerpos);
    void setTiles(std::string* TileMap);
    void drawMap(sf::RenderWindow* window);
    void setCharacters(sf::RenderWindow* window, std::vector <Character*>& chars);

    std::string* getMap() const;
    sf::Vector2f getPlayerPos() const;
};
