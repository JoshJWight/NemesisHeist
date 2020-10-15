#ifndef __GAME_OBJECT_HH__
#define __GAME_OBJECT_HH__

#include "MathUtil.hh"
#include <SFML/Graphics/Sprite.hpp>

enum ColliderType{
    NONE,
    CIRCLE,
    //Axis-aligned box
    BOX
};

class GameObject
{
public:
    GameObject();

    bool isColliding(GameObject& other);
    void bounceOutOf(GameObject& other);
    double radius();

    ColliderType colliderType;

    point_t pos;
    point_t size;

    sf::Sprite sprite;

    double moveSpeed;

};

#endif
