// The header file should have a header guard to prevent multiple inclusion errors.
// header guard at start of header file
#ifndef TILE_HPP
#define TILE_HPP

#include "Player.hpp"

#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile(sf::Sprite sprite);

    sf::Sprite tile;
};
// end header guard at bottom of header file
#endif // TILE_HPP