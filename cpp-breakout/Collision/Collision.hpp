#ifndef COLLISION_HPP
#define COLLISION_HPP
#include <SFML/Graphics.hpp>

namespace Collision {

    bool isClamped(float mid, float A, float B);
    bool checkCollisionOneWay(sf::Sprite spriteA, sf::Sprite spriteB);
    bool checkCollisionBothWays(sf::Sprite spriteA, sf::Sprite spriteB);
}
#endif