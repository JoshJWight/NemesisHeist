#include "GameObject.hh"
#include <iostream>
#include "CollisionUtil.hh"

GameObject::GameObject()
{

}

double GameObject::radius()
{
    return size.x / 2.0;
}

bool GameObject::isColliding(GameObject& other)
{
    if(colliderType==CIRCLE)
    {
        if(other.colliderType==CIRCLE)
        {
            return math_util::dist(pos, other.pos) < (radius() + other.radius());
        }
        else if(other.colliderType==BOX)
        {
            return collision::boxCircle(other.pos, other.size, pos, radius());
        }
    }
    else if(colliderType==BOX)
    {
        if(other.colliderType==CIRCLE)
        {
            return collision::boxCircle(pos, size, other.pos, other.radius());
        }
        else if(other.colliderType==BOX)
        {
            //Top right, bottom left
            point_t tr1 = pos + (size / 2.0);
            point_t bl1 = pos - (size / 2.0);
            point_t tr2 = other.pos + (other.size / 2.0);
            point_t bl2 = other.pos - (other.size / 2.0);

            return (tr1.y > bl2.y && bl2.y < tr2.y && bl1.x < tr2.x && tr1.x > bl2.x);
        }
    }

    //Generally you get here if one object or other has no collider
    return false;
}

void GameObject::bounceOutOf(GameObject& other)
{
    //TODO
}
