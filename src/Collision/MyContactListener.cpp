/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


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

    if((budA->entityType == TILE && budB->entityType == BALL) || (budB->entityType == BALL && budA->entityType == TILE)) {
        Tile* tile = (Tile*)entityA;

        tile->armor -= 1;

        if(tile->armor == 1) {
            tile->cracked();
        }

        if(tile->armor == 0) {
            tile->flaggedToErase = true; // Flag the tile instance for erase.
            tilesToRemove.push_back(bodyA); // Push the tile body to a vector, which contents will be removed.

            if(budA->tileLevel == LEVEL1) {
                GlobalVar::score += 50;
            }
            else if(budA->tileLevel == LEVEL2) {
                GlobalVar::score += 100;
            }
            else if(budA->tileLevel == LEVEL3) {
                GlobalVar::score += 150;
            }
            else if(budA->tileLevel == LEVEL4) {
                GlobalVar::score += 200;
            }
            else if(budA->tileLevel == LEVEL5) {
                GlobalVar::score += 250;
            }
            else if(budA->tileLevel == LEVEL6) {
                GlobalVar::score += 300;
            }
        }
    }
    else if((budA->entityType == BOTTOM && budB->entityType == BALL) || (budB->entityType == BALL && budA->entityType == BOTTOM)) {
        Ball* ball = (Ball*)entityB;
        ball->paddleHasBall = true;
        GlobalVar::lives -= 1;
    }
}

/// Called when two fixtures cease to touch.
void MyContactListener::EndContact(b2Contact* contact) { }