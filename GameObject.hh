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

    bool isColliding(const GameObject& other);
    void bounceOutOf(const GameObject& other);

    ColliderType colliderType;

    point_t pos;
    double circle_r;
    double box_len_x;
    double box_len_y;

    sf::Sprite sprite;

    double moveSpeed;

};

#endif
