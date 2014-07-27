/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "MainMenuState.hpp"
#include "../GameStateMachine/StateMachine.hpp"


MainMenuState::MainMenuState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(levelNumber, machine, window, replace) {

    // Create texts.
    title.init(80, sf::Vector2f(m_window.getSize().x / 2, 100), sf::Color(226, 90, 0), "Breakout");
    play.init(60, sf::Vector2f(m_window.getSize().x / 2, 400), sf::Color(255, 255, 255), "Play");
    quit.init(60, sf::Vector2f(m_window.getSize().x / 2, 500), sf::Color(255, 255, 255), "Quit");
}

void MainMenuState::processEvents() {
    sf::Event event;

    while(m_window.pollEvent(event)) {

        switch(event.type) {

        case sf::Event::Closed:
            state_machine.quit();
            break;

        case sf::Event::KeyPressed: {

            switch(event.key.code) {

            case sf::Keyboard::Escape:
                state_machine.quit();
                break;

            default:
                break;
            }
            break;
        }

        case sf::Event::MouseButtonPressed: {
            switch(event.key.code) {

            case sf::Mouse::Button::Left: {
                if(play.hovered(m_window)) {
                    m_next = StateMachine::build<LevelIntroState>(1, state_machine, m_window, true);
                    GlobalVar::lives = 5;
                    GlobalVar::score = 0;
                }
                if(quit.hovered(m_window)) {
                    state_machine.quit();
                }
                break;
            }
            default:
                break;
            }
            break;
        }
        default:
            break;
        }
    }
}

void MainMenuState::update(sf::Time deltaTime) {
    if(play.hovered(m_window)) {
        play.mouseOnButton = true;
    }
    else {
        play.mouseOnButton = false;
    }
    if(quit.hovered(m_window)) {
        quit.mouseOnButton = true;
    }
    else {
        quit.mouseOnButton = false;
    }
}

void MainMenuState::draw() {
    m_window.clear();

    play.setHoveredColor();
    quit.setHoveredColor();

    title.draw(m_window);
    play.draw(m_window);
    quit.draw(m_window);

    m_window.display();
}