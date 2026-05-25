#include "TileMap.h"
#include "Textures.h"
#include "Gunner.h"
#include "Combatant.h"
#include "Boss.h"

TileMap::TileMap(std::string* TileMap, int h, int w, sf::Vector2f playerpos)
{
    HEIGHT_MAP = h;
    WIDTH_MAP = w;
    tileMap = TileMap;
    setTiles(TileMap);
    player_pos = playerpos;
}

void TileMap::setTiles(std::string* TileMap)
{
    for (int i = 0; i < HEIGHT_MAP; ++i) {
        for (int j = 0; j < WIDTH_MAP; ++j) {
            tileMap[i][j] = TileMap[i][j];
        }
    }
}

void TileMap::setCharacters(sf::RenderWindow* window, std::vector <Character*>& chars)
{
    for (int i = 0; i < HEIGHT_MAP; i++) {
        for (int j = 0; j < WIDTH_MAP; j++)
            if (getMap()[i][j] == 'C')
                chars.push_back(new Combatant(textures::combatant_texture, sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE), 50, 0.1, 1000, *chars[0]));
            else if (getMap()[i][j] == 'G')
                chars.push_back(new Gunner(textures::gunner_texture, sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE), 30, 0.1, 1500, *chars[0]));
            else if (getMap()[i][j] == 'B')
                chars.push_back(new Boss(textures::boss_texture, sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE), 300, 0.1, 500, *chars[0]));
    }
}

void TileMap::drawMap(sf::RenderWindow* window)
{
    textures::setTextures();
    sf::Sprite s_map;
    s_map.setTexture(textures::tiles_texture);
    for (int i = 0; i < HEIGHT_MAP; i++) {
        for (int j = 0; j < WIDTH_MAP; j++) {
            if (getMap()[i][j] == '0')  s_map.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE)); //Пустота
            else if (getMap()[i][j] == '1') s_map.setTextureRect(sf::IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));//Пол
            else if (getMap()[i][j] == '2') s_map.setTextureRect(sf::IntRect(2 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));//Стена
            else if (getMap()[i][j] == '3') s_map.setTextureRect(sf::IntRect(3 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));//Аптечка
            else if (getMap()[i][j] == '4') s_map.setTextureRect(sf::IntRect(4 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));//Ящик
            else if (getMap()[i][j] == 'T') s_map.setTextureRect(sf::IntRect(5 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));//Сундук
            else if (getMap()[i][j] == 'E') s_map.setTextureRect(sf::IntRect(6 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));//Выход
            else if (getMap()[i][j] == 'A') s_map.setTextureRect(sf::IntRect(7 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));//Патроны

            s_map.setPosition(j * TILE_SIZE, i * TILE_SIZE);
            window->draw(s_map);
        }
    }
}

std::string* TileMap::getMap() const
{
    return tileMap;
}

sf::Vector2f TileMap::getPlayerPos() const
{
    return player_pos;
}
