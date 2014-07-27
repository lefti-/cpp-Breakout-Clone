/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "PlayState.hpp"
#include "../GameStateMachine/StateMachine.hpp"


///////////////////////////////////////////////////////////////////////////////////
//// TO-DO:
////    * More levels.
////        - 5 levels?
////    * Level selection screen.
////        - Unlocking levels?
////    * Sounds.
////    * High-scores. (check high score when game completed.. check high score also when game over)
////    * HighScoreState.
////        - If GameOverState or GameWonState, go to HighScoreState AFTER these states (that is, if you got score worthy of high score).
////    * Restrict ball from going too horizontal or vertical!
////    * Multiply score by lives?
////    * Pressing ESC.
////        - Pauses game.
////        - Main menu.
////        - Level selection screen.
////        - Quit.
//// MAYBE:
////    * Power-ups?
////    * Options.
////        - Volume.
////        - Control scheme (Keyboard, mouse).
///////////////////////////////////////////////////////////////////////////////////


namespace GlobalVar{
    int score = 0;
    int lives = 5;
}

PlayState::PlayState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(levelNumber, machine, window, replace) {

    currentLevel = levelNumber;

    // Set gravity value.
    b2Vec2 gravity = b2Vec2(0.f, 0.f);

    // Set up the physics world.
    world = new b2World(gravity);

    // Set up a contact listener for collision detection/callbacks.
    m_contactListener = MyContactListener();
    world->SetContactListener(&m_contactListener);

    // Create paddle and ball.
    paddle.setBodyAndSprite(world, window.getSize().x / 2, window.getSize().y - paddle.HEIGHT);
    ball.setBodyAndSprite(world);

    createLifeIcons();
    createUITexts();
    createBordersAroundScreen();

    // Load level.
    level.loadLevel(world, currentLevel);

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

void PlayState::createLifeIcons() {
    // Create lives.
    if(lifeTexture.loadFromFile("data/images/life_icon2.png")) {
        lifeSprite1.setTexture(lifeTexture);
        lifeSprite2.setTexture(lifeTexture);
        lifeSprite3.setTexture(lifeTexture);
        lifeSprite4.setTexture(lifeTexture);
        lifeSprite5.setTexture(lifeTexture);
    }
    lifeSprite1.setPosition(10, 10);
    lifeSprite2.setPosition(65, 10);
    lifeSprite3.setPosition(120, 10);
    lifeSprite4.setPosition(175, 10);
    lifeSprite5.setPosition(230, 10);
}
void PlayState::createUITexts() {
    font.loadFromFile("data/fonts/centurygothic.ttf");

    fpsText.setFont(font);
    fpsText.setCharacterSize(30);
    fpsText.setColor(sf::Color::White);
    fpsText.setPosition(sf::Vector2f(10, 60));

    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(900, 10));
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

    // Bottom edge
    edgeShape.Set(b2Vec2(0, windowSize.y / PTM_RATIO), b2Vec2(windowSize.x / PTM_RATIO, windowSize.y / PTM_RATIO));
    bottomFixtureDef.shape = &edgeShape;
    borderBody->CreateFixture(&bottomFixtureDef);

    // Top edge
    edgeShape.Set(b2Vec2(0, 0), b2Vec2(windowSize.x / PTM_RATIO, 0));
    borderFixtureDef.shape = &edgeShape;
    borderBody->CreateFixture(&borderFixtureDef);

    // Left edge
    edgeShape.Set(b2Vec2(0, 0), b2Vec2(0, windowSize.y / PTM_RATIO));
    borderFixtureDef.shape = &edgeShape;
    borderBody->CreateFixture(&borderFixtureDef);

    // Right edge
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

    for(unsigned int i = 0; i < level.solidTiles.size(); i++) {
        if(level.solidTiles[i]->flaggedToErase == true) {
            level.solidTiles.erase(level.solidTiles.begin() + i);
        }
    }
}

