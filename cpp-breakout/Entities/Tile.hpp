#ifndef TILE_HPP
#define TILE_HPP

#include "Player.hpp"

#include <SFML/Graphics.hpp>


class Tile {
public:
    Tile();
    Tile(sf::Sprite sprite);
    void setBody(b2World* world, float posX, float posY);

    const float PX_TO_METER = 32.f;
    const int HALF_WIDTH = 32;
    const int HALF_HEIGHT = 16;
    int armor;

    b2Body* tileBody;
    sf::Sprite tile;
};
#endif // TILE_HPP