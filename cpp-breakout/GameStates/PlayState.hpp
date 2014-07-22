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
    Tile getTile(int x, int y);
    sf::FloatRect getTileBounds(int x, int y);
    void pause();
    void resume();
    void processEvents();
    void update(sf::Time deltaTime);
    void handleCollisions();
    void draw();
private:
    const float PX_TO_METER = 32.f;
    b2World* world;
    b2Body* playerBody;
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