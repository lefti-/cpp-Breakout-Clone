#include "Level.hpp"


Level::Level() { }

void Level::loadLevel(b2World* world) {

    Level::loadMap("data/levels/Map1.txt", "data/levels/tiles.png");

    // Loop through the map and set the tile position and sprites to the tiles.
    for(unsigned int i = 0; i < map.size(); i++) {
        for(unsigned int j = 0; j < map[i].size(); j++) {
            // Set sprites to the tiles in every grid cell which is not -1,-1.
            if(map[i][j].x != -1 && map[i][j].y != -1) {
                Tile tempTile;
                tempTile.setBody(world, j * TILE_WIDTH, i * TILE_HEIGHT);
                tempTile.tile = tiles;
                tempTile.tile.setOrigin(sf::Vector2f(HALF_WIDTH, HALF_HEIGHT));
                tempTile.tile.setTextureRect(sf::IntRect(map[i][j].x * TILE_WIDTH, map[i][j].y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
                tempTile.tile.setPosition(sf::Vector2f(tempTile.tileBody->GetPosition().x * PX_TO_METER, tempTile.tileBody->GetPosition().y * PX_TO_METER));

                
                // Go through the numbered grid cells and add the tiles to their appropriate containers.
                if(map[i][j].x == 0 && map[i][j].y == 0) {
                    tempTile.armor = 1;
                    moveableTiles.push_back(tempTile);
                }
                if(map[i][j].x == 0 && map[i][j].y == 1) {
                    tempTile.armor = 1;
                    moveableTiles.push_back(tempTile);
                }
                if(map[i][j].x == 0 && map[i][j].y == 2) {
                    tempTile.armor = 1;
                    moveableTiles.push_back(tempTile);
                }
                if(map[i][j].x == 1 && map[i][j].y == 0) {
                    tempTile.armor = 4;
                    moveableTiles.push_back(tempTile);
                }
                if(map[i][j].x == 1 && map[i][j].y == 1) {
                    tempTile.armor = 2;
                    moveableTiles.push_back(tempTile);
                }
                if(map[i][j].x == 1 && map[i][j].y == 2) {
                    tempTile.armor = 2;
                    moveableTiles.push_back(tempTile);
                }
                
            }
        }
    }
}

void Level::loadMap(const char* fileName, const char* tileTextureFile) {

    std::ifstream openfile(fileName);

    // Clear the map, if loading a map after the first map.
    map.clear();

    if(openfile.is_open() && !openfile.eof()) {
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
                    std::string xx = value.substr(0, value.find('.'));
                    // Get the value after the comma
                    std::string yy = value.substr(value.find('.') + 1);

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

            if(tempMap.size() > 0) {
                map.push_back(tempMap);
                tempMap.clear();
            }
        }
    }
}
