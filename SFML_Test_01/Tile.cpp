#include "Tile.h"

void Tile::AddAnim(Animation& anim)
{
    m_AnimHandler.AddAnim(anim);
    m_AnimHandler.ChangeAnim(m_AnimHandler.GetAnimCount() - 1);
}

sf::RectangleShape* Tile::Get(float dt)
{
    int frame = m_AnimHandler.Update(dt);
    int spriteIndex = frame;
    m_Shape.setTexture(m_pTextures[spriteIndex]);

    return &m_Shape;
}

Tile::Tile(const sf::Vector2f& size, std::vector<sf::Texture*> pTextures, int zLevel)
{
    m_Shape.setSize(size);
    m_pTextures = pTextures;
    m_Shape.setTexture(pTextures[0]);
    ZLevel = zLevel;
}

void Tile::SetPosition(const sf::Vector2f& pos)
{
    m_Shape.setPosition(pos);
}
