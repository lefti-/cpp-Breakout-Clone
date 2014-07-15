#ifndef BALL_HPP
#define BALL_HPP

#include "Player.hpp"

#include <SFML/Graphics.hpp>

#include <string>

class Ball {
public:
    Ball();

    void launch(std::string direction);

    void update(sf::RenderWindow& window, Player player, sf::Time deltaTime);

    bool playerHasBall = true;

    sf::Sprite sprite;
    sf::Vector2f velocity;
};
#endif