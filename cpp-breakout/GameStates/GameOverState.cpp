/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "GameOverState.hpp"
#include "../GameStateMachine/StateMachine.hpp"


GameOverState::GameOverState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(levelNumber, machine, window, replace) {

    font.loadFromFile("data/fonts/centurygothic.ttf");

    // Create texts.
    gameOverText.setString("Game Over");
    gameOverText.setFont(font);
    gameOverText.setStyle(sf::Text::Bold | sf::Text::Italic);
    gameOverText.setCharacterSize(80);
    gameOverText.setColor(sf::Color(226, 90, 0));

    mainMenuText.setString("Main menu");
    mainMenuText.setFont(font);
    mainMenuText.setCharacterSize(60);

    quitText.setString("Quit");
    quitText.setFont(font);
    quitText.setCharacterSize(60);

    // Center texts.
    sf::FloatRect gameOverTextRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(sf::Vector2f(gameOverTextRect.left + gameOverTextRect.width / 2, gameOverTextRect.top + gameOverTextRect.height / 2));
    gameOverText.setPosition(sf::Vector2f(m_window.getSize().x / 2, 100));

    sf::FloatRect mainMenuTextRect = mainMenuText.getLocalBounds();
    mainMenuText.setOrigin(sf::Vector2f(mainMenuTextRect.left + mainMenuTextRect.width / 2, mainMenuTextRect.top + mainMenuTextRect.height / 2));
    mainMenuText.setPosition(sf::Vector2f(m_window.getSize().x / 2, 400));

    sf::FloatRect quitTextRect = quitText.getLocalBounds();
    quitText.setOrigin(sf::Vector2f(quitTextRect.left + quitTextRect.width / 2, quitTextRect.top + quitTextRect.height / 2));
    quitText.setPosition(sf::Vector2f(m_window.getSize().x / 2, 500));

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
                sf::Vector2f mousePos(sf::Vector2f(sf::Mouse::getPosition(m_window)));

                sf::FloatRect mainMenuTextBounds = mainMenuText.getGlobalBounds();
                sf::FloatRect quitTextBounds = quitText.getGlobalBounds();

                if(mainMenuTextBounds.contains(mousePos)) {
                    m_next = StateMachine::build<MainMenuState>(0, state_machine, m_window, true);
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

void GameOverState::update(sf::Time deltaTime) {
    sf::Vector2f mousePos(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));

    sf::FloatRect mainMenuTextBounds = mainMenuText.getGlobalBounds();
    sf::FloatRect quitTextBounds = quitText.getGlobalBounds();

    if(mainMenuTextBounds.contains(mousePos)) {
        mouseOnMenuButton = true;
    }
    else {
        mouseOnMenuButton = false;
    }
    if(quitTextBounds.contains(mousePos)) {
        mouseOnQuitButton = true;
    }
    else {
        mouseOnQuitButton = false;
    }
}

void GameOverState::draw() {
    m_window.clear();

    if(mouseOnMenuButton) {
        mainMenuText.setColor(sf::Color(226, 90, 0));
    }
    else {
        mainMenuText.setColor(sf::Color(255, 255, 255));
    }
    if(mouseOnQuitButton) {
        quitText.setColor(sf::Color(226, 90, 0));
    }
    else {
        quitText.setColor(sf::Color(255, 255, 255));
    }

    m_window.draw(gameOverText);
    m_window.draw(mainMenuText);
    m_window.draw(quitText);

    m_window.display();
}