#include "Ball.hpp"


Ball::Ball() { }

void Ball::launch(std::string direction) {
    if(direction == "left") {
        velocity.x = -5;
        velocity.y = -5;
        playerHasBall = false;
    }
    if(direction == "right") {
        velocity.x = 5;
        velocity.y = -5;
        playerHasBall = false;
    }
}

void Ball::update(sf::RenderWindow& window, Player player, sf::Time deltaTime) {
    if(playerHasBall) {
        sprite.setPosition(player.sprite.getPosition().x + 20, player.sprite.getPosition().y - 25);
    }
    else {
        sprite.move(sf::Vector2f(velocity.x, velocity.y));
    }
}