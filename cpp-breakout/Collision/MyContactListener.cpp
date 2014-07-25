#include "MyContactListener.hpp"
#include "../GameStates/PlayState.hpp"


// Called when two fixtures begin to touch.
void MyContactListener::BeginContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureA()->GetBody();

    bUserData* budA = (bUserData*)contact->GetFixtureA()->GetUserData();
    bUserData* budB = (bUserData*)contact->GetFixtureB()->GetUserData();

    Entity* entityA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
    Entity* entityB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();

    if((budA->entityType == PADDLE && budB->entityType == BALL) || (budB->entityType == BALL && budA->entityType == PADDLE)) {

        std::cout << ">>> Paddle and ball BEGAN colliding. Velocity. " << std::endl;
    }
    else if((budA->entityType == PADDLE && budB->entityType == TILE) || (budB->entityType == TILE && budA->entityType == PADDLE)) {

        std::cout << ">>> Tile and paddle BEGAN colliding." << std::endl;
    }
    else if((budA->entityType == TILE && budB->entityType == BALL) || (budB->entityType == BALL && budA->entityType == TILE)) {
        Tile* tile = (Tile*)entityA;
        tile->flaggedToErase = true; // Flag the tile instance for erase.
        tilesToRemove.push_back(bodyA); // Push the tile body to a vector, which contents will be removed.
        
        std::cout << ">>> Ball and tile BEGAN colliding." << std::endl;
    }
    else if((budA->entityType == BOTTOM && budB->entityType == BALL) || (budB->entityType == BALL && budA->entityType == BOTTOM)) {
        Ball* ball = (Ball*)entityB;
        ball->paddleHasBall = true;
        ball->lives -= 1;

        std::cout << ">>> Ball and bottom BEGAN colliding." << std::endl;
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

    if((budA->entityType == PADDLE && budB->entityType == BALL) || (budB->entityType == BALL && budA->entityType == PADDLE)) {

        std::cout << "<<< Paddle and ball STOPPED colliding." << std::endl;
    }
    else if((budA->entityType == PADDLE && budB->entityType == TILE) || (budB->entityType == TILE && budA->entityType == PADDLE)) {

        std::cout << "<<< Tile and paddle STOPPED colliding." << std::endl;
    }
    else if((budA->entityType == TILE && budB->entityType == BALL) || (budB->entityType == BALL && budA->entityType == TILE)) {

        std::cout << "<<< Ball and tile STOPPED colliding." << std::endl;
    }
    else if((budA->entityType == BOTTOM && budB->entityType == BALL) || (budB->entityType == BALL && budA->entityType == BOTTOM)) {

        std::cout << "<<< Ball and bottom STOPPED colliding." << std::endl;
    }
}