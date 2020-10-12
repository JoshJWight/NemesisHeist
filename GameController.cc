#include "GameController.hh"
#include <SFML/Window/Keyboard.hpp>

GameController::GameController()
    : m_graphics(800, 600)
{
    m_player.reset(new GameObject);
    m_player->pos = point_t(0, 0);
    m_player->colliderType = CIRCLE;
    m_player->circle_r = 5;
    m_player->sprite.setTexture(m_textureBank.get("smiley.png"));
    m_player->moveSpeed = 1;

    std::shared_ptr<GameObject> obj(new GameObject);
    obj-> pos = point_t(10, 10);
    obj-> colliderType = BOX;
    obj-> box_len_x = 20;
    obj-> box_len_y = 20;
    obj->sprite.setTexture(m_textureBank.get("box.png"));

    std::shared_ptr<GameObject> obj2(new GameObject);
    obj2-> pos = point_t(-20, -20);
    obj2-> colliderType = BOX;
    obj2-> box_len_x = 20;
    obj2-> box_len_y = 20;
    obj2->sprite.setTexture(m_textureBank.get("box.png"));


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
        std::cout << "TICK" << std::endl;
        tick();

        std::this_thread::sleep_until(frameStart + frameDuration);
    }
}

void GameController::tick()
{
    //Player movement - maybe should go in a separate method or class
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        std::cout << "W" << std::endl;
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
