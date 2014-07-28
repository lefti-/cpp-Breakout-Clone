/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "HighScoreState.hpp"
#include "../GameStateMachine/StateMachine.hpp"


HighScoreState::HighScoreState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(levelNumber, machine, window, replace) {

    // Create texts.
    highScores.init(80, sf::Vector2f((float)m_window.getSize().x / 2, 70), sf::Color(226, 90, 0), "Highscores");
    highScores.text.setStyle(sf::Text::Bold);
    score.init(50, sf::Vector2f(630 / 2, 170), sf::Color(255, 255, 255), "Score");
    score.text.setStyle(sf::Text::Underlined);
    name.init(50, sf::Vector2f(730, 170), sf::Color(255, 255, 255), "Name");
    name.text.setStyle(sf::Text::Underlined);
    mainMenu.init(50, sf::Vector2f((float)m_window.getSize().x / 2, 700), sf::Color(255, 255, 255), "Back");

    // Create highscore list.
    // Check if highscore file exists.
    if(std::ifstream("data/highscores.txt")) {
        // Read highscore.txt lines.
        std::ifstream hsFile("data/highscores.txt");
        std::string line;

        // Create temp struct which is used to fill vector.
        HighScoreEntry temp;

        std::vector<HighScoreEntry> entries(10);

        while(hsFile.good()) {

            std::getline(hsFile, line);

            // Split the line.
            // Get substring from index 0 to space and convert it to integer.
            std::string xx = line.substr(0, line.find(' '));
            int x = atoi(xx.c_str());
            temp.score = x;
            temp.name = line.substr(line.find(' ') + 1);    // Get substring from space and to the end of the string.
            entries.push_back(temp);                        // Add highscore to vector.
        }
        hsFile.close();

        std::sort(entries.begin(), entries.end());

        // Create highscore texts.
        hsEntryScore0.init(35, sf::Vector2f(500 / 2, 220), sf::Color(255, 255, 255), std::to_string(entries[0].score));
        hsEntryScore0.text.setOrigin(sf::Vector2f(0, 0));
        hsEntryName0.init(35, sf::Vector2f(660, 220), sf::Color(255, 255, 255), entries[0].name);
        hsEntryName0.text.setOrigin(sf::Vector2f(0, 0));

        hsEntryScore1.init(35, sf::Vector2f(500 / 2, 265), sf::Color(255, 255, 255), std::to_string(entries[1].score));
        hsEntryScore1.text.setOrigin(sf::Vector2f(0, 0));
        hsEntryName1.init(35, sf::Vector2f(660, 265), sf::Color(255, 255, 255), entries[1].name);
        hsEntryName1.text.setOrigin(sf::Vector2f(0, 0));

        hsEntryScore2.init(35, sf::Vector2f(500 / 2, 310), sf::Color(255, 255, 255), std::to_string(entries[2].score));
        hsEntryScore2.text.setOrigin(sf::Vector2f(0, 0));
        hsEntryName2.init(35, sf::Vector2f(660, 310), sf::Color(255, 255, 255), entries[2].name);
        hsEntryName2.text.setOrigin(sf::Vector2f(0, 0));

        hsEntryScore3.init(35, sf::Vector2f(500 / 2, 355), sf::Color(255, 255, 255), std::to_string(entries[3].score));
        hsEntryScore3.text.setOrigin(sf::Vector2f(0, 0));
        hsEntryName3.init(35, sf::Vector2f(660, 355), sf::Color(255, 255, 255), entries[3].name);
        hsEntryName3.text.setOrigin(sf::Vector2f(0, 0));

        hsEntryScore4.init(35, sf::Vector2f(500 / 2, 400), sf::Color(255, 255, 255), std::to_string(entries[4].score));
        hsEntryScore4.text.setOrigin(sf::Vector2f(0, 0));
        hsEntryName4.init(35, sf::Vector2f(660, 400), sf::Color(255, 255, 255), entries[4].name);
        hsEntryName4.text.setOrigin(sf::Vector2f(0, 0));

        hsEntryScore5.init(35, sf::Vector2f(500 / 2, 445), sf::Color(255, 255, 255), std::to_string(entries[5].score));
        hsEntryScore5.text.setOrigin(sf::Vector2f(0, 0));
        hsEntryName5.init(35, sf::Vector2f(660, 445), sf::Color(255, 255, 255), entries[5].name);
        hsEntryName5.text.setOrigin(sf::Vector2f(0, 0));

        hsEntryScore6.init(35, sf::Vector2f(500 / 2, 490), sf::Color(255, 255, 255), std::to_string(entries[6].score));
        hsEntryScore6.text.setOrigin(sf::Vector2f(0, 0));
        hsEntryName6.init(35, sf::Vector2f(660, 490), sf::Color(255, 255, 255), entries[6].name);
        hsEntryName6.text.setOrigin(sf::Vector2f(0, 0));

        hsEntryScore7.init(35, sf::Vector2f(500 / 2, 535), sf::Color(255, 255, 255), std::to_string(entries[7].score));
        hsEntryScore7.text.setOrigin(sf::Vector2f(0, 0));
        hsEntryName7.init(35, sf::Vector2f(660, 535), sf::Color(255, 255, 255), entries[7].name);
        hsEntryName7.text.setOrigin(sf::Vector2f(0, 0));

        hsEntryScore8.init(35, sf::Vector2f(500 / 2, 580), sf::Color(255, 255, 255), std::to_string(entries[8].score));
        hsEntryScore8.text.setOrigin(sf::Vector2f(0, 0));
        hsEntryName8.init(35, sf::Vector2f(660, 580), sf::Color(255, 255, 255), entries[8].name);
        hsEntryName8.text.setOrigin(sf::Vector2f(0, 0));

        hsEntryScore9.init(35, sf::Vector2f(500 / 2, 625), sf::Color(255, 255, 255), std::to_string(entries[9].score));
        hsEntryScore9.text.setOrigin(sf::Vector2f(0, 0));
        hsEntryName9.init(35, sf::Vector2f(660, 625), sf::Color(255, 255, 255), entries[9].name);
        hsEntryName9.text.setOrigin(sf::Vector2f(0, 0));
    }

}

void HighScoreState::processEvents() {
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

void HighScoreState::update(sf::Time deltaTime) {
    if(mainMenu.hovered(m_window)) {
        mainMenu.mouseOnButton = true;
    }
    else {
        mainMenu.mouseOnButton = false;
    }
}

void HighScoreState::draw() {
    m_window.clear();

    mainMenu.setHoveredColor();

    highScores.draw(m_window);
    score.draw(m_window);
    name.draw(m_window);
    mainMenu.draw(m_window);

    hsEntryScore0.draw(m_window);
    hsEntryName0.draw(m_window);

    hsEntryScore1.draw(m_window);
    hsEntryName1.draw(m_window);

    hsEntryScore2.draw(m_window);
    hsEntryName2.draw(m_window);

    hsEntryScore3.draw(m_window);
    hsEntryName3.draw(m_window);

    hsEntryScore4.draw(m_window);
    hsEntryName4.draw(m_window);

    hsEntryScore5.draw(m_window);
    hsEntryName5.draw(m_window);

    hsEntryScore6.draw(m_window);
    hsEntryName6.draw(m_window);

    hsEntryScore7.draw(m_window);
    hsEntryName7.draw(m_window);

    hsEntryScore8.draw(m_window);
    hsEntryName8.draw(m_window);

    hsEntryScore9.draw(m_window);
    hsEntryName9.draw(m_window);

    m_window.display();
}