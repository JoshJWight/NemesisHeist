#include "TextureBank.hh"

sf::Texture& TextureBank::get(std::string filename)
{
    if(m_map.count(filename) == 0)
    {
        m_map[filename] = sf::Texture();
        m_map[filename].loadFromFile(filename);
    }

    return m_map[filename];
}
