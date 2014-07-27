/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "GameState.hpp"
#include "PlayState.hpp"
#include "LevelSelectState.hpp"
#include "LevelIntroState.hpp"
#include "../MenuButtons/TextButton.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>


class StateMachine;

namespace sf {
    class RenderWindow;
}

class MainMenuState : public GameState {
public:
    MainMenuState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    void processEvents();
    void update(sf::Time deltaTime);
    void draw();
private:
    TextButton title;
    TextButton play;
    TextButton quit;
};
#endif