#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>


class Player {
public:
    // Player(sf::Vector2f position, sf::Vector2f size, sf::Color color);
    Player();
    void update(sf::RenderWindow& window, sf::Time deltaTime);
    bool movingUp, movingDown, movingLeft, movingRight;

    sf::Sprite sprite;
    sf::Vector2f velocity;
    sf::Vector2f mousePos;
};
#endif // PLAYER_HPP