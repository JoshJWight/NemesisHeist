#include "GameObject.hh"
#include "Graphics.hh"
#include "TextureBank.hh"
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

class  GameController
{
public:
    GameController();
    void mainLoop();
private:

    void tick();

    Graphics m_graphics;
    std::vector<std::shared_ptr<GameObject>> m_objects;

    std::shared_ptr<GameObject> m_player;
};
