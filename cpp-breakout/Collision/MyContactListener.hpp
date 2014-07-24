#ifndef MYCONTACTLISTENER_HPP
#define MYCONTACTLISTENER_HPP

#include "../Entities/Tile.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Ball.hpp"
#include "../Entities/Entity.hpp"

#include <Box2D/Box2D.h>

#include <iostream>


class MyContactListener : public b2ContactListener {
public:
    virtual void BeginContact(b2Contact* contact) override;
    virtual void EndContact(b2Contact* contact) override;

    std::vector<b2Body*> tilesToRemove;
};
#endif