#ifndef _LEVEL_HPP
#define _LEVEL_HPP

#include "../Entities/Tile.hpp"

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>


class Level {
public:
    Level();
    void loadLevel(b2World* world);
    void loadMap(const char* fileName, const char* tileTextureFile);

    std::vector<std::unique_ptr<Tile>> solidTiles;
private:
    const float PTM_RATIO = 32.f;
    const int HALF_WIDTH = 32;
    const int HALF_HEIGHT = 16;
    const int TILE_WIDTH = 64;
    const int TILE_HEIGHT = 32;
    std::vector<std::vector<sf::Vector2i>> map;
    std::vector<sf::Vector2i> tempMap;
    sf::Texture tileTexture;
    sf::Sprite tiles;
    sf::Sprite sprite;
};
#endif
