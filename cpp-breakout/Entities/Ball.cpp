#include "Ball.hpp"


Ball::Ball() { }

void Ball::launch(std::string direction) {
    if(direction == "left") {
        velocity.x = -1;
        velocity.y = -1;
        playerHasBall = false;
    }
    if(direction == "right") {
        velocity.x = 1;
        velocity.y = -1;
        playerHasBall = false;
    }
}

void Ball::setBodyAndSprite(b2World* world) {
    // Define a body.
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(700 / PX_TO_METER, 700 / PX_TO_METER);

    // Use the body definition to create the actual body instance.
    ballBody = world->CreateBody(&ballBodyDef);
    ballBody->SetUserData(this);

    // Define shape.
    b2PolygonShape ballShape;
    ballShape.SetAsBox(HALF_WIDTH / PX_TO_METER, HALF_HEIGHT / PX_TO_METER);

    // Define fixture.
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &ballShape;
    ballFixtureDef.density = 1;
    ballFixtureDef.restitution = 1;
    //ballFixtureDef.isSensor = true;
    ballFixtureDef.userData = "Ball";

    // Create fixture.
    ballBody->CreateFixture(&ballFixtureDef);

    if(texture.loadFromFile("data/images/ball_24x24.png")) {
        sprite.setTexture(texture);
    }
    sprite.setOrigin(sf::Vector2f(HALF_WIDTH, HALF_HEIGHT));
}

void Ball::update(Player player, sf::Time deltaTime) {
    b2Vec2 velocity(ballBody->GetLinearVelocity());
    /*
    if(playerHasBall) {
        ballBody->SetTransform(b2Vec2(player.playerBody->GetPosition().x + 50 / PX_TO_METER, player.playerBody->GetPosition().y - 50 / PX_TO_METER), 0);
        ballBodyDef.position.Set(player.playerBody->GetPosition().x * PX_TO_METER, player.playerBody->GetPosition().y);
    }
    */
    ballBody->SetLinearVelocity(velocity);
}

void Ball::draw(sf::RenderWindow& window) {
    sprite.setPosition(sf::Vector2f(ballBody->GetPosition().x * PX_TO_METER, ballBody->GetPosition().y * PX_TO_METER));
    window.draw(sprite);
}