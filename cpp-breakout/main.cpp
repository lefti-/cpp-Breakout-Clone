// Started on 13.7.2014.
// Breakout clone made in C++ and SFML.

// A small game engine or better state machine.
// https://github.com/eXpl0it3r/SmallGameEngine

#include "GameStates/IntroState.hpp"
#include "GameStateMachine/StateMachine.hpp"

#include <SFML/Graphics.hpp>
#include <Windows.h>


int main() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time deltaTime = sf::seconds(1.f / 60.f);

    sf::RenderWindow m_window;
    m_window.create(sf::VideoMode{1024, 768}, "Game State Machine Test v0.1");

    //m_window.setVerticalSyncEnabled(true);
    //m_window.setFramerateLimit(60);

    // Initialize the Game State engine.
    StateMachine state_machine;
    state_machine.run(StateMachine::build<IntroState>(state_machine, m_window, true));

    // Main loop.
    while(state_machine.running())
    {
        // Fixed timestep
        timeSinceLastUpdate += clock.restart();
        // This loop is executed at a constant rate.
        while(timeSinceLastUpdate > deltaTime) {
            timeSinceLastUpdate -= deltaTime;

            state_machine.nextState();
            state_machine.processEvents();
            state_machine.update(deltaTime);
        }
        // If rendering is slow, the inner loop is called multiple times before one draw() call.
        state_machine.draw();
    }
    // Leaving the scope of 'state_machine' will cleanup the engine.
}