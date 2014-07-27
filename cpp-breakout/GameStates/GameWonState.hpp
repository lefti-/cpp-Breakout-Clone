/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef GAMEWONSTATE_HPP
#define GAMEWONSTATE_HPP

#include "GameState.hpp"
#include "MainMenuState.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class StateMachine;

namespace sf {
    class RenderWindow;
}

class GameWonState : public GameState {
public:
    GameWonState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    void processEvents();
    void update(sf::Time deltaTime);
    void draw();
private:
    bool mouseOnMenuButton;
    bool mouseOnQuitButton;
    sf::Font font;
    sf::Text gratsText;
    sf::Text completionText;
    sf::Text mainMenuText;
    sf::Text quitText;
};
#endif