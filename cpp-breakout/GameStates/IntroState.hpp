#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "PlayState.hpp"
#include "GameState.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>


class StateMachine;

namespace sf {
    class RenderWindow;
}

class IntroState : public GameState {
public:
    IntroState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

    void pause();
    void resume();

    void processEvents();
    void update(sf::Time deltaTime);
    void draw();
private:
    sf::Texture intro_bgTex;
    sf::Sprite intro_bg;
    sf::RectangleShape intro_fader;
    sf::Color intro_alpha;
};
#endif // INTROSTATE_HPP