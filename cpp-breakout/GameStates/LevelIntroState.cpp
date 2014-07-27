/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "LevelIntroState.hpp"
#include "../GameStateMachine/StateMachine.hpp"


LevelIntroState::LevelIntroState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(levelNumber, machine, window, replace) {

    currentLevel = levelNumber;

    font.loadFromFile("data/fonts/centurygothic.ttf");

    std::string levelNumberStr = std::to_string(currentLevel);
    std::string levelStr = "Level ";
    std::string fullStr = levelStr + levelNumberStr;

    // Create texts.
    levelNumberText.setString(fullStr);
    levelNumberText.setFont(font);
    levelNumberText.setCharacterSize(80);

    getReadyText.setString("Get ready!");
    getReadyText.setFont(font);
    getReadyText.setCharacterSize(60);

    // Center texts.
    sf::FloatRect levelNumberTextRect = levelNumberText.getLocalBounds();
    levelNumberText.setOrigin(sf::Vector2f(levelNumberTextRect.left + levelNumberTextRect.width / 2, levelNumberTextRect.top + levelNumberTextRect.height / 2));
    levelNumberText.setPosition(sf::Vector2f(m_window.getSize().x / 2, 250));

    sf::FloatRect getReadyTextRect = getReadyText.getLocalBounds();
    getReadyText.setOrigin(sf::Vector2f(getReadyTextRect.left + getReadyTextRect.width / 2, getReadyTextRect.top + getReadyTextRect.height / 2));
    getReadyText.setPosition(sf::Vector2f(m_window.getSize().x / 2, 400));

    // Set background.
    currentLevelIntro.setFillColor(sf::Color(0, 0, 0));
    currentLevelIntro.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));

    // Start off opaque (not transparent).
    introAlpha = sf::Color(0, 0, 0, 255);
    // Start off transparent.
    introAlpha2 = sf::Color(0, 0, 0, 0);

    // Fill the fader surface with black.
    introFader.setFillColor(introAlpha);
    introFader.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
    introFader2.setFillColor(introAlpha2);
    introFader2.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));

    std::cout << "<< LevelIntroState initialized >>" << std::endl;
}

void LevelIntroState::processEvents() {
    sf::Event event;

    while(m_window.pollEvent(event)) {

        switch(event.type) {

        case sf::Event::Closed:
            state_machine.quit();
            break;

        case sf::Event::KeyPressed: {

            switch(event.key.code) {

            case sf::Keyboard::Space:
                m_next = StateMachine::build<PlayState>(currentLevel, state_machine, m_window, true);
                std::cout << "Pressed SPACE in IntroState." << std::endl;
                break;

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

void LevelIntroState::update(sf::Time deltaTime) {
    if(introAlpha.a > 0) {
        // Draw fader 1.
        introAlpha.a -= 3;
    }

    if(introAlpha.a == 0) {
        // Start drawing fader 2.
        alphaCounter = 1;
    }

    if(introAlpha2.a < 250 && alphaCounter == 1) {
        introAlpha2.a += 3;
    }    
    introFader.setFillColor(introAlpha);

    introFader2.setFillColor(introAlpha2);
}

void LevelIntroState::draw() {
    m_window.clear();

    m_window.draw(currentLevelIntro);
    m_window.draw(levelNumberText);
    m_window.draw(getReadyText);

    // No need to draw the first fader if the fader background is transparent
    if(introAlpha.a != 0)
    {
        m_window.draw(introFader);
    }
    // No need to draw the second fader if the fader background is opaque
    if(introAlpha2.a != 255) {
        m_window.draw(introFader2);
    }
    if(introAlpha2.a > 250) {
        m_next = StateMachine::build<PlayState>(currentLevel, state_machine, m_window, true);
    }

    m_window.display();
}