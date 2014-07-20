#ifndef TILE_HPP
#define TILE_HPP

#include "Player.hpp"

#include <SFML/Graphics.hpp>


class Tile {
public:
    Tile(sf::Sprite sprite);
    int getTile(int mapRow, int mapColumn);

    int armor;
    int mapRow;
    int mapColumn;
    sf::Sprite tile;
};
#endif // TILE_HPP