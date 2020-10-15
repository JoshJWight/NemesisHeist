#include "GameController.hh"
#include <SFML/Window/Keyboard.hpp>

GameController::GameController()
    : m_graphics(800, 600)
{
    m_player.reset(new GameObject);
    m_player->pos = point_t(0, 0);
    m_player->colliderType = CIRCLE;
    m_player->size = point_t(10, 10);
    m_player->sprite.setTexture(TextureBank::get("smiley.png"));
    m_player->moveSpeed = 1;

    std::shared_ptr<GameObject> obj(new GameObject);
    obj-> pos = point_t(10, 10);
    obj-> colliderType = BOX;
    obj-> size = point_t(20, 20);
    obj->sprite.setTexture(TextureBank::get("box.png"));

    std::shared_ptr<GameObject> obj2(new GameObject);
    obj2-> pos = point_t(-20, -30);
    obj2-> colliderType = BOX;
    obj2-> size = point_t(20, 30);
    obj2->sprite.setTexture(TextureBank::get("box.png"));


    m_objects.push_back(m_player);
    m_objects.push_back(obj);
    m_objects.push_back(obj2);
}

void GameController::mainLoop()
{
    //~60 FPS
    int msPerFrame = 16;
    std::chrono::duration<int, std::milli> frameDuration(msPerFrame);
    while(true)
    {
        auto frameStart = std::chrono::system_clock::now();
        tick();

        std::this_thread::sleep_until(frameStart + frameDuration);
    }
}

void GameController::tick()
{
    point_t mouseWorldPos = m_graphics.getMousePos();

    //Player movement - maybe should go in a separate method or class
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_player->pos.y += m_player->moveSpeed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_player->pos.y -= m_player->moveSpeed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_player->pos.x -= m_player->moveSpeed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_player->pos.x += m_player->moveSpeed;
    }

    for(int i=0; i<m_objects.size(); i++)
    {
        for(int j=0; j<m_objects.size(); j++)
        {
            if( i==j )
            {
                continue;
            }
            if(m_objects[i]->isColliding(*(m_objects[j])))
            {
                std::cout << "Object " << i << " colliding with object " << j << std::endl;
            }
        }
    }

    m_graphics.draw(m_objects);
}
