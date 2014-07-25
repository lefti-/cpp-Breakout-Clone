#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "PlayState.hpp"
#include "GameState.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>


class StateMachine;

namespace sf {
    class RenderWindow;
}

class MainMenuState : public GameState {
public:
    MainMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    void pause();
    void resume();
    void processEvents();
    void update(sf::Time deltaTime);
    void draw();
private:
    bool mouseOnPlayButton;
    bool mouseOnQuitButton;
    sf::Font font;
    sf::Text titleText;
    sf::Text playText;
    sf::Text quitText;
};
#endif // INTROSTATE_HPP