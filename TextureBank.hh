#include <map>
#include <SFML/Graphics/Texture.hpp>

class TextureBank
{
public:
    TextureBank() {}

    sf::Texture& get(std::string filename);

private:
    std::map<std::string, sf::Texture> m_map;

};
