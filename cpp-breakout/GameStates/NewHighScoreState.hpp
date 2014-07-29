/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef NEWHIGHSCORESTATE_HPP
#define NEWHIGHSCORESTATE_HPP

#include "GameState.hpp"
#include "HighscoreListState.hpp"
#include "../Highscores/HighscoreEntry.hpp"
#include "../MenuButtons/TextButton.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class StateMachine;

namespace sf {
    class RenderWindow;
}

class NewHighscoreState : public GameState {
public:
    NewHighscoreState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    void processEvents();
    void update(sf::Time deltaTime);
    void draw();
private:
    int alphaCounter = 0;
    std::string renderString = "_";
    std::string scoreStr;
    sf::Font font;
    sf::Text nameText;
    sf::RectangleShape introFader;
    sf::Color introAlpha;
    TextButton newHighScore;
    TextButton score;
    TextButton enterName;
    TextButton OK;
    HighscoreEntry newEntry;
};
#endif