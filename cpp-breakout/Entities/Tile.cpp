#include "Tile.hpp"
#include <iostream>


Tile::Tile(b2World* world, float posX, float posY)
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
    tileFixtureDef.density = 10.0f;
    tileFixtureDef.restitution = 0.1f;
    tileFixtureDef.friction = 0.0f;

    // Create user data.
    bUserData* bud = new bUserData;
    bud->entityType = TILE;
    tileFixtureDef.userData = bud;

    // Create fixture.
    tileBody->CreateFixture(&tileFixtureDef);
}

void Tile::draw(sf::RenderWindow& window) {
    //sprite.setPosition(sf::Vector2f(tileBody->GetPosition().x * PTM_RATIO, tileBody->GetPosition().y * PTM_RATIO));
    window.draw(sprite);
}

void Tile::saySomething() {
    std::cout << "flaggedToErase: " << flaggedToErase << std::endl;
    flaggedToErase = true;
    std::cout << "flaggedToErase: " << flaggedToErase << std::endl;
}
