#ifndef BALL_HPP
#define BALL_HPP

#include "Player.hpp"

#include <SFML/Graphics.hpp>

#include <string>


class Ball {
public:
    Ball();
    void launch(std::string direction);
    void setBodyAndSprite(b2World* world);
    void update(Player player, sf::Time deltaTime);
    void draw(sf::RenderWindow& window);

    const float PX_TO_METER = 32.f;
    const int HALF_WIDTH = 12;
    const int HALF_HEIGHT = 12;
    bool collided = false;
    bool playerHasBall = true;
    b2BodyDef ballBodyDef;
    b2Body* ballBody;
    b2Vec2 velocity;
    sf::Texture texture;
    sf::Sprite sprite;
};
#endif