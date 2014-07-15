#include "IntroState.hpp"
#include "../GameStateMachine/StateMachine.hpp"


IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(machine, window, replace) {
    intro_bgTex.loadFromFile("C:/Users/Harry/Documents/Visual Studio 2013/Projects/cpp SFML test/Game State Machine/data/images/episode_2_unlocked.png");
    intro_bg.setTexture(intro_bgTex, true);

    // Start off opaque
    intro_alpha = sf::Color(0, 0, 0, 255);

    // Fill the fader surface with black
    intro_fader.setFillColor(intro_alpha);
    intro_fader.setSize(static_cast<sf::Vector2f>(intro_bgTex.getSize()));

    std::cout << "<< IntroState initialized >>" << std::endl;
}

void IntroState::pause() {
    std::cout << "IntroState Pause" << std::endl;
}

void IntroState::resume() {
    std::cout << "IntroState Resume" << std::endl;
}

void IntroState::processEvents() {
    sf::Event event;

    while(m_window.pollEvent(event)) {

        switch(event.type) {

        case sf::Event::Closed:
            state_machine.quit();
            break;

        case sf::Event::KeyPressed: {

            switch(event.key.code) {

            case sf::Keyboard::Space:
                m_next = StateMachine::build<PlayState>(state_machine, m_window, true);
                std::cout << "Pressed SPACE in IntroState." << std::endl;
                break;

            case sf::Keyboard::Up:
                std::cout << "Pressed UP arrow." << std::endl;
                break;

            case sf::Keyboard::Escape:
                state_machine.quit();
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

void IntroState::update(sf::Time deltaTime) {
    if(intro_alpha.a != 0)
        intro_alpha.a--;

    intro_fader.setFillColor(intro_alpha);
}

void IntroState::draw() {
    // Clear the previous drawing
    m_window.clear();

    m_window.draw(intro_bg);

    // No need to draw if the background is transparent
    if(intro_alpha.a != 0)
    {
        m_window.draw(intro_fader);
    }

    m_window.display();
}