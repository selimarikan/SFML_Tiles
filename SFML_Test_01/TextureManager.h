#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>

class TextureManager
{
private:
	std::map<std::string, sf::Texture*> m_Textures;

public:
	void LoadTexture(const std::string& name, const std::string& filename);
	sf::Texture* GetTexture(const std::string& name);
};

