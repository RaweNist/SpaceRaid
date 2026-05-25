#include "Textures.h"
#include "Player.h"
#include "Maps.h"

int main() {
    sf::View view;
    view.reset(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT));
    TileMap lvl1(lvl_1, 14, 30, sf::Vector2f(WINDOW_WIDTH / 2 - 64, WINDOW_HEIGHT / 2));
    TileMap lvl2(lvl_2, 36, 28, sf::Vector2f(WINDOW_WIDTH / 2 - 64, TILE_SIZE * 34));
    TileMap lvl3(lvl_3, 36, 28, sf::Vector2f(TILE_SIZE * 14, TILE_SIZE * 2));
    TileMap lvl4(lvl_4, 30, 30, sf::Vector2f(TILE_SIZE * 15, TILE_SIZE * 28));
    TileMap lvls[4] = { lvl1, lvl2, lvl3, lvl4 };

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Raid");
    textures::setTextures();

    std::vector <Character*> characters;

    Player* player = new Player(textures::player_texture, sf::Vector2f(WINDOW_WIDTH / 2 - 64, WINDOW_HEIGHT / 2), 100, 0.5, 0, lvls, 4);
    
    std::string* lvlActive = nullptr;
    sf::Clock clock;

    while (window.isOpen()) {
        window.setMouseCursorVisible(0);
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= CLOCKS_PER_SEC;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        TileMap curLvl = lvls[player->getCurLvl()];
        window.clear(BLACK);
        curLvl.drawMap(&window);

        if (!lvlActive || lvlActive != curLvl.getMap()) {
            characters.clear();
            characters.push_back(player);
            curLvl.setCharacters(&window, characters);
            lvlActive = curLvl.getMap();
        }

        for (int i = 0; i < characters.size(); ++i) {
            characters[i]->Update(window, curLvl.getMap(), characters, time);
        }

        player->UpdateHUD(window, view, time);
        window.setView(view);
        window.display();
        }
    return 0;
}
