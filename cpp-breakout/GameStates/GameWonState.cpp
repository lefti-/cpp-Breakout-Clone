/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "GameWonState.hpp"
#include "../GameStateMachine/StateMachine.hpp"


GameWonState::GameWonState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(levelNumber, machine, window, replace) {

    font.loadFromFile("data/fonts/centurygothic.ttf");

    // Create texts.
    gratsText.setString("Congratulations !");
    gratsText.setFont(font);
    gratsText.setStyle(sf::Text::Bold | sf::Text::Italic);
    gratsText.setCharacterSize(80);
    gratsText.setColor(sf::Color(226, 90, 0));

    completionText.setString("You have completed the game!");
    completionText.setFont(font);
    completionText.setCharacterSize(50);
    completionText.setColor(sf::Color(226, 90, 0));

    mainMenuText.setString("Main menu");
    mainMenuText.setFont(font);
    mainMenuText.setCharacterSize(60);

    quitText.setString("Quit");
    quitText.setFont(font);
    quitText.setCharacterSize(60);

    // Center texts.
    sf::FloatRect gratsTextRect = gratsText.getLocalBounds();
    gratsText.setOrigin(sf::Vector2f(gratsTextRect.left + gratsTextRect.width / 2, gratsTextRect.top + gratsTextRect.height / 2));
    gratsText.setPosition(sf::Vector2f(m_window.getSize().x / 2, 100));

    sf::FloatRect completionTextRect = completionText.getLocalBounds();
    completionText.setOrigin(sf::Vector2f(completionTextRect.left + completionTextRect.width / 2, completionTextRect.top + completionTextRect.height / 2));
    completionText.setPosition(sf::Vector2f(m_window.getSize().x / 2, 300));

    sf::FloatRect mainMenuTextRect = mainMenuText.getLocalBounds();
    mainMenuText.setOrigin(sf::Vector2f(mainMenuTextRect.left + mainMenuTextRect.width / 2, mainMenuTextRect.top + mainMenuTextRect.height / 2));
    mainMenuText.setPosition(sf::Vector2f(m_window.getSize().x / 2, 500));

    sf::FloatRect quitTextRect = quitText.getLocalBounds();
    quitText.setOrigin(sf::Vector2f(quitTextRect.left + quitTextRect.width / 2, quitTextRect.top + quitTextRect.height / 2));
    quitText.setPosition(sf::Vector2f(m_window.getSize().x / 2, 600));

}

void GameWonState::processEvents() {
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

void GameWonState::update(sf::Time deltaTime) {
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

void GameWonState::draw() {
    m_window.clear();

    if(mouseOnMenuButton) {
        mainMenuText.setColor(sf::Color(0, 32, 216));
    }
    else {
        mainMenuText.setColor(sf::Color(226, 90, 0));
    }
    if(mouseOnQuitButton) {
        quitText.setColor(sf::Color(0, 32, 216));
    }
    else {
        quitText.setColor(sf::Color(226, 90, 0));
    }

    m_window.draw(gratsText);
    m_window.draw(completionText);
    m_window.draw(mainMenuText);
    m_window.draw(quitText);

    m_window.display();
}