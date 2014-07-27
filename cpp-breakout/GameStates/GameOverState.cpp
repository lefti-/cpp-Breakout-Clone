/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "GameOverState.hpp"
#include "../GameStateMachine/StateMachine.hpp"


GameOverState::GameOverState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(levelNumber, machine, window, replace) {

    // Create texts.
    gameOver.init(80, sf::Vector2f((float)m_window.getSize().x / 2, 100), sf::Color(226, 90, 0), "Game Over");
    gameOver.text.setStyle(sf::Text::Bold);
    mainMenu.init(60, sf::Vector2f((float)m_window.getSize().x / 2, 400), sf::Color(255, 255, 255), "Main menu");
    quit.init(60, sf::Vector2f((float)m_window.getSize().x / 2, 500), sf::Color(255, 255, 255), "Quit");
}

void GameOverState::processEvents() {
    sf::Event event;

    while(m_window.pollEvent(event)) {

        switch(event.type) {

        case sf::Event::Closed:
            state_machine.quit();
            break;

        case sf::Event::KeyPressed: {

            switch(event.key.code) {

            case sf::Keyboard::Escape:
                m_next = StateMachine::build<MainMenuState>(0, state_machine, m_window, true);
                break;

            default:
                break;
            }
            break;
        }

        case sf::Event::MouseButtonPressed: {
            switch(event.key.code) {

            case sf::Mouse::Button::Left: {
                if(mainMenu.hovered(m_window)) {
                    m_next = StateMachine::build<MainMenuState>(0, state_machine, m_window, true);
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

void GameOverState::update(sf::Time deltaTime) {
    if(mainMenu.hovered(m_window)) {
        mainMenu.mouseOnButton = true;
    }
    else {
        mainMenu.mouseOnButton = false;
    }
    if(quit.hovered(m_window)) {
        quit.mouseOnButton = true;
    }
    else {
        quit.mouseOnButton = false;
    }
}

void GameOverState::draw() {
    m_window.clear();

    mainMenu.setHoveredColor();
    quit.setHoveredColor();

    gameOver.draw(m_window);
    mainMenu.draw(m_window);
    quit.draw(m_window);

    m_window.display();
}