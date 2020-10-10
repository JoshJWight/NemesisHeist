#ifndef __MATH_UTIL_HH__
#define __MATH_UTIL_HH__

#include <cmath>
#include <SFML/System/Vector2.hpp>

typedef sf::Vector2<double> point_t;

namespace math_util{
    static double dist(point_t p1, point_t p2)
    {
        double dx = p2.x - p1.x;
        double dy = p2.y - p1.y;
        return sqrt(dx * dx + dy * dy);
    }


}//end namespace math

#endif
