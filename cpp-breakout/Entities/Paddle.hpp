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
    const int HALF_WIDTH = 64;
    const int HALF_HEIGHT = 12;
    bool m_contacting = false;
    b2BodyDef paddleBodyDef;
    b2Vec2 velocity;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f mousePos;
    bUserData* bud;
};
#endif // PADDLE_HPP