#ifndef TILE_HPP
#define TILE_HPP

#include "Paddle.hpp"
#include "Entity.hpp"

#include <SFML/Graphics.hpp>

// Maybe add destructor??


class Tile : public Entity {
public:
    Tile(b2World* world, float posX, float posY, int tileLevel);
    ~Tile();
    void cracked();
    void draw(sf::RenderWindow& window);

    int textRectX;
    int textRectY;
    int armor;
    bool flaggedToErase = false;
    sf::Sprite sprite;
    b2Body* tileBody;
private:
    float PTM_RATIO = 32.f;
    int HALF_WIDTH = 32;
    int HALF_HEIGHT = 16;
    int TILE_WIDTH = 64;
    int TILE_HEIGHT = 32;
    b2BodyDef tileBodyDef;
    b2PolygonShape tileShape;
    b2FixtureDef tileFixtureDef;
    bUserData* bud;
};
#endif // TILE_HPP