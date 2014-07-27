/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "LevelSelectState.hpp"
#include "../GameStateMachine/StateMachine.hpp"


LevelSelectState::LevelSelectState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(levelNumber, machine, window, replace) {

    // Create texts.
    selectLevel.init(80, sf::Vector2f(m_window.getSize().x / 2, 100), sf::Color(226, 90, 0), "Select Level");
    level1.init(40, sf::Vector2f(m_window.getSize().x / 2, 300), sf::Color(255, 255, 255), "Level 1");
    level2.init(40, sf::Vector2f(m_window.getSize().x / 2, 350), sf::Color(255, 255, 255), "Level 2");
    level3.init(40, sf::Vector2f(m_window.getSize().x / 2, 400), sf::Color(255, 255, 255), "Level 3");
    level4.init(40, sf::Vector2f(m_window.getSize().x / 2, 450), sf::Color(255, 255, 255), "Level 4");
    level5.init(40, sf::Vector2f(m_window.getSize().x / 2, 500), sf::Color(255, 255, 255), "Level 5");
    back.init(50, sf::Vector2f(m_window.getSize().x / 2, 700), sf::Color(255, 255, 255), "Back");
}

void LevelSelectState::processEvents() {
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

                if(level1.hovered(m_window)) {
                    m_next = StateMachine::build<LevelIntroState>(1, state_machine, m_window, true);
                }
                if(level2.hovered(m_window)) {
                    m_next = StateMachine::build<LevelIntroState>(2, state_machine, m_window, true);
                }
                if(level3.hovered(m_window)) {
                    m_next = StateMachine::build<LevelIntroState>(3, state_machine, m_window, true);
                }
                if(level4.hovered(m_window)) {
                    m_next = StateMachine::build<LevelIntroState>(4, state_machine, m_window, true);
                }
                if(level5.hovered(m_window)) {
                    m_next = StateMachine::build<LevelIntroState>(5, state_machine, m_window, true);
                }
                if(back.hovered(m_window)) {
                    m_next = StateMachine::build<MainMenuState>(0, state_machine, m_window, true);
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

void LevelSelectState::update(sf::Time deltaTime) {

    if(level1.hovered(m_window)) {
        level1.mouseOnButton = true;
    }
    else {
        level1.mouseOnButton = false;
    }
    if(level2.hovered(m_window)) {
        level2.mouseOnButton = true;
    }
    else {
        level2.mouseOnButton = false;
    }
    if(level3.hovered(m_window)) {
        level3.mouseOnButton = true;
    }
    else {
        level3.mouseOnButton = false;
    }
    if(level4.hovered(m_window)) {
        level4.mouseOnButton = true;
    }
    else {
        level4.mouseOnButton = false;
    }
    if(level5.hovered(m_window)) {
        level5.mouseOnButton = true;
    }
    else {
        level5.mouseOnButton = false;
    }
    if(back.hovered(m_window)) {
        back.mouseOnButton = true;
    }
    else {
        back.mouseOnButton = false;
    }
}

void LevelSelectState::draw() {
    m_window.clear();

    level1.setHoveredColor();
    level2.setHoveredColor();
    level3.setHoveredColor();
    level4.setHoveredColor();
    level5.setHoveredColor();
    back.setHoveredColor();

    selectLevel.draw(m_window);
    level1.draw(m_window);
    level2.draw(m_window);
    level3.draw(m_window);
    level4.draw(m_window);
    level5.draw(m_window);
    back.draw(m_window);

    m_window.display();
}