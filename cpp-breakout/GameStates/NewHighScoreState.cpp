/*
This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "NewHighscoreState.hpp"
#include "../GameStateMachine/StateMachine.hpp"


NewHighscoreState::NewHighscoreState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(levelNumber, machine, window, replace) {

    //FADE FROM BLACK.
    //FADE TO BLACK.

    font.loadFromFile("data/fonts/centurygothic.ttf");

    GlobalVar::score = 37550;
    // Create texts.
    newHighScore.init(70, sf::Vector2f((float)m_window.getSize().x / 2, 100), sf::Color(226, 90, 0), "New highscore!");
    newHighScore.text.setStyle(sf::Text::Bold);
    std::string scoreStr = std::to_string(GlobalVar::score);

    score.init(50, sf::Vector2f((float)m_window.getSize().x / 2, 250), sf::Color(255, 255, 255), scoreStr);
    enterName.init(40, sf::Vector2f(155, 400), sf::Color(255, 255, 255), "Enter your name: ");
    enterName.text.setOrigin(0, 0);
    OK.init(55, sf::Vector2f((float)m_window.getSize().x / 2, 650), sf::Color(255, 255, 255), "OK");

    nameText = sf::Text(renderString, font, 40);
    nameText.setPosition(sf::Vector2f(510, 400));
}

void NewHighscoreState::processEvents() {
    sf::Event event;

    while(m_window.pollEvent(event)) {

        switch(event.type) {

        case sf::Event::Closed:
            state_machine.quit();
            break;

        case sf::Event::KeyPressed: {

            switch(event.key.code) {

            case sf::Keyboard::Escape:
                m_next = StateMachine::build<HighscoreListState>(0, state_machine, m_window, true);
                break;

            case sf::Keyboard::Return:
                newEntry.score = GlobalVar::score;
                Highscore::writeFile(newEntry);
                m_next = StateMachine::build<HighscoreListState>(0, state_machine, m_window, true);
                break;

            default:
                break;
            }
            break;
        }

        case sf::Event::MouseButtonPressed: {
            switch(event.key.code) {

            case sf::Mouse::Button::Left: {
                if(enterName.hovered(m_window)) {
                    //m_next = StateMachine::build<MainMenuState>(0, state_machine, m_window, true);
                }
                if(OK.hovered(m_window)) {
                    newEntry.score = GlobalVar::score;
                    Highscore::writeFile(newEntry);
                    m_next = StateMachine::build<HighscoreListState>(0, state_machine, m_window, true);
                }
                break;
            }
            default:
                break;
            }
            break;
        }

        case sf::Event::TextEntered: {
            if(event.text.unicode > 32 && event.text.unicode < 128 && event.text.unicode != 8) {
                if(renderString == "_") { renderString = ""; }

                renderString += static_cast<char>(event.text.unicode);
            }
            else if(event.text.unicode == 8) {
                // Backspace, delete char.
                renderString = renderString.substr(0, renderString.length() - 1);
            }
            nameText.setString(renderString);
            newEntry.name = renderString;
            break;
        }

        default:
            break;
        }
    }
}

void NewHighscoreState::update(sf::Time deltaTime) {
    if(OK.hovered(m_window)) {
        OK.mouseOnButton = true;
    }
    else {
        OK.mouseOnButton = false;
    }
}

void NewHighscoreState::draw() {
    m_window.clear();

    OK.setHoveredColor();

    newHighScore.draw(m_window);
    score.draw(m_window);
    enterName.draw(m_window);
    m_window.draw(nameText);
    OK.draw(m_window);

    m_window.display();
}