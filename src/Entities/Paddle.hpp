/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "Entity.hpp"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>


class Paddle : public Entity {
public:
    Paddle();
    ~Paddle();
    void setBodyAndSprite(b2World* world, float posX, float posY);
    void update(sf::RenderWindow& window, sf::Time deltaTime);
    void draw(sf::RenderWindow& window);

    const int HEIGHT = 24;
    b2Body* paddleBody;
private:
    const float PTM_RATIO = 32.f;
    const float HALF_WIDTH = 48.f;
    const float HALF_HEIGHT = 12.f;
    bool m_contacting = false;
    b2BodyDef paddleBodyDef;
    b2Vec2 velocity;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f mousePos;
    bUserData* bud;
};
#endif