#ifndef BALL_HPP
#define BALL_HPP

#include "Paddle.hpp"
#include "Entity.hpp"

#include <SFML/Graphics.hpp>


class Ball : public Entity {
public:
    Ball();
    void launch(std::string direction);
    void setBodyAndSprite(b2World* world);
    void update(Paddle paddle, sf::Time deltaTime);
    void draw(sf::RenderWindow& window);

    bool paddleHasBall = true;
private:
    const float PTM_RATIO = 32.f;
    const int HALF_WIDTH = 12;
    const int HALF_HEIGHT = 12;
    b2BodyDef ballBodyDef;
    b2Body* ballBody;
    b2Vec2 velocity;
    sf::Texture texture;
    sf::Sprite sprite;
};
#endif