void PlayState::checkWin() {
    // Condition for completing a level
    if(level.solidTiles.size() == 0) {
        // Condition for completing the game
        if(currentLevel == lastLevel) {
            m_next = StateMachine::build<GameWonState>(0, state_machine, m_window, true);
        }
        else {
            m_next = StateMachine::build<LevelIntroState>(currentLevel + 1, state_machine, m_window, true);
        }
    }
}

void PlayState::checkLoss() {
    // Game over condition
    if(GlobalVar::lives == 0) {
        m_next = StateMachine::build<GameOverState>(0, state_machine, m_window, true);
    }
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

            case sf::Keyboard::Space:
                if(gamePaused == true) {
                    gamePaused = false;

                    // When unpaused, center mouse position to paddle body position.
                    int playerPosX = (int)paddle.paddleBody->GetPosition().x * PTM_RATIO;
                    int playerPosY = (int)paddle.paddleBody->GetPosition().y * PTM_RATIO;
                    sf::Mouse::setPosition(sf::Vector2i(playerPosX, playerPosY), m_window);
                }
                else {
                    gamePaused = true;
                }
                break;

            case sf::Keyboard::Up:
                std::cout << "Global score: " << GlobalVar::score << std::endl;
                break;

            case sf::Keyboard::Escape:
                m_next = StateMachine::build<MainMenuState>(0, state_machine, m_window, true);
                break;

            case sf::Keyboard::Num1:
                m_next = StateMachine::build<PlayState>(1, state_machine, m_window, true);
                break;

            case sf::Keyboard::Num2:
                m_next = StateMachine::build<PlayState>(2, state_machine, m_window, true);
                break;

            case sf::Keyboard::Num3:
                m_next = StateMachine::build<PlayState>(3, state_machine, m_window, true);
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
    if(gamePaused) { }
    else {
        // Measure FPS.
        time = fpsClock.getElapsedTime();
        sf::Int64 fps = 1000000 / time.asMicroseconds();
        std::string fpsString = std::to_string(fps);
        fpsText.setString(fpsString + " fps");
        fpsClock.restart();

        checkWin();
        checkLoss();

        // Track score.
        std::string scoreString = std::to_string(GlobalVar::score);
        scoreText.setString(scoreString);

        // Physics calculations.
        world->Step(1.f / 60.f, 6, 2);

        ball.update(paddle, deltaTime);

        // Move paddle towards mouse.
        sf::Vector2f mousePos(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)) / PTM_RATIO);
        m_mouseJoint->SetTarget(b2Vec2(mousePos.x, mousePos.y));

        removeTiles();
        removeTileBodies();
    }
}

void PlayState::draw() {
    m_window.clear(sf::Color(0, 0, 0));

    for(unsigned int i = 0; i < level.solidTiles.size(); i++) {
        level.solidTiles[i]->draw(m_window);
    }

    paddle.draw(m_window);
    m_window.draw(fpsText);
    m_window.draw(scoreText);

    if(GlobalVar::lives == 5) {
        m_window.draw(lifeSprite1);
        m_window.draw(lifeSprite2);
        m_window.draw(lifeSprite3);
        m_window.draw(lifeSprite4);
        m_window.draw(lifeSprite5);
    }
    else if(GlobalVar::lives == 4) {
        m_window.draw(lifeSprite1);
        m_window.draw(lifeSprite2);
        m_window.draw(lifeSprite3);
        m_window.draw(lifeSprite4);
    }
    else if(GlobalVar::lives == 3) {
        m_window.draw(lifeSprite1);
        m_window.draw(lifeSprite2);
        m_window.draw(lifeSprite3);
    }
    else if(GlobalVar::lives == 2) {
        m_window.draw(lifeSprite1);
        m_window.draw(lifeSprite2);
    }
    else if(GlobalVar::lives == 1) {
        m_window.draw(lifeSprite1);
    }

    ball.draw(m_window);

    m_window.display();
}