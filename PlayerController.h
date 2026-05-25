#pragma once
#include "Constants.h"

class Player;

class PlayerController {
private:
    PlayerController() = default;

    static PlayerController* controller;
    bool isChange = 0;
public:
    PlayerController(PlayerController const&) = delete;
    void operator=(PlayerController const&) = delete;
    ~PlayerController();

    static PlayerController* getPlayerController();

    void controllPlayer(sf::RenderWindow& window, Player* player, float time);
};