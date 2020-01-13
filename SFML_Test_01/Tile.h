#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "AnimationHandler.h"
#include "ITile.h"

enum class TileType { VOID, GRASS };

class Tile : public ITile
{
public:

    void SetPosition(const sf::Vector2f& pos);
    
    void AddAnim(Animation& anim) override;
    sf::RectangleShape* Get(float dt) override;
    

    Tile(const sf::Vector2f& size, std::vector<sf::Texture*> pTextures, int zLevel);
    
    ~Tile() {}

private:
    std::vector<sf::Texture*> m_pTextures;
};

