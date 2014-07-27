/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "Tile.hpp"
#include <iostream>


Tile::Tile(b2World* world, float posX, float posY, int tileLevel)
{
    // Define a body.
    tileBodyDef.type = b2_staticBody;
    tileBodyDef.position.Set((posX + HALF_WIDTH) / PTM_RATIO, (posY + HALF_HEIGHT) / PTM_RATIO);

    // Use the body definition to create the actual body instance.
    tileBody = world->CreateBody(&tileBodyDef);
    tileBody->SetUserData(static_cast<Entity*>(this));

    // Define shape.
    tileShape.SetAsBox(HALF_WIDTH / PTM_RATIO, HALF_HEIGHT / PTM_RATIO);

    // Define fixture.
    tileFixtureDef.shape = &tileShape;
    tileFixtureDef.density = 1.f;
    tileFixtureDef.restitution = 0.f;
    tileFixtureDef.friction = 0.f;

    // Create user data.
    bUserData* bud = new bUserData;
    bud->entityType = TILE;

    if(tileLevel == 1) {
        bud->tileLevel = LEVEL1;
    }
    else if(tileLevel == 2) {
        bud->tileLevel = LEVEL2;
    }
    else if(tileLevel == 3) {
        bud->tileLevel = LEVEL3;
    }
    else if(tileLevel == 4) {
        bud->tileLevel = LEVEL4;
    }
    else if(tileLevel == 5) {
        bud->tileLevel = LEVEL5;
    }
    else if(tileLevel == 6) {
        bud->tileLevel = LEVEL6;
    }

    tileFixtureDef.userData = bud;

    // Create fixture.
    tileBody->CreateFixture(&tileFixtureDef);
}

Tile::~Tile() {
    delete bud;
}

void Tile::cracked() {
    sprite.setTextureRect(sf::IntRect((textRectX + 1) * TILE_WIDTH, textRectY * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
