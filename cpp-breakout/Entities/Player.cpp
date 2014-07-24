#include "Player.hpp"


Player::Player() { }

void Player::setBodyAndSprite(b2World* world, float posX, float posY) {
    // Define a body.
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody; //this will be a dynamic body
    playerBodyDef.position.Set(posX / PTM_RATIO, posY / PTM_RATIO);

    // Use the body definition to create the actual body instance.
    playerBody = world->CreateBody(&playerBodyDef);
    playerBody->SetUserData(static_cast<Entity*>(this));

    // Define shape.
    b2PolygonShape playerShape;
    playerShape.SetAsBox(HALF_WIDTH / PTM_RATIO, HALF_HEIGHT / PTM_RATIO);

    // Define fixture.
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &playerShape;
    playerFixtureDef.density = 10;
    playerFixtureDef.friction = 0.4f;
    playerFixtureDef.restitution = 0.1f;

    // Create user data.
    bUserData* bud = new bUserData;
    bud->entityType = PLAYER;
    playerFixtureDef.userData = bud;

    // Create fixture.
    playerBody->CreateFixture(&playerFixtureDef);

    if(texture.loadFromFile("data/images/paddle_128x24.png")) {
        sprite.setTexture(texture);
    }
    sprite.setOrigin(sf::Vector2f(HALF_WIDTH, HALF_HEIGHT));
    sprite.setPosition(sf::Vector2f(playerBody->GetPosition().x * PTM_RATIO, playerBody->GetPosition().y * PTM_RATIO));
}

void Player::update(sf::RenderWindow& window, sf::Time deltaTime) {
/*
    sf::Vector2f mousePos(sf::Vector2f(sf::Mouse::getPosition(window)) / PTM_RATIO);

    b2Vec2 playerPos = playerBody->GetPosition();

    // Moving mouse cursor up or down from player's center.
    if(mousePos.y - playerPos.y > 0.001f || mousePos.y - playerPos.y < -0.001f) {
        velocity.y = (mousePos.y - playerPos.y) * 60;
    }
    else {
        velocity.y = 0.f;
    }
    // Moving mouse cursor left or down from player's center.
    if(mousePos.x - playerPos.x > 0.001f || mousePos.x - playerPos.x < -0.001f) {
        velocity.x = (mousePos.x - playerPos.x) * 60;
    }
    else {
        velocity.x = 0.f;
    }
    playerBody->SetLinearVelocity(velocity);
    */
}

void Player::draw(sf::RenderWindow& window) {
    sprite.setPosition(sf::Vector2f(playerBody->GetPosition().x * PTM_RATIO, playerBody->GetPosition().y * PTM_RATIO));

    window.draw(sprite); 
}