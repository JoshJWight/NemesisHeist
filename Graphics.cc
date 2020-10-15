#include "Graphics.hh"

#include <iostream>

Graphics::Graphics(int windowWidth, int windowHeight)
    :m_window(sf::VideoMode(windowWidth, windowHeight), "NemesisHeist"),
     m_windowSize(windowWidth, windowHeight),
     m_cameraScale(windowWidth / 200.0)
{
    m_reticleSprite.setTexture(TextureBank::get("reticle.png"));
    m_reticleSprite.setOrigin(sf::Vector2f(m_reticleSprite.getTexture()->getSize() / (unsigned int)2));
    float cursorScale = 0.4;
    m_reticleSprite.setScale(cursorScale, cursorScale);

    m_window.setMouseCursorVisible(false);
}
//TODO objects should be sorted by some kind of z-level
//That probably waits until we have a better ontology for objects
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
        //scale the size and origin of the sprite
        const sf::Texture * texture = objects[i]->sprite.getTexture();
        sf::Vector2f texSize(texture->getSize());
        sf::Vector2f scale(m_cameraScale * objects[i]->size);
        scale = math_util::elementwise_divide(scale, texSize);

        objects[i]->sprite.setScale(scale);
        //Since this ignores all transformations we don't need to do it every time.
        //GameObject could handle this
        objects[i]->sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);

        point_t cameraPos = worldToCamera(objects[i]->pos);
        objects[i]->sprite.setPosition(sf::Vector2f(cameraPos));
        m_window.draw(objects[i]->sprite);
    }

    m_window.draw(m_reticleSprite);

    m_window.display();
}

point_t Graphics::getMousePos()
{
    sf::Vector2f mouseCameraPos(sf::Mouse::getPosition(m_window));
    m_reticleSprite.setPosition(mouseCameraPos);

    return cameraToWorld(mouseCameraPos);
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


point_t Graphics::cameraToWorld(sf::Vector2f cameraPoint)
{
    point_t point(cameraPoint);
    point -= m_windowSize / 2.0;
    point.y *= -1.0;
    point /= m_cameraScale;
    point += m_cameraWorldPos;
    return point;
}
