#include "Player.hpp"


Player::Player() { }

void Player::update(sf::RenderWindow& window, sf::Time deltaTime) {
    /*
    if(movingRight) {
    velocity.x = 60.0f;
    }
    else if(movingLeft) {
    velocity.x = -60.0f;
    }
    else {
    velocity.x = 0.0f;
    }

    if(movingUp) {
    velocity.y = -60.0f;
    }
    else if(movingDown) {
    velocity.y = 60.0f;
    }
    else {
    velocity.y = 0.0f;
    }
    sprite.move(velocity * deltaTime.asSeconds());

    sprite.setColor(sf::Color::White);
    */

    sf::Vector2f mousePos(sf::Vector2f(sf::Mouse::getPosition(window)));
    sprite.setPosition(mousePos.x, mousePos.y);
}
