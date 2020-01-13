#include "TextureManager.h"

void TextureManager::LoadTexture(const std::string& name, const std::string& filename)
{
    sf::Texture* pTex = new sf::Texture();
    pTex->loadFromFile(filename);
	
	m_Textures[name] = pTex;
}

sf::Texture* TextureManager::GetTexture(const std::string& name)
{
    return m_Textures.at(name);
}
