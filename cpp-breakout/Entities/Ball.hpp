#ifndef BALL_HPP
#define BALL_HPP

#include "Player.hpp"
#include "Tile.hpp"
#include "../Collision/Collision.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>


class Ball {
public:
    Ball();

    void launch(std::string direction);

    void update(Player player, sf::Time deltaTime, std::vector<Tile>& moveableTiles);

    bool playerHasBall = true;

    sf::Sprite sprite;
    sf::Vector2f velocity;

};
#endif