#include "Ball.hpp"


Ball::Ball() { }

void Ball::launch(std::string direction) {
    if(direction == "left") {
        velocity.x = -1;
        velocity.y = -1;
        playerHasBall = false;
    }
    if(direction == "right") {
        velocity.x = 1;
        velocity.y = -1;
        playerHasBall = false;
    }
}

void Ball::update(Player player, sf::Time deltaTime) {
    if(playerHasBall) {
        sprite.setPosition(player.sprite.getPosition().x + 20, player.sprite.getPosition().y - 25);
    }
    else {
        sprite.move(sf::Vector2f(velocity.x, velocity.y));
    }
}