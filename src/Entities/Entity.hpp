/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef ENTITY_HPP
#define ENTITY_HPP

// Types of fixture user data
enum entityType {
    TILE,
    BALL,
    PADDLE,
    BORDER,
    BOTTOM
};
enum tileLevel {
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL5,
    LEVEL6
};

struct bUserData {
    int entityType;
    int tileLevel;
};

class Entity { };
#endif