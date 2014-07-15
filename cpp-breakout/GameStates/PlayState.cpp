#include "PlayState.hpp"
#include "../GameStateMachine/StateMachine.hpp"
#include "../Collision/Collision.hpp"

#define _USE_MATH_DEFINES

#include <math.h>


PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace)
    : GameState(machine, window, replace) {

    if(playerTex.loadFromFile("data/images/gizmo_32x32.png"))
    {
        player.sprite.setTexture(playerTex);

    }
    player.sprite.setPosition(sf::Vector2f(500, 100));

    if(ballTex.loadFromFile("data/images/ball_24x24.png")) {
        ball.sprite.setTexture(ballTex);
    }

    font.loadFromFile("data/fonts/centurygothic.ttf");

    text.setFont(font);
    text.setCharacterSize(40);
    text.setColor(sf::Color::White);
    text.setPosition(sf::Vector2f(900, 10));

    PlayState::loadMap("data/levels/Map1.txt", "data/levels/tiles.png");
                           
    // Loop through the map and set the tile position and sprites to the tiles.
    for(unsigned int i = 0; i < map.size(); i++) {
        for(unsigned int j = 0; j < map[i].size(); j++) {
            std::cout << "Map[x][y]: " << map[i][j].x << "," << map[i][j].y << std::endl;
            // Set sprites to the tiles in every grid cell which is not -1,-1.
            if(map[i][j].x != -1 && map[i][j].y != -1) {
                sprite = tiles;
                sprite.setTextureRect(sf::IntRect(map[i][j].x * 32, map[i][j].y * 32, 32, 32));
                sprite.setPosition(sf::Vector2f(j * 32.0f, i * 32.0f));
                Tile tempTile(sprite);

                // Go through the numbered grid cells and add the tiles to their appropriate vectors.
                if(map[i][j].x == 0 && map[i][j].y == 0) {
                    tempTile.armor = 1;
                    changePlayerColorTiles.push_back(tempTile);
                }
                if(map[i][j].x == 0 && map[i][j].y == 1) {
                    tempTile.armor = 1;
                    changePlayerColorTiles.push_back(tempTile);
                }
                if(map[i][j].x == 1 && map[i][j].y == 0) {
                    tempTile.armor = 2;
                    moveableTiles.push_back(tempTile);
                }
                if(map[i][j].x == 1 && map[i][j].y == 1) {
                    tempTile.armor = 2;
                    moveableTiles.push_back(tempTile);
                }

            }
        }
    }
  
    std::cout << "<< PlayState initialized >>" << std::endl;
}

void PlayState::loadMap(const char* fileName, const char* tileTextureFile) {

    std::ifstream openfile(fileName);

    // Clear the map, if loading a map after the first map.
    map.clear();

    if (openfile.is_open() && !openfile.eof()) {
        tileTexture.loadFromFile(tileTextureFile);
        tiles.setTexture(tileTexture);

        while(!openfile.eof()) {

            std::string str, value;

            // Get a line from the open map file, and save it in str
            std::getline(openfile, str);
            std::stringstream stream(str);

            // Every time we reach a space, take the values before it and store it in "value".
            while(std::getline(stream, value, ' ')) {

                if(value.length() > 0) {
                // Get the value before the comma
                std::string xx = value.substr(0, value.find(','));
                // Get the value after the comma
                std::string yy = value.substr(value.find(',') + 1);

                unsigned int x, y, i, j;

                // If there are only digits in the line, continue counting.
                for(i = 0; i < xx.length(); ++i) {
                    if(!isdigit(xx[i])) {
                        break;
                    }
                }
                // If there are only digits in the line, continue counting.
                for(j = 0; j < yy.length(); ++j) {
                    if(!isdigit(yy[j])) {
                        break;
                    }
                }

                // If i is equal to xx.length(), then  x will be equal to atoi(xx.c_str()) else, it will be equal to -1.
                x = (i == xx.length()) ? atoi(xx.c_str()) : -1;
                y = (j == yy.length()) ? atoi(yy.c_str()) : -1;

                tempMap.push_back(sf::Vector2i(x, y));
                }
            }

            if(tempMap.size() > 0){
                map.push_back(tempMap);
                tempMap.clear();
            }
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

    // Measure FPS
    time = fpsClock.getElapsedTime();
    sf::Int64 fps = 1000000 / time.asMicroseconds();
    std::string fpsString = std::to_string(fps);;
    text.setString(fpsString + " fps");
    fpsClock.restart();

    ball.update(player, deltaTime);
    player.update(m_window, deltaTime);

    // Collision Detection
    for(unsigned int i = 0; i < changePlayerColorTiles.size(); i++) {
        if(Collision::checkCollisionBothWays(player.sprite, changePlayerColorTiles[i].tile)) {
            changePlayerColorTiles.erase(changePlayerColorTiles.begin() + i);
        }
    }

    for(unsigned int i = 0; i < moveableTiles.size(); i++) {
        if(Collision::checkCollisionBothWays(ball.sprite, moveableTiles[i].tile)) {
            // Find the angle between the two sprites' centers.
            double angle = std::atan2(ball.sprite.getPosition().y - moveableTiles[i].tile.getPosition().y,
                                     ball.sprite.getPosition().x - moveableTiles[i].tile.getPosition().x) * 180 / M_PI;

            // Collision Handling
            //moveableTiles[i].tile.move(player.velocity * deltaTime.asSeconds());

            if (angle <= -45 && angle >= -135) {    // collision from TOP
                ball.velocity.y = -ball.velocity.y;
                std::cout << "Collision from TOP." << std::endl;
            }
            if(angle > 45 && angle <= 135) {        // collision from BOTTOM
                ball.velocity.y = -ball.velocity.y;
                std::cout << "Collision from BOTTOM." << std::endl;
            }
            if(angle > -45 && angle <= 45) {        // collision from RIGHT
                std::cout << "Collision from RIGHT." << std::endl;
                ball.velocity.x = -ball.velocity.x;
            }
            if((angle > 135 && angle <= 180) ||
                (angle > -180 && angle < -135)) {  // collision from LEFT
                ball.velocity.x = -ball.velocity.x;
                std::cout << "Collision from LEFT." << std::endl;
            }
        }
    }
}

void PlayState::draw() {
    m_window.clear(sf::Color(0, 0, 0));

    for(unsigned int i = 0; i < moveableTiles.size(); i++) {
        m_window.draw(moveableTiles[i].tile);
    }
    for(unsigned int i = 0; i < changePlayerColorTiles.size(); i++)
    {
        m_window.draw(changePlayerColorTiles[i].tile);
    }
    m_window.draw(ball.sprite);
    m_window.draw(player.sprite);
    m_window.draw(text);

    m_window.display();

}

