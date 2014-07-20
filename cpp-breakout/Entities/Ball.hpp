#ifndef BALL_HPP
#define BALL_HPP

#include "Player.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <algorithm>


class Ball {
public:
    Ball();
    void launch(std::string direction);
    void update(Player player, sf::Time deltaTime);

    bool playerHasBall = true;
    sf::Vector2f topLeft;
    sf::Vector2f topRight;
    sf::Vector2f bottomLeft;
    sf::Vector2f bottomRight;
    sf::Sprite sprite;
    sf::Vector2f velocity;
};
#endif