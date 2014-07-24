#include "MyContactListener.hpp"


// Called when two fixtures begin to touch.
void MyContactListener::BeginContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureA()->GetBody();

    bUserData* budA = (bUserData*)contact->GetFixtureA()->GetUserData();
    bUserData* budB = (bUserData*)contact->GetFixtureB()->GetUserData();

    Entity* entityA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
    Entity* entityB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();

    if((budA->entityType == PLAYER && budB->entityType == BALL) || (budB->entityType == BALL && budA->entityType == PLAYER)) {
        
        std::cout << ">>> Player and ball BEGAN colliding. Velocity. " << std::endl;
    }
    else if((budA->entityType == PLAYER && budB->entityType == TILE) || (budB->entityType == TILE && budA->entityType == PLAYER)) {

        std::cout << ">>> Tile and player BEGAN colliding." << std::endl;
    }
    else if((budA->entityType == TILE && budB->entityType == BALL) || (budB->entityType == BALL && budA->entityType == TILE)) {
        Tile* tile = (Tile*)entityA;
        std::cout << "tile->flaggedToErase: " << tile->flaggedToErase << std::endl;
        tile->flaggedToErase = true; // HERE IS THE BUG !! Doesn't work on objects which are in a vector, their variables get reset to originals
        tilesToRemove.push_back(bodyA);
        std::cout << "tile->flaggedToErase: " << tile->flaggedToErase << std::endl;
        
        std::cout << ">>> Ball and tile BEGAN colliding." << std::endl;
    }
}

/// Called when two fixtures cease to touch.
void MyContactListener::EndContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureA()->GetBody();

    bUserData* budA = (bUserData*)contact->GetFixtureA()->GetUserData();
    bUserData* budB = (bUserData*)contact->GetFixtureB()->GetUserData();

    Entity* entityA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
    Entity* entityB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();

    if((budA->entityType == PLAYER && budB->entityType == BALL) || (budB->entityType == BALL && budA->entityType == PLAYER)) {

        std::cout << "<<< Player and ball STOPPED colliding." << std::endl;
    }
    else if((budA->entityType == PLAYER && budB->entityType == TILE) || (budB->entityType == TILE && budA->entityType == PLAYER)) {

        std::cout << "<<< Tile and player STOPPED colliding." << std::endl;
    }
    else if((budA->entityType == TILE && budB->entityType == BALL) || (budB->entityType == BALL && budA->entityType == TILE)) {

        std::cout << "<<< Ball and tile STOPPED colliding." << std::endl;
    }
}