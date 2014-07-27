/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef MYCONTACTLISTENER_HPP
#define MYCONTACTLISTENER_HPP

#include "../Entities/Tile.hpp"
#include "../Entities/Paddle.hpp"
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