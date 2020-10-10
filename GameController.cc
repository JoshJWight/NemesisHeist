#include "GameController.hh"
#include <SFML/Window/Keyboard.hpp>

GameController::GameController()
    : m_graphics(800, 600)
{
    m_player.reset(new GameObject);
    m_player->pos = point_t(0, 0);
    m_player->colliderType = CIRCLE;
    m_player->circle_r = 1;
    m_player->sprite.setTexture(m_textureBank.get("smiley.png"));
    m_player->moveSpeed = 1;

    m_objects.push_back(m_player);
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

    m_graphics.draw(m_objects);
}
