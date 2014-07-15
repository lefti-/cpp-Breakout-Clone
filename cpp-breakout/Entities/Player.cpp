#include "Player.hpp"

//Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Color color)
Player::Player() { }

void Player::update(sf::RenderWindow& window, sf::Time deltaTime) {

    sf::Vector2f mousePos(sf::Vector2f(sf::Mouse::getPosition(window)));
    sprite.setPosition(mousePos.x, 600.f);
}