#pragma once
#include "Character.h"
#include "Timer.h"
#include "TileMap.h"
#include "Weapon.h"

class HUDRender;
class PlayerController;

enum class State {
    IDLE,
    RUN,
    WIN
};

class Player : public Character {
private:
    short curLvl;
    short lvls;
    TileMap* Maps;
    State c_state;
    PlayerController* p_controller;
    std::vector<Weapon> weapons;
    short cur_wpn;
public:
    Player() = delete;
    Player(sf::Texture& texture, sf::Vector2f startpos, float health, float speed, 
        short curlvl, TileMap* maps, short _lvls);
    ~Player();

    void Update(sf::RenderWindow& window, std::string* map, std::vector <Character*>& chars, float time) override;
    void drawCrosshair(sf::RenderWindow& window, sf::View& view);
    int checkCollision(std::string* map, float time) override;
    void Attack(sf::RenderWindow& window, std::string* map, std::vector <Character*>& chars, float time) override;
    void UpdateHUD(sf::RenderWindow& window, sf::View& view, float tim);

    int getCurLvl() const;
    State getState() const;

    void addWeapon(Weapon& wpn);
    Weapon& getWeapon(unsigned i);
    Weapon& getCurWeapon();
    int getCurWeaponId();
    int getWeaponsCount();
    void prewWeapon();
    void nextWeapon();
    void setState(State state);

};