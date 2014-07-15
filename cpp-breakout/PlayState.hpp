// The header file should have a header guard to prevent multiple inclusion errors.
// header guard at start of header file
#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "Tile.hpp"
#include "GameState.hpp"
#include "Player.hpp"
#include "IntroState.hpp"
#include "Collision.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


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
    void update(sf::Time deltaTime);
    void draw();
private:
    sf::Texture playerTex;
    sf::Font font;
    sf::Text text;
    sf::Time deltaTime;
    sf::Clock fpsClock;
    sf::Time time;
    sf::Texture tileTexture;
    sf::Sprite tiles;
    sf::Sprite sprite;
    std::vector<std::vector<sf::Vector2i>> map;
    std::vector<sf::Vector2i> tempMap;
    std::vector<Tile> moveableTiles;
    std::vector<Tile> changePlayerColorTiles;
    Player player;
};
// end header guard at bottom of header file
#endif // PLAYSTATE_HPP