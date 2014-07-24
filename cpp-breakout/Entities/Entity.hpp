#ifndef ENTITY_HPP
#define ENTITY_HPP

// Types of fixture user data
enum entityType {
    TILE,
    BALL,
    PLAYER,
    BORDER,
    BOTTOM
};

struct bUserData {
    int entityType;
};

class Entity { };
#endif