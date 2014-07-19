#include "Ball.hpp"

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream> 


Ball::Ball() { }


void Ball::launch(std::string direction) {
    if(direction == "left") {
        velocity.x = -150;
        velocity.y = -150;
        playerHasBall = false;
    }
    if(direction == "right") {
        velocity.x = 150;
        velocity.y = -150;
        playerHasBall = false;
    }
}


void Ball::update(Player player, sf::Time deltaTime, std::vector<Tile>& moveableTiles) {
    int last_x = sprite.getPosition().x;
    int last_y = sprite.getPosition().y;

    if(playerHasBall) {
        sprite.setPosition(player.sprite.getPosition().x + 20, player.sprite.getPosition().y - 25);
    }
    else {
        // Move on Y-axis.
        sprite.move(0, velocity.y * deltaTime.asSeconds());

        // Collision detection and resolution.
        for(unsigned int i = 0; i < moveableTiles.size(); i++) {
            if(Collision::BoundingBoxTest(sprite, moveableTiles[i].tile)) {

                // Calculate the angle to tile's center, to determine collision direction.
                double angle = std::atan2(sprite.getPosition().y - moveableTiles[i].tile.getPosition().y,
                                          sprite.getPosition().x - moveableTiles[i].tile.getPosition().x) * 180 / M_PI;
                if(angle <= -45 && angle >= -135) {     // Colliding TOP.
                    sprite.setPosition(last_x, sprite.getPosition().y - 1);
                    velocity.y = -velocity.y;
                    moveableTiles.erase(moveableTiles.begin() + i);
                    std::cout << "Collision from TOP." << std::endl;
                }
                if(angle > 45 && angle <= 135) {        // collision from BOTTOM
                    sprite.setPosition(last_x, sprite.getPosition().y + 1);
                    velocity.y = -velocity.y;
                    moveableTiles.erase(moveableTiles.begin() + i);
                    std::cout << "Collision from BOTTOM." << std::endl;
                }

            }
        }
        // Move on X-axis.
        sprite.move(velocity.x * deltaTime.asSeconds(), 0);

        // Collision detection and resolution.
        for(unsigned int i = 0; i < moveableTiles.size(); i++) {
            if(Collision::BoundingBoxTest(sprite, moveableTiles[i].tile)) {

                // Calculate the angle to tile's center, to determine collision direction.
                double angle = std::atan2(sprite.getPosition().y - moveableTiles[i].tile.getPosition().y,
                                          sprite.getPosition().x - moveableTiles[i].tile.getPosition().x) * 180 / M_PI;
                if(angle > -45 && angle <= 45) {    // Colliding LEFT.
                    sprite.setPosition(sprite.getPosition().x + 1, last_y);
                    velocity.x = -velocity.x;
                    moveableTiles.erase(moveableTiles.begin() + i);
                    std::cout << "Colliding LEFT." << std::endl;
                }
                if((angle > 135 && angle <= 180) ||
                   (angle > -180 && angle < -135)) {  // Colliding RIGHT.
                    sprite.setPosition(sprite.getPosition().x - 1, last_y);
                    velocity.x = -velocity.x;
                    moveableTiles.erase(moveableTiles.begin() + i);
                    std::cout << "Colliding RIGHT." << std::endl;
                }
            }
        }
    }
}