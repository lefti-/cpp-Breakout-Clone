// The header file should have a header guard to prevent multiple inclusion errors.
// header guard at start of header file
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>


class Player {
public:
    // Player(sf::Vector2f position, sf::Vector2f size, sf::Color color);
    Player();

    void update(sf::RenderWindow& window, sf::Time deltaTime);

    bool collision(Player p);

    sf::Sprite sprite;

    std::vector<sf::Vector2i> tilesTouching;
    sf::Vector2f velocity;
    sf::Vector2f mousePos;

    float bottom, left, right, top;
    bool movingUp, movingDown, movingLeft, movingRight;
};
// end header guard at bottom of header file
#endif // PLAYER_HPP