// Started on 13.7.2014.
// Resources used:

// A small game engine or better state machine.
// https://github.com/eXpl0it3r/SmallGameEngine

// C++ Sfml 2.0 Made Easy Tutorial 30 - Loading Tile Maps[Hard]
// https://www.youtube.com/watch?v=NdOY8kuk4Ds&list=PLHJE4y54mpC5j_x90UkuoMZOdmmL9-_rg&index=30

// C++ Sfml 2.0 Made Easy Tutorial 39 - Tile Map Collision[Hard]
// https://www.youtube.com/watch?v=QCUZG9o4AVY&index=39&list=PLHJE4y54mpC5j_x90UkuoMZOdmmL9-_rg

// SFML Game Development
// http://books.google.fi/books?id=4oYlKBl5g24C&pg=PT510&lpg=PT510&dq=sfml+releasing+resources&source=bl&ots=1LVGlh1Zev&sig=ahMWifPoGGksj0g-YfIvQ_NSDE8&hl=fi&sa=X&ei=a8HDU6KDKMS6ygPL8oB4&ved=0CCYQ6AEwATgK#v=onepage&q&f=false

#include "GameStates/IntroState.hpp"
#include "GameStateMachine/StateMachine.hpp"

#include <SFML/Graphics.hpp>
#include <Windows.h>

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <direct.h>


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