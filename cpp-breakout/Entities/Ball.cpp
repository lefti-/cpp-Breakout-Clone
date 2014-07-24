#include "Ball.hpp"


Ball::Ball() { }

void Ball::launch(std::string direction) {
    if(direction == "left") {
        ballBody->ApplyLinearImpulse(b2Vec2(-20, -20), ballBodyDef.position, true);
        playerHasBall = false;
    }
    if(direction == "right") {
        ballBody->ApplyLinearImpulse(b2Vec2(20, -20), ballBodyDef.position, true);
        playerHasBall = false;
    }
}

void Ball::setBodyAndSprite(b2World* world) {
    // Define a body.
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(700 / PTM_RATIO, 700 / PTM_RATIO);

    // Use the body definition to create the actual body instance.
    ballBody = world->CreateBody(&ballBodyDef);
    ballBody->SetUserData(static_cast<Entity*>(this));

    // Define shape.
    b2CircleShape ballShape;
    ballShape.m_radius = 12.0 / PTM_RATIO;

    // Define fixture.
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &ballShape;
    ballFixtureDef.density = 1.f;
    ballFixtureDef.friction = 0.f;
    ballFixtureDef.restitution = 1.f;

    // Create user data.
    bUserData* bud = new bUserData;
    bud->entityType = BALL;
    ballFixtureDef.userData = bud;

    // Create fixture.
    ballBody->CreateFixture(&ballFixtureDef);

    if(texture.loadFromFile("data/images/ball_24x24.png")) {
        sprite.setTexture(texture);
    }
    sprite.setOrigin(sf::Vector2f(HALF_WIDTH, HALF_HEIGHT));
}

void Ball::update(Player player, sf::Time deltaTime) {
    if(playerHasBall) {
        ballBody->SetTransform(b2Vec2(player.playerBody->GetPosition().x + 1 / PTM_RATIO, player.playerBody->GetPosition().y - 50 / PTM_RATIO), 0);
    }
    
    int maxSpeed = 30;
    b2Vec2 velocity = ballBody->GetLinearVelocity();
    float32 speed = velocity.Length();

    // If the ball is too fast, apply linear damping to indirectly affect the velocity of the ball.
    // If the velocity is too large, increase the linear damping so it will eventually slow down.
    if(speed > maxSpeed) {
        ballBody->SetLinearDamping(0.5);
    }
    else if(speed < maxSpeed) {
        ballBody->SetLinearDamping(0.0);
    }
}

void Ball::draw(sf::RenderWindow& window) {
    sprite.setPosition(sf::Vector2f(ballBody->GetPosition().x * PTM_RATIO, ballBody->GetPosition().y * PTM_RATIO));
    window.draw(sprite);
}