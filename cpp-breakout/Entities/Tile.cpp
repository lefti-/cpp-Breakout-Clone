#include "Tile.hpp"

#include <iostream>

Tile::Tile() { }

Tile::Tile(sf::Sprite sprite) {
    tile = sprite;
}

void Tile::setBody(b2World* world, float posX, float posY) {
    // Define a body.
    b2BodyDef tileBodyDef;
    tileBodyDef.type = b2_staticBody;
    tileBodyDef.position.Set((posX + HALF_WIDTH) / PX_TO_METER, (posY + HALF_HEIGHT) / PX_TO_METER);

    // Use the body definition to create the actual body instance.
    tileBody = world->CreateBody(&tileBodyDef);
    tileBody->SetUserData(this);

    // Define shape.
    b2PolygonShape tileShape;
    tileShape.SetAsBox(HALF_WIDTH / PX_TO_METER, HALF_HEIGHT / PX_TO_METER);

    // Define fixture.
    b2FixtureDef tileFixtureDef;
    tileFixtureDef.shape = &tileShape;
    //tileFixtureDef.restitution = 1;
    //tileFixtureDef.isSensor = true;
    tileFixtureDef.userData = "Tile";

    // Create fixture.
    tileBody->CreateFixture(&tileFixtureDef);
}