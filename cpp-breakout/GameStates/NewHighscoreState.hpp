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
    TextButton newHighScore;
    TextButton score;
    TextButton enterName;
    TextButton OK;
    std::string renderString = "_";
    sf::Font font;
    sf::Text nameText;
    HighscoreEntry newEntry;
};
#endif
