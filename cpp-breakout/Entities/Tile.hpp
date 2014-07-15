#ifndef TILE_HPP
#define TILE_HPP

#include "Player.hpp"

#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile(sf::Sprite sprite);

    sf::Sprite tile;
    int armor;
};
#endif // TILE_HPP