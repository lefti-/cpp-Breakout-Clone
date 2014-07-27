/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "Paddle.hpp"


Paddle::Paddle() { }

Paddle::~Paddle() {
    delete bud;
}

void Paddle::setBodyAndSprite(b2World* world, float posX, float posY) {
    // Define a body.
    b2BodyDef paddleBodyDef;
    paddleBodyDef.type = b2_dynamicBody;
    paddleBodyDef.position.Set(posX / PTM_RATIO, posY / PTM_RATIO);

    // Use the body definition to create the actual body instance.
    paddleBody = world->CreateBody(&paddleBodyDef);
    paddleBody->SetUserData(static_cast<Entity*>(this));

    // Define shape.
    b2PolygonShape paddleShape;
    paddleShape.SetAsBox(HALF_WIDTH / PTM_RATIO, HALF_HEIGHT / PTM_RATIO);

    // Define fixture.
    b2FixtureDef paddleFixtureDef;
    paddleFixtureDef.shape = &paddleShape;
    paddleFixtureDef.density = 1.f;
    paddleFixtureDef.friction = 0.f;
    paddleFixtureDef.restitution = 0.1f;

    // Create user data.
    bUserData* bud = new bUserData;
    bud->entityType = PADDLE;
    paddleFixtureDef.userData = bud;

    // Create fixture.
    paddleBody->CreateFixture(&paddleFixtureDef);

    if(texture.loadFromFile("data/images/paddle_96x24.png")) {
        sprite.setTexture(texture);
    }
    sprite.setOrigin(sf::Vector2f(HALF_WIDTH, HALF_HEIGHT));
    sprite.setPosition(sf::Vector2f(paddleBody->GetPosition().x * PTM_RATIO, paddleBody->GetPosition().y * PTM_RATIO));
}

void Paddle::update(sf::RenderWindow& window, sf::Time deltaTime) { }

void Paddle::draw(sf::RenderWindow& window) {
    sprite.setPosition(sf::Vector2f(paddleBody->GetPosition().x * PTM_RATIO, paddleBody->GetPosition().y * PTM_RATIO));

    window.draw(sprite); 
}