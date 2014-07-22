#include "MyContactListener.hpp"


/// Called when two fixtures begin to touch.
void MyContactListener::BeginContact(b2Contact* contact) {

    void* typeA = contact->GetFixtureA()->GetUserData();
    void* typeB = contact->GetFixtureB()->GetUserData();

    if((typeA == "Player" && typeB == "Ball") || (typeB == "Ball" && typeA == "Player")) {
        std::cout << ">> Player and Ball started colliding." << std::endl;
    }
    if((typeA == "Tile" && typeB == "Player") || (typeB == "Player" && typeA == "Tile")) {
        std::cout << ">> Player and Tile started colliding." << std::endl;
    }
    if((typeA == "Ball" && typeB == "Tile") || (typeB == "Tile" && typeA == "Ball")) {
        std::cout << ">> Ball and Tile started colliding." << std::endl;
    }
}

/// Called when two fixtures cease to touch.
void MyContactListener::EndContact(b2Contact* contact) {
    void* typeA = contact->GetFixtureA()->GetUserData();
    void* typeB = contact->GetFixtureB()->GetUserData();

    if((typeA == "Player" && typeB == "Ball") || (typeB == "Ball" && typeA == "Player")) {
        std::cout << "<< Player and Ball stopped colliding." << std::endl;
    }
    if((typeA == "Tile" && typeB == "Player") || (typeB == "Player" && typeA == "Tile")) {
        std::cout << "<< Player and Tile stopped colliding." << std::endl;
    }
    if((typeA == "Ball" && typeB == "Tile") || (typeB == "Tile" && typeA == "Ball")) {
        std::cout << "<< Ball and Tile stopped colliding." << std::endl;
    }
}

/*
std::cout << "Contact... " << std::endl;

void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
if(bodyUserData)
static_cast<Player*>(bodyUserData)->startContact();

//check if fixture B was a ball
bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
if(bodyUserData)
static_cast<Player*>(bodyUserData)->startContact();
*/