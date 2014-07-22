#ifndef MYCONTACTLISTENER_HPP
#define MYCONTACTLISTENER_HPP

#include "../Entities/Tile.hpp"
#include "../Entities/Player.hpp"

#include <Box2D/Box2D.h>

#include <iostream>

class MyContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact) ;
};
#endif