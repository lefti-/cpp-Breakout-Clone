#ifndef TILE_HPP
#define TILE_HPP

#include "Player.hpp"
#include "Entity.hpp"

#include <SFML/Graphics.hpp>

// Maybe add destructor??
//m_body->DestroyFixture(m_body->GetFixtureList());
//m_body->GetWorld()->DestroyBody(m_body);

class Tile : public Entity {
public:
    Tile(b2World* world, float posX, float posY);
    void draw(sf::RenderWindow& window);
    void saySomething();

    int armor;
    bool flaggedToErase = false;
    b2Body* tileBody;
    sf::Sprite sprite;
private:
    float PTM_RATIO = 32.f;
    int HALF_WIDTH = 32;
    int HALF_HEIGHT = 16;
    b2BodyDef tileBodyDef;
    b2PolygonShape tileShape;
    b2FixtureDef tileFixtureDef;
};
#endif // TILE_HPP