#include "Graphics.hh"

#include <iostream>

Graphics::Graphics(int windowWidth, int windowHeight)
    :m_window(sf::VideoMode(windowWidth, windowHeight), "NemesisHeist"),
     m_windowSize(windowWidth, windowHeight),
     m_cameraScale(windowWidth / 50.0)
{

}
//TODO should objects be sorted by some kind of z-level
void Graphics::draw(std::vector<std::shared_ptr<GameObject>>& objects)
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            m_window.close();
            exit(0);
        }
    }

    m_window.clear();

    for(int i=0; i<objects.size(); i++)
    {
        //TODO handle sprite origins (probably not handled here)
        //TODO scale the size of the sprite
        point_t cameraPos = worldToCamera(objects[i]->pos);
        objects[i]->sprite.setPosition(floatVec(cameraPos));
        m_window.draw(objects[i]->sprite);
    }

    m_window.display();
}

point_t Graphics::worldToCamera(point_t worldPoint)
{
    point_t worldDiff = worldPoint - m_cameraWorldPos;
    point_t cameraDiff = worldDiff * m_cameraScale;
    //In SFML the +y axis is downwards on the screen, but my world space
    //has +y as the up direction, because I find it easier to think in
    cameraDiff.y *= -1.0;
    return cameraDiff + (m_windowSize / 2.0);
}

sf::Vector2f Graphics::floatVec(point_t point)
{
    return sf::Vector2f((float)point.x, (float)point.y);
}
