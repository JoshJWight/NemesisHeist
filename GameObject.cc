#include "GameObject.hh"
#include <iostream>
#include "CollisionUtil.hh"

GameObject::GameObject()
{

}

bool GameObject::isColliding(const GameObject& other)
{
    if(colliderType==CIRCLE)
    {
        if(other.colliderType==CIRCLE)
        {
            return math_util::dist(pos, other.pos) < (circle_r + other.circle_r);
        }
        else if(other.colliderType==BOX)
        {
            return collision::boxCircle(other.pos, other.box_len_x, other.box_len_y, pos, circle_r);
        }
    }
    else if(colliderType==BOX)
    {
        if(other.colliderType==CIRCLE)
        {
            return collision::boxCircle(pos, box_len_x, box_len_y, other.pos, other.circle_r);
        }
        else if(other.colliderType==BOX)
        {
            double top1 = pos.y + box_len_y / 2.0;
            double bottom1 = pos.y - box_len_y / 2.0;
            double left1 = pos.x - box_len_x / 2.0;
            double right1 = pos.x - box_len_x / 2.0;
            double top2 = other.pos.y + other.box_len_y / 2.0;
            double bottom2 = other.pos.y - other.box_len_y / 2.0;
            double left2 = other.pos.x - other.box_len_x / 2.0;
            double right2 = other.pos.x - other.box_len_x / 2.0;

            return (top1 > bottom2 && bottom1 < top2 && left1 < right2 && right1 > left2);
        }
    }

    //Generally you get here if one object or other has no collider
    return false;
}

void GameObject::bounceOutOf(const GameObject& other)
{
    //TODO
}
