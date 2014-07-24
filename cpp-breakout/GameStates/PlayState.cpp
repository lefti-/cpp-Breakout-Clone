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
    player.setBodyAndSprite(world, 300, 700);
    ball.setBodyAndSprite(world);

    font.loadFromFile("data/fonts/centurygothic.ttf");
    text.setFont(font);
    text.setCharacterSize(40);
    text.setColor(sf::Color::White);
    text.setPosition(sf::Vector2f(900, 10));

    createEdgesAroundScreen();

    // Load level.
    level1.loadLevel(world, solidTiles);
    
    // Create a mouse joint for moving the player.
    b2MouseJointDef md;
    md.bodyA = borderBody;
    md.bodyB = player.playerBody;
    md.target.Set(player.playerBody->GetPosition().x, player.playerBody->GetPosition().y);
    md.collideConnected = true;
    md.maxForce = 10000.0f * player.playerBody->GetMass();
    md.dampingRatio = 0;
    md.frequencyHz = 100;
    m_mouseJoint = static_cast<b2MouseJoint*>(world->CreateJoint(&md));
    player.playerBody->SetAwake(true);

    // Restrict paddle along the x axis.
    b2PrismaticJointDef jointDef;
    b2Vec2 worldAxis(1.0f, 0.0f);
    jointDef.collideConnected = true;
    jointDef.Initialize(player.playerBody, borderBody,
                        player.playerBody->GetWorldCenter(), worldAxis);
    world->CreateJoint(&jointDef);
    
    std::cout << "World created, bodycount: " << world->GetBodyCount() << std::endl;
    std::cout << "<< PlayState initialized >>" << std::endl;
}

void PlayState::createEdgesAroundScreen() {
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
    bud->entityType = BORDER;
    borderFixtureDef.userData = bud1;

    edgeShape.Set(b2Vec2(0, 0), b2Vec2(windowSize.x / PTM_RATIO, 0));
    bottomFixtureDef.shape = &edgeShape;
    borderBody->CreateFixture(&bottomFixtureDef);

    edgeShape.Set(b2Vec2(0, 0), b2Vec2(0, windowSize.y / PTM_RATIO));
    borderFixtureDef.shape = &edgeShape;
    borderBody->CreateFixture(&borderFixtureDef);

    edgeShape.Set(b2Vec2(0, windowSize.y / PTM_RATIO), b2Vec2(windowSize.x / PTM_RATIO, windowSize.y / PTM_RATIO));
    borderFixtureDef.shape = &edgeShape;
    borderBody->CreateFixture(&borderFixtureDef);

    edgeShape.Set(b2Vec2(windowSize.x / PTM_RATIO, windowSize.y / PTM_RATIO), b2Vec2(windowSize.x / PTM_RATIO, 0));
    borderFixtureDef.shape = &edgeShape;
    borderBody->CreateFixture(&borderFixtureDef);
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
                removeSprites();
                break;

            case sf::Keyboard::Down:
                for(unsigned int i = 0; i < solidTiles.size(); i++) {
                    //if(level1.moveableTiles[i].tileBody == nullptr) {
                    solidTiles[i].flaggedToErase = true;
                    std::cout << "solidTiles[i].flaggedToErase: " << solidTiles[i].flaggedToErase << std::endl;
                    }
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
        world->Step(1.f / 60.f / subSteps, 6, 2);
        ball.update(player, deltaTime);
        player.update(m_window, deltaTime);
        sf::Vector2f mousePos(sf::Vector2f(sf::Mouse::getPosition(m_window)) / PTM_RATIO);
        m_mouseJoint->SetTarget(b2Vec2(mousePos.x, mousePos.y));
    }
    removeBodies();
}

void PlayState::removeBodies(){
    for(unsigned int i = 0; i < m_contactListener.tilesToRemove.size(); i++) {
        world->DestroyBody(m_contactListener.tilesToRemove[i]);
    }
    m_contactListener.tilesToRemove.clear();
}

void PlayState::removeSprites() {

    for(unsigned int i = 0; i < solidTiles.size(); i++) {
        //solidTiles.erase(solidTiles.begin() + i);
        std::cout << "Tile: " << i << " flagged: " << solidTiles[i].flaggedToErase << std::endl;
    }
}

void PlayState::draw() {
    m_window.clear(sf::Color(0, 0, 0));

    for(unsigned int i = 0; i < solidTiles.size(); i++) {
        solidTiles[i].draw(m_window);
    }
    ball.draw(m_window);
    player.draw(m_window);
    m_window.draw(text);

    m_window.display();
}