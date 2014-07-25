#include "PlayState.hpp"
#include "../GameStateMachine/StateMachine.hpp"

#include <algorithm>
#include <math.h>

#define _USE_MATH_DEFINES


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
    paddle.setBodyAndSprite(world, 300, 700);
    ball.setBodyAndSprite(world);

    createUITexts();
    createBordersAroundScreen();

    // Load level.
    level1.loadLevel(world);

    // Create a mouse joint for moving the paddle.
    b2MouseJointDef md;
    md.bodyA = borderBody;
    md.bodyB = paddle.paddleBody;
    md.target.Set(paddle.paddleBody->GetPosition().x, paddle.paddleBody->GetPosition().y);
    md.collideConnected = true;
    md.maxForce = 10000.0f * paddle.paddleBody->GetMass();
    md.dampingRatio = 0;
    md.frequencyHz = 100;
    m_mouseJoint = static_cast<b2MouseJoint*>(world->CreateJoint(&md));
    paddle.paddleBody->SetAwake(true);

    // Restrict paddle along the x axis.
    b2PrismaticJointDef jointDef;
    b2Vec2 worldAxis(1.0f, 0.0f);
    jointDef.collideConnected = true;
    jointDef.Initialize(paddle.paddleBody, borderBody,
                        paddle.paddleBody->GetWorldCenter(), worldAxis);
    world->CreateJoint(&jointDef);
    
    std::cout << "World created, bodycount: " << world->GetBodyCount() << std::endl;
    std::cout << "<< PlayState initialized >>" << std::endl;
}

void PlayState::createUITexts() {
    font.loadFromFile("data/fonts/centurygothic.ttf");

    fpsText.setFont(font);
    fpsText.setCharacterSize(30);
    fpsText.setColor(sf::Color::White);
    fpsText.setPosition(sf::Vector2f(930, 10));

    livesText.setFont(font);
    livesText.setCharacterSize(30);
    livesText.setColor(sf::Color::White);
    livesText.setPosition(sf::Vector2f(10, 10));
}

void PlayState::createBordersAroundScreen() {
    sf::Vector2u windowSize = m_window.getSize();
    
    b2BodyDef borderBodyDef;
    borderBodyDef.position.Set(0, 0);
    borderBody = world->CreateBody(&borderBodyDef);

    b2EdgeShape edgeShape;

    b2FixtureDef bottomFixtureDef;
    bUserData* bud = new bUserData;
    bud->entityType = BOTTOM;
    bottomFixtureDef.userData = bud;

    b2FixtureDef borderFixtureDef;
    bUserData* bud1 = new bUserData;
    bud1->entityType = BORDER;
    borderFixtureDef.userData = bud1;

    edgeShape.Set(b2Vec2(0, windowSize.y / PTM_RATIO), b2Vec2(windowSize.x / PTM_RATIO, windowSize.y / PTM_RATIO));
    bottomFixtureDef.shape = &edgeShape;
    borderBody->CreateFixture(&bottomFixtureDef);

    edgeShape.Set(b2Vec2(0, 0), b2Vec2(windowSize.x / PTM_RATIO, 0));
    borderFixtureDef.shape = &edgeShape;
    borderBody->CreateFixture(&borderFixtureDef);

    edgeShape.Set(b2Vec2(0, 0), b2Vec2(0, windowSize.y / PTM_RATIO));
    borderFixtureDef.shape = &edgeShape;
    borderBody->CreateFixture(&borderFixtureDef);


    edgeShape.Set(b2Vec2(windowSize.x / PTM_RATIO, windowSize.y / PTM_RATIO), b2Vec2(windowSize.x / PTM_RATIO, 0));
    borderFixtureDef.shape = &edgeShape;
    borderBody->CreateFixture(&borderFixtureDef);
}

void PlayState::removeTileBodies() {
    for(unsigned int i = 0; i < m_contactListener.tilesToRemove.size(); i++) {
        world->DestroyBody(m_contactListener.tilesToRemove[i]);
    }
    m_contactListener.tilesToRemove.clear();
}

void PlayState::removeTiles() {

    for(unsigned int i = 0; i < level1.solidTiles.size(); i++) {
        if(level1.solidTiles[i]->flaggedToErase == true) {
            level1.solidTiles.erase(level1.solidTiles.begin() + i);
        }
    }
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
                paddle.movingRight = true;
                break;

            case sf::Keyboard::Left:
                std::cout << level1.solidTiles.size() << std::endl;
                break;

            case sf::Keyboard::Up:
                break;

            case sf::Keyboard::Down:
                for(unsigned int i = 0; i < level1.solidTiles.size(); i++) {
                    std::cout << "solidTiles.size(): " << level1.solidTiles.size() << std::endl;
                    }
                break;

            case sf::Keyboard::Space:
                break;

            case sf::Keyboard::Escape:
                m_next = StateMachine::build<MainMenuState>(state_machine, m_window, true);
                break;

            default:
                break;
            }
            break;
        }    

        case sf::Event::KeyReleased: {

            switch(event.key.code) {

            case sf::Keyboard::Right:
                paddle.movingRight = false;
                break;

            case sf::Keyboard::Left:
                paddle.movingLeft = false;
                break;

            case sf::Keyboard::Up:
                paddle.movingUp = false;
                break;

            case sf::Keyboard::Down:
                paddle.movingDown = false;
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
                if(ball.paddleHasBall == true) {
                    ball.launch("right");
                }
                break;

            case sf::Mouse::Left:
                if(ball.paddleHasBall == true) {
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
    fpsText.setString(fpsString + " fps");
    fpsClock.restart();

    // Track lives.
    std::string livesString = std::to_string(ball.lives);
    livesText.setString("Lives: " + livesString);

    // Simulate a smaller timestep, to prevent tunneling on high velocities.
    float subSteps = 1;
    for(int i = 0; i < subSteps; i++) {
        world->Step(1.f / 60.f / subSteps, 6, 2);
        ball.update(paddle, deltaTime);
        paddle.update(m_window, deltaTime);
        sf::Vector2f mousePos(sf::Vector2f(sf::Mouse::getPosition(m_window)) / PTM_RATIO);
        m_mouseJoint->SetTarget(b2Vec2(mousePos.x, mousePos.y));
    }
    removeTiles();
    removeTileBodies();
}



void PlayState::draw() {
    m_window.clear(sf::Color(0, 0, 0));

    for(unsigned int i = 0; i < level1.solidTiles.size(); i++) {
        level1.solidTiles[i]->draw(m_window);
    }

    ball.draw(m_window);
    paddle.draw(m_window);
    m_window.draw(fpsText);
    m_window.draw(livesText);

    m_window.display();
}