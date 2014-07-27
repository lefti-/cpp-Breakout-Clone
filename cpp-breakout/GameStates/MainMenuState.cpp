/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "MainMenuState.hpp"
#include "../GameStateMachine/StateMachine.hpp"


MainMenuState::MainMenuState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(levelNumber, machine, window, replace) {

    font.loadFromFile("data/fonts/centurygothic.ttf");

    // Create texts.
    titleText.setString("Breakout");
    titleText.setFont(font);
    titleText.setCharacterSize(80); 
    titleText.setColor(sf::Color(226, 90, 0));
        
    playText.setString("Play");
    playText.setFont(font);
    playText.setCharacterSize(60);

    quitText.setString("Quit");
    quitText.setFont(font);
    quitText.setCharacterSize(60);

    // Center texts.
    sf::FloatRect titleTextRect = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(titleTextRect.left + titleTextRect.width / 2, titleTextRect.top + titleTextRect.height / 2));
    titleText.setPosition(sf::Vector2f(m_window.getSize().x / 2, 100));

    sf::FloatRect playTextRect = playText.getLocalBounds();
    playText.setOrigin(sf::Vector2f(playTextRect.left + playTextRect.width / 2, playTextRect.top + playTextRect.height / 2));
    playText.setPosition(sf::Vector2f(m_window.getSize().x / 2, 400));

    sf::FloatRect quitTextRect = quitText.getLocalBounds();
    quitText.setOrigin(sf::Vector2f(quitTextRect.left + quitTextRect.width / 2, quitTextRect.top + quitTextRect.height / 2));
    quitText.setPosition(sf::Vector2f(m_window.getSize().x / 2, 500));

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
                sf::Vector2f mousePos(sf::Vector2f(sf::Mouse::getPosition(m_window)));

                sf::FloatRect playTextBounds = playText.getGlobalBounds();
                sf::FloatRect quitTextBounds = quitText.getGlobalBounds();

                if(playTextBounds.contains(mousePos)) {
                    m_next = StateMachine::build<LevelSelectState>(1, state_machine, m_window, true);
                    GlobalVar::lives = 5;
                    GlobalVar::score = 0;
                }
                if(quitTextBounds.contains(mousePos)) {
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
    sf::Vector2f mousePos(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));

    sf::FloatRect playTextBounds = playText.getGlobalBounds();
    sf::FloatRect quitTextBounds = quitText.getGlobalBounds();

    if(playTextBounds.contains(mousePos)) {
        mouseOnPlayButton = true;
    }
    else {
        mouseOnPlayButton = false;
    }
    if(quitTextBounds.contains(mousePos)) {
        mouseOnQuitButton = true;
    }
    else {
        mouseOnQuitButton = false;
    }
}

void MainMenuState::draw() {
    m_window.clear();

    if(mouseOnPlayButton) {
        playText.setColor(sf::Color(226, 90, 0));
    }
    else {
        playText.setColor(sf::Color(255, 255, 255));
    }
    if(mouseOnQuitButton) {
        quitText.setColor(sf::Color(226, 90, 0));
    }
    else {
        quitText.setColor(sf::Color(255, 255, 255));
    }

    m_window.draw(titleText);
    m_window.draw(playText);
    m_window.draw(quitText);

    m_window.display();
}