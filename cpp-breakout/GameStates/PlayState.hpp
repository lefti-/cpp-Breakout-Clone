#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "GameState.hpp"
#include "IntroState.hpp"
#include "../Levels//Level.hpp"
#include "../Entities/Ball.hpp"
#include "../Entities/Tile.hpp"
#include "../Entities/Player.hpp"
#include "../Collision/MyContactListener.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <utility>


class StateMachine;

class PlayState : public GameState, b2ContactListener {
public:
    PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    void createEdgesAroundScreen();
    void pause();
    void resume();
    void processEvents();
    void update(sf::Time deltaTime);
    void removeBodies();
    void removeSprites();
    void draw();
private:
    const float PTM_RATIO = 32.f;
    std::vector<Tile> solidTiles;
    b2World* world;
    b2Body* borderBody;
    b2MouseJointDef md;
    b2MouseJoint* m_mouseJoint;
    sf::Vector2f depth;
    sf::Font font;
    sf::Text text;
    sf::Time deltaTime;
    sf::Clock fpsClock;
    sf::Time time;
    sf::Sprite tileSprite;
    sf::Vector2u windowSize;
    MyContactListener m_contactListener;
    Player player;
    Ball ball;
    Level level1;
};
#endif // PLAYSTATE_HPP