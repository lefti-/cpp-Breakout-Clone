#include "Player.hpp"

#include <iostream>
#include <algorithm>

//Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Color color)
Player::Player() { }

void Player::update(sf::RenderWindow& window, sf::Time deltaTime) {
    if(movingRight) {
        velocity.x = 40.0f;
    }
    else if(movingLeft) {
        velocity.x = -40.0f;
    }
    else {
        velocity.x = 0.0f;
    }

    if(movingUp) {
        velocity.y = -40.0f;
    }
    else if(movingDown) {
        velocity.y = 40.0f;
    }
    else {
        velocity.y = 0.0f;
    }

    sprite.move(velocity * deltaTime.asSeconds());

    sf::Vector2f mousePos(sf::Vector2f(sf::Mouse::getPosition(window)));
    sprite.setPosition(mousePos.x, 600.f);

    sprite.setColor(sf::Color::White);
    /*
    // Bounding box collision test.
    bottom = sprite.getPosition().y + sprite.getTextureRect().height;
    left = sprite.getPosition().x;
    right = sprite.getPosition().x + sprite.getTextureRect().width;
    top = sprite.getPosition().y;


    // Find the 4 corners of the player.
    sf::Vector2i topLeft(sf::Vector2i((int)left / 32, (int)top / 32));
    sf::Vector2i topRight(sf::Vector2i((int)right / 32, (int)top / 32));
    sf::Vector2i bottomLeft(sf::Vector2i((int)left / 32, (int)bottom / 32));
    sf::Vector2i bottomRight(sf::Vector2i((int)right / 32, (int)bottom / 32));

    // Every update we have to have new fresh tiles
    tilesTouching.clear();

    // Add the topLeft corner to the tiles
    tilesTouching.push_back(topLeft);
    if(std::find(tilesTouching.begin(), tilesTouching.end(), topRight) == tilesTouching.end()) {
        tilesTouching.push_back(topRight);
    }
    if(std::find(tilesTouching.begin(), tilesTouching.end(), bottomLeft) == tilesTouching.end()) {
        tilesTouching.push_back(bottomLeft);
    }
    if(std::find(tilesTouching.begin(), tilesTouching.end(), bottomRight) == tilesTouching.end())
    {
        tilesTouching.push_back(bottomRight);
    }
    */
}