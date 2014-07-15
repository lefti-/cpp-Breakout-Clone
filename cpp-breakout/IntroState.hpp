// The header file should have a header guard to prevent multiple inclusion errors.
// header guard at start of header file
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
// end header guard at bottom of header file
#endif // INTROSTATE_HPP