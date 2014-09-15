/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef HIGHSCORESTATE_HPP
#define HIGHSCORESTATE_HPP

#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "../MenuButtons/TextButton.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class StateMachine;

namespace sf {
    class RenderWindow;
}

class HighscoreListState : public GameState {
public:
    HighscoreListState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    void processEvents();
    void update(sf::Time deltaTime);
    void draw();
private:

    TextButton highScores;
    TextButton score;
    TextButton name;
    TextButton mainMenu;
    TextButton hsEntryScore0;
    TextButton hsEntryName0;
    TextButton hsEntryScore1;
    TextButton hsEntryName1;
    TextButton hsEntryScore2;
    TextButton hsEntryName2;
    TextButton hsEntryScore3;
    TextButton hsEntryName3;
    TextButton hsEntryScore4;
    TextButton hsEntryName4;
    TextButton hsEntryScore5;
    TextButton hsEntryName5;
    TextButton hsEntryScore6;
    TextButton hsEntryName6;
    TextButton hsEntryScore7;
    TextButton hsEntryName7;
    TextButton hsEntryScore8;
    TextButton hsEntryName8;
    TextButton hsEntryScore9;
    TextButton hsEntryName9;
};
#endif
