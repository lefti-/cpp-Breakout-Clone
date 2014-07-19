#include "Tile.hpp"

#include <iostream>


Tile::Tile(sf::Sprite sprite) {
    tile = sprite;
}

int Tile::getTile(int mapRow, int mapColumn) {
    return (mapRow, mapColumn);
}
