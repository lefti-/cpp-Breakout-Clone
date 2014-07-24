#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>


class Player : public Entity {
public:
    Player();
    void setBodyAndSprite(b2World* world, float posX, float posY);
    void update(sf::RenderWindow& window, sf::Time deltaTime);
    void draw(sf::RenderWindow& window);

    b2Body* playerBody;
    bool movingUp, movingDown, movingLeft, movingRight = false;
private:
    const float PTM_RATIO = 32.f;
    const int HALF_WIDTH = 64;
    const int HALF_HEIGHT = 12;
    bool m_contacting = false;
    b2BodyDef playerBodyDef;
    b2Vec2 velocity;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f mousePos;
};
#endif // PLAYER_HPP