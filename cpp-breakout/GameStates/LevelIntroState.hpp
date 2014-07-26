#ifndef LEVELINTROSTATE_HPP
#define LEVELINTROSTATE_HPP

#include "PlayState.hpp"
#include "GameState.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>


class StateMachine;

namespace sf {
    class RenderWindow;
}

class LevelIntroState : public GameState {
public:
    LevelIntroState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    void processEvents();
    void update(sf::Time deltaTime);
    void draw();
private:
    int currentLevel;
    int alphaCounter = 0;
    sf::Texture intro_bgTex;
    sf::Sprite intro_bg;
    sf::RectangleShape introFader;
    sf::RectangleShape introFader2;
    sf::RectangleShape currentLevelIntro;
    sf::Color introAlpha;
    sf::Color introAlpha2;
    sf::Font font;
    sf::Text levelNumberText;
    sf::Text getReadyText;
};
#endif // INTROSTATE_HPP