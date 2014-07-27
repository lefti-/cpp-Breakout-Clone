/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef LEVELSELECTSTATE_HPP
#define LEVELSELECTSTATE_HPP

#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "../MenuButton/TextButton.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class StateMachine;

namespace sf {
    class RenderWindow;
}

class LevelSelectState : public GameState {
public:
    LevelSelectState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    void processEvents();
    void update(sf::Time deltaTime);
    void draw();
private:
    TextButton selectLevel;
    TextButton level1;
    TextButton level2;
    TextButton level3;
    TextButton level4;
    TextButton level5;
    TextButton back;
};
#endif