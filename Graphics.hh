#include "GameObject.hh"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Graphics
{
public:
    Graphics(int windowWidth, int windowHeight);

    void draw(std::vector<std::shared_ptr<GameObject>>& objects);



private:
    point_t worldToCamera(point_t worldPoint);
    sf::Vector2f floatVec(point_t point);

    sf::RenderWindow m_window;

    point_t m_cameraWorldPos;
    //Number of pixels per world unit
    double m_cameraScale;

    point_t m_windowSize;


};
