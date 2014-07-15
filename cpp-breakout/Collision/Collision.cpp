#include "Collision.hpp"

namespace Collision {

    bool isClamped(float mid, float A, float B) {
        if(A > B) {
            return mid >= B && mid <= A;
        }
        return mid >= A && mid <= B;
    }

    bool checkCollisionOneWay(sf::Sprite spriteA, sf::Sprite spriteB) {

        if((isClamped(spriteA.getPosition().x, spriteB.getPosition().x, spriteB.getPosition().x + spriteB.getTextureRect().width)
            || isClamped(spriteA.getPosition().x + spriteA.getTextureRect().width, spriteB.getPosition().x, spriteB.getPosition().x + spriteB.getTextureRect().width))
            && (isClamped(spriteA.getPosition().y + spriteA.getTextureRect().height, spriteB.getPosition().y + spriteB.getTextureRect().height, spriteB.getPosition().y)
            || isClamped(spriteA.getPosition().y, spriteB.getPosition().y + spriteB.getTextureRect().height, spriteB.getPosition().y)))

        {
            return true;
        }
        return false;
    }

    bool checkCollisionBothWays(sf::Sprite spriteA, sf::Sprite spriteB) {
        return checkCollisionOneWay(spriteA, spriteB) || checkCollisionOneWay(spriteB, spriteA);
    }
}