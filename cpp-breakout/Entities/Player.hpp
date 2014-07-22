#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Player {
public:
    Player();
    void setBodyAndSprite(b2World* world, float posX, float posY);
    void startContact();
    void endContact();
    void update(sf::RenderWindow& window, sf::Time deltaTime);
    void draw(sf::RenderWindow& window);

    const float PX_TO_METER = 32.f;
    const int HALF_WIDTH = 16;
    const int HALF_HEIGHT = 16;
    bool movingUp, movingDown, movingLeft, movingRight = false;
    bool m_contacting = false;
    b2BodyDef playerBodyDef;
    b2Body* playerBody;
    b2Vec2 velocity;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f mousePos;
};
#endif // PLAYER_HPP