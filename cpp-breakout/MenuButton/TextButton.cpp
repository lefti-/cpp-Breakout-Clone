/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "TextButton.hpp"
#include <iostream>

// Error: no default constructor exists for class. That's why I have the init method.
TextButton::TextButton() { }

void TextButton::init(int charSize, sf::Vector2f pos, sf::Color color, sf::String levelName) {
    font.loadFromFile("data/fonts/centurygothic.ttf");

    levelText.setFont(font);
    levelText.setString(levelName);
    levelText.setCharacterSize(charSize);
    levelText.setColor(color);
    levelText.setPosition(pos);

    levelTextRect = levelText.getLocalBounds();
    levelText.setOrigin(sf::Vector2f(levelTextRect.left + levelTextRect.width / 2, levelTextRect.top + levelTextRect.height / 2));

    levelTextBounds = levelText.getGlobalBounds();
}

bool TextButton::hovered(sf::RenderWindow& window) {
    sf::Vector2f mousePos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

    if(levelTextBounds.contains(mousePos)) {
        return true;
    }
    else {
        return false;
    }
}

void TextButton::setHoveredColor() {
    if(mouseOnButton) {
        levelText.setColor(sf::Color(226, 90, 0));
    }
    else {
        levelText.setColor(sf::Color(255, 255, 255));
    }
}

void TextButton::draw(sf::RenderWindow& window) {
    window.draw(levelText);
    //std::cout << "Drawing textbutton.." << std::endl;
}