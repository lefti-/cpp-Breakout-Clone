#include "PlayState.hpp"
#include "../GameStateMachine/StateMachine.hpp"

#define _USE_MATH_DEFINES

#include <math.h>

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(machine, window, replace) {

    // Set gravity value.
    b2Vec2 gravity = b2Vec2(0.f, 0.f);

    // Set up the physics world.
    world = new b2World(gravity);

    // Set up a contact listener for collision detection/callbacks.
    m_contactListener = MyContactListener();
    world->SetContactListener(&m_contactListener);

    // Create objects.
    player.setBodyAndSprite(world, 300, 700);
    ball.setBodyAndSprite(world);

    font.loadFromFile("data/fonts/centurygothic.ttf");
    text.setFont(font);
    text.setCharacterSize(40);
    text.setColor(sf::Color::White);
    text.setPosition(sf::Vector2f(900, 10));

    // Load level.
    level1.loadLevel(world);

    std::cout << "World created, bodycount: " << world->GetBodyCount() << std::endl;
    std::cout << "<< PlayState initialized >>" << std::endl;
}

void PlayState::pause() {
    std::cout << "PlayState  Pause" << std::endl;
}

void PlayState::resume() {
    std::cout << "PlayState  Resume" << std::endl;
}

void PlayState::processEvents() {
    sf::Event event;

    while(m_window.pollEvent(event)) {

        switch(event.type) {

        case sf::Event::Closed:
            state_machine.quit();
            break;
            
        case sf::Event::KeyPressed: {

            switch(event.key.code) {

            case sf::Keyboard::Right:
                player.movingRight = true;
                break;

            case sf::Keyboard::Left:
                player.movingLeft = true;
                break;

            case sf::Keyboard::Up:
                player.movingUp = true;
                break;

            case sf::Keyboard::Down:
                player.movingDown = true;
                break;

            case sf::Keyboard::Space:
                m_next = StateMachine::build<IntroState>(state_machine, m_window, true);
                break;

            case sf::Keyboard::Escape:
                std::cout << "Quit via Esc!" << std::endl;
                state_machine.quit();
                break;

            default:
                break;
            }
            break;
        }    

        case sf::Event::KeyReleased: {

            switch(event.key.code) {

            case sf::Keyboard::Right:
                player.movingRight = false;
                break;

            case sf::Keyboard::Left:
                player.movingLeft = false;
                break;

            case sf::Keyboard::Up:
                player.movingUp = false;
                break;

            case sf::Keyboard::Down:
                player.movingDown = false;
                break;

            default:
                break;
            }
            break;
        }

        case sf::Event::MouseButtonPressed:
        {
            switch(event.mouseButton.button) {
            case sf::Mouse::Right:
                if(ball.playerHasBall == true) {
                    ball.launch("right");
                }
                break;

            case sf::Mouse::Left:
                if(ball.playerHasBall == true) {
                    ball.launch("left");
                }
                break;

            case sf::Mouse::Middle:
                break;

            default:
                break;
            }
        }

        default:
            break;
        }
    }
}

void PlayState::update(sf::Time deltaTime) {
    // Measure FPS.
    time = fpsClock.getElapsedTime();
    sf::Int64 fps = 1000000 / time.asMicroseconds();
    std::string fpsString = std::to_string(fps);;
    text.setString(fpsString + " fps");
    fpsClock.restart();

    // Simulate a smaller timestep, to prevent tunneling on high velocities.
    float subSteps = 1;
    for(int i = 0; i < subSteps; i++) {
        world->Step(1.f / 60.f / subSteps, 1, 1);
        // Fast moving physics here.
        ball.update(player, deltaTime);
        player.update(m_window, deltaTime);
    }
    // Slow moving physics here.
}

void PlayState::draw() {
    m_window.clear(sf::Color(0, 0, 0));

    for(unsigned int i = 0; i < level1.moveableTiles.size(); i++) {
        m_window.draw(level1.moveableTiles[i].tile);
    }
    ball.draw(m_window);
    player.draw(m_window);
    m_window.draw(text);

    m_window.display();
}