#include "Player.hpp"


Player::Player() { }

void Player::setBodyAndSprite(b2World* world, float posX, float posY) {
    // Define a body.
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody; //this will be a dynamic body
    playerBodyDef.position.Set(posX / PX_TO_METER, posY / PX_TO_METER);

    // Use the body definition to create the actual body instance.
    playerBody = world->CreateBody(&playerBodyDef);
    playerBody->SetUserData(this);

    // Define shape.
    b2PolygonShape playerShape;
    playerShape.SetAsBox(HALF_WIDTH / PX_TO_METER, HALF_HEIGHT / PX_TO_METER);

    // Define fixture.
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &playerShape;
    playerFixtureDef.density = 10;
    //playerFixtureDef.restitution = 1;
    //playerFixtureDef.isSensor = true;
    playerFixtureDef.userData = "Player";

    // Create fixture.
    playerBody->CreateFixture(&playerFixtureDef);

    if(texture.loadFromFile("data/images/gizmo_32x32.png")) {
        sprite.setTexture(texture);
    }
    sprite.setOrigin(sf::Vector2f(HALF_WIDTH, HALF_HEIGHT));
    sprite.setPosition(sf::Vector2f(playerBody->GetPosition().x * PX_TO_METER, playerBody->GetPosition().y * PX_TO_METER));
}

void Player::startContact() {
    m_contacting = true;
}

void Player::endContact() {
    m_contacting = false;
}

void Player::update(sf::RenderWindow& window, sf::Time deltaTime) {

    sf::Vector2f mousePos(sf::Vector2f(sf::Mouse::getPosition(window)) / PX_TO_METER);

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
}

void Player::draw(sf::RenderWindow& window) {
    sprite.setPosition(sf::Vector2f(playerBody->GetPosition().x * PX_TO_METER, playerBody->GetPosition().y * PX_TO_METER));
    window.draw(sprite);

    if(m_contacting) {
        sprite.setColor(sf::Color(0, 255, 0));
    }
    else {
        sprite.setColor(sf::Color(255, 255, 255));
    }
}