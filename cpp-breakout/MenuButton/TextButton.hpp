/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef TEXTBUTTON_HPP
#define TEXTBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>


class TextButton {
public:
    TextButton();
    void init(int charSize, sf::Vector2f pos, sf::Color color, sf::String levelName);
    void draw(sf::RenderWindow& window);
    bool hovered(sf::RenderWindow& window);
    void setHoveredColor();

    bool mouseOnButton;
    sf::Text levelText;
    sf::FloatRect levelTextBounds;
private:
    sf::Font font;
    sf::FloatRect levelTextRect;
};
#endif