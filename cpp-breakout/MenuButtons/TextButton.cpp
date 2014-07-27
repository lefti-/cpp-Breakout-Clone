/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "TextButton.hpp"
#include <iostream>

// Error: no default constructor exists for class. That's why I have the init method.
TextButton::TextButton() { }

void TextButton::init(int charSize, sf::Vector2f pos, sf::Color color, sf::String levelName) {
    font.loadFromFile("data/fonts/centurygothic.ttf");

    text.setFont(font);
    text.setString(levelName);
    text.setCharacterSize(charSize);
    text.setColor(color);
    text.setPosition(pos);

    textRect = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2));

    textBounds = text.getGlobalBounds();
}

bool TextButton::hovered(sf::RenderWindow& window) {
    sf::Vector2f mousePos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

    if(textBounds.contains(mousePos)) {
        return true;
    }
    else {
        return false;
    }
}

void TextButton::setHoveredColor() {
    if(mouseOnButton) {
        text.setColor(sf::Color(226, 90, 0));
    }
    else {
        text.setColor(sf::Color(255, 255, 255));
    }
}

void TextButton::draw(sf::RenderWindow& window) {
    window.draw(text);
    //std::cout << "Drawing textbutton.." << std::endl;
}