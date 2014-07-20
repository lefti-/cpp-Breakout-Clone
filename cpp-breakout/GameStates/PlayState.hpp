#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "GameState.hpp"
#include "IntroState.hpp"
#include "../Entities/Ball.hpp"
#include "../Entities/Tile.hpp"
#include "../Entities/Player.hpp"
#include "../Collision/Collision.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>


class StateMachine;

namespace sf {
    class RenderWindow;
    class RectangleShape;
}

class PlayState : public GameState {
public:
    PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    void loadMap(const char* fileName, const char* tileTextureFile);
    void pause();
    void resume();
    void processEvents();
    void update(sf::Time deltaTime);
    sf::Vector2f getIntersectionDepth(sf::FloatRect rectA, sf::FloatRect rectB);
    void draw();
private:
    const int TILE_WIDTH = 64;
    const int TILE_HEIGHT = 32;
    float distanceX;
    float distanceY;
    sf::Texture playerTex;
    sf::Texture ballTex;
    sf::Font font;
    sf::Text text;
    sf::Time deltaTime;
    sf::Clock fpsClock;
    sf::Time time;
    sf::Texture tileTexture;
    sf::Sprite tiles;
    sf::Sprite sprite;
    sf::Sprite tileSprite;
    sf::Vector2u windowSize;
    std::vector<std::vector<sf::Vector2i>> map;
    std::vector<sf::Vector2i> tempMap;
    std::vector<Tile> tilesNearBall;
    std::vector<Tile> moveableTiles;
    std::vector<Tile> changePlayerColorTiles;
    Player player;
    Ball ball;
};
#endif // PLAYSTATE_HPP