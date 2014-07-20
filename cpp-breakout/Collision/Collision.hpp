/*
* Authors: Nick Koirala (original version), ahnonay (SFML2 compatibility)
*
* Collision Detection and handling class
* For SFML2.

Notice from the original version:

(c) 2009 - LittleMonkey Ltd

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.

*
* Created on 30 January 2009, 11:02
*/

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/Graphics.hpp>


namespace Collision {
    //////
    /// Test for bounding box collision using the Seperating Axis Theorem
    /// Supports scaling and rotation
    //////
    bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2);

    /// Calculates the signed depth of intersection between two rectangles.
    /// <returns>
    /// The amount of overlap between two intersecting rectangles. These
    /// depth values can be negative depending on which wides the rectangles
    /// intersect. This allows callers to determine the correct direction
    /// to push objects in order to resolve collisions.
    /// If the rectangles are not intersecting, Vector2.Zero is returned.
    /// </returns>
    sf::Vector2f getIntersectionDepth(sf::FloatRect rectA, sf::FloatRect rectB);
}
#endif