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
    tryAgain.init(50, sf::Vector2f((float)m_window.getSize().x / 2, 300), sf::Color(226, 90, 0), "You should try again!");
    OK.init(55, sf::Vector2f((float)m_window.getSize().x / 2, 650), sf::Color(255, 255, 255), "OK");

    // Start off transparent.
    introAlpha = sf::Color(0, 0, 0, 0);

    // Fill the fader surface with black.
    introFader.setFillColor(introAlpha);
    introFader.setSize(sf::Vector2f((float)m_window.getSize().x, (float)m_window.getSize().y));
}

void GameOverState::checkHighscore() {
    // If file exists...
    if(std::ifstream("data/highscores.txt")) {
        // Read highscore.txt lines.
        std::ifstream hsFileRead("data/highscores.txt");
        std::string line;

        // Create temp struct which is used to fill vector.
        HighscoreEntry temp;

        std::vector<HighscoreEntry> entries;

        while(hsFileRead.good()) {

            std::getline(hsFileRead, line);

            // Split the line.
            // Get substring from index 0 to space and convert it to integer.
            std::string xx = line.substr(0, line.find(' '));
            int x = atoi(xx.c_str());
            temp.score = x;
            temp.name = line.substr(line.find(' ') + 1);    // Get substring from space and to the end of the string.
            entries.push_back(temp);                        // Add highscore to vector.
        }
        hsFileRead.close();

        // Sort from highest score to lowest.
        std::sort(entries.begin(), entries.end());

        if(GlobalVar::score > entries[entries.size() - 1].score) {
            m_next = StateMachine::build<NewHighscoreState>(0, state_machine, m_window, true);
        }
        else {
            m_next = StateMachine::build<MainMenuState>(0, state_machine, m_window, true);
        }
    }
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

            case sf::Keyboard::Return:
                alphaCounter = 1;
                break;

            default:
                break;
            }
            break;
        }

        case sf::Event::MouseButtonPressed: {
            switch(event.key.code) {

            case sf::Mouse::Button::Left: {
                if(OK.hovered(m_window)) {
                    alphaCounter = 1;
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
    if(OK.hovered(m_window)) {
        OK.mouseOnButton = true;
    }
    else {
        OK.mouseOnButton = false;
    }

    if(introAlpha.a < 250 && alphaCounter == 1) {
        introAlpha.a += 3;
    }
    introFader.setFillColor(introAlpha);

    if(introAlpha.a > 250) {
        checkHighscore();
    }
}

void GameOverState::draw() {
    m_window.clear();

    OK.setHoveredColor();

    gameOver.draw(m_window);
    tryAgain.draw(m_window);
    OK.draw(m_window);

    if(introAlpha.a != 255) {
        m_window.draw(introFader);
    }

    m_window.display();
}