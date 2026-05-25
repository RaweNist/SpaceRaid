#include "PlayerController.h"
#include "SFMLConnect.h"
#include "Player.h"
#include "Projectile.h"

PlayerController* PlayerController::controller = nullptr;

PlayerController::~PlayerController() {
    delete controller;
}

PlayerController* PlayerController::getPlayerController() {
    if (!controller) {
        controller = new PlayerController();
    }

    return controller;
}

void PlayerController::controllPlayer(sf::RenderWindow& window, Player* player, float time) {
    sf::Vector2f updated_pos = player->getPosition();
    float update_rot = player->getRotation();
    player->setDirectionX(DirectionX::STOP);
    player->setDirectionY(DirectionY::STOP);
    window.setKeyRepeatEnabled(true);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player->setState(State::RUN);
        player->setDirectionX(DirectionX::LEFT);
        if (SFMLConnect::checkKeyPressedS()) {
            updated_pos.x -= sqrt(0.5) * player->getSpeed() * time;
            updated_pos.y += sqrt(0.5) * player->getSpeed() * time;
            player->setDirectionY(DirectionY::DOWN);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            updated_pos.x -= sqrt(0.5) * player->getSpeed() * time;
            updated_pos.y -= sqrt(0.5) * player->getSpeed() * time;
            player->setDirectionY(DirectionY::UP);
        }
        else {
            updated_pos.x -= player->getSpeed() * time;
            player->setDirectionY(DirectionY::STOP);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->setState(State::RUN);
        player->setDirectionX(DirectionX::RIGHT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            updated_pos.x += sqrt(0.5) * player->getSpeed() * time;
            updated_pos.y += sqrt(0.5) * player->getSpeed() * time;
            player->setDirectionY(DirectionY::DOWN);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            updated_pos.x += sqrt(0.5) * player->getSpeed() * time;
            updated_pos.y -= sqrt(0.5) * player->getSpeed() * time;
            player->setDirectionY(DirectionY::UP);
        }
        else {
            updated_pos.x += player->getSpeed() * time;
            player->setDirectionY(DirectionY::STOP);
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
        && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)
        && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->setState(State::RUN);
        player->setDirectionX(DirectionX::STOP);
        player->setDirectionY(DirectionY::UP);
        updated_pos.y -= player->getSpeed() * time;
        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) 
        && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)
        && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->setState(State::RUN);
        player->setDirectionX(DirectionX::STOP);
        player->setDirectionY(DirectionY::DOWN);
        updated_pos.y += player->getSpeed() * time;
    }
    window.setKeyRepeatEnabled(false);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && isChange == 0) {
        isChange = 1;
        player->nextWeapon();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && isChange == 0) {
        isChange = 1;
        player->prewWeapon();
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        isChange = 0;
    }

    player->setPosition(updated_pos);
    player->setRotation(update_rot);
}