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

    bool intersects(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2);
    void loadMap(const char* fileName, const char* tileTextureFile);
    void loadColMap(const char* fileName);

    void pause();
    void resume();

    void processEvents();

    void PlayState::findAllEqualLines();
    void PlayState::giveTilePoints();
    void update(sf::Time deltaTime);
    void draw();
private:
    const int TILESIZE = 32;
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
    std::vector<std::vector<sf::Vector2i>> map;
    std::vector<sf::Vector2i> tempMap;
    std::vector<Tile> moveableTiles;
    std::vector<Tile> tempTileVector;
    std::vector<Tile> changePlayerColorTiles;
    Player player;
    Ball ball;
    sf::IntRect tile1;
    sf::IntRect tile2;
};
#endif // PLAYSTATE_HPP