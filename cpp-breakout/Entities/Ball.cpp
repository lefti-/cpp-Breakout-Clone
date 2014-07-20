#include "Ball.hpp"
#include <iostream>


Ball::Ball() { }

void Ball::launch(std::string direction) {
    if(direction == "left") {
        velocity.x = -250;
        velocity.y = -250;
        playerHasBall = false;
    }
    if(direction == "right") {
        velocity.x = 250;
        velocity.y = -250;
        playerHasBall = false;
    }
}

void Ball::update(Player player, sf::Time deltaTime) {
    int last_x = sprite.getPosition().x;
    int last_y = sprite.getPosition().y;

    int bottom = sprite.getPosition().y + sprite.getTextureRect().height;
    int left = sprite.getPosition().x;
    int right = sprite.getPosition().x + sprite.getTextureRect().width;
    int top = sprite.getPosition().y;

    // Get the (x, y)-coords of the player sprite corners.
    topLeft.x = left;
    topLeft.y = top;
    topRight.x = right;
    topRight.y = top;
    bottomLeft.x = left;
    bottomLeft.y = bottom;
    bottomRight.x = right;
    bottomRight.y = bottom;

    sprite.move(velocity.x * deltaTime.asSeconds(), velocity.y * deltaTime.asSeconds());

    if(playerHasBall) {
        sprite.setPosition(player.sprite.getPosition().x + 20, player.sprite.getPosition().y - 25);
    }
}