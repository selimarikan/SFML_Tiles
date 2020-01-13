#include "Map.h"

Map::Map(unsigned int width, unsigned int height, unsigned int tileSize): 
    m_Width(width),
    m_Height(height),
    m_TileSize(tileSize)
{

}

void Map::AddTexture(const std::string& name, std::vector<sf::Texture*> pTexture)
{
    m_pTextures[name] = pTexture;
}

std::vector<Tile*> Map::GetTiles()
{
    return m_pTiles;
}

void Map::Build()
{
    sf::Vector2f tileSize(m_TileSize, m_TileSize);

    // Background
    for (size_t i = 0; i < m_Width; i += m_TileSize)
    {
        for (size_t j = 0; j < m_Height; j += m_TileSize)
        {
            // Create the tile
            Tile* pTile = new Tile(tileSize, m_pTextures["grass"], 0);
            //pTile->AddAnim(grassAnim);
            pTile->SetPosition(sf::Vector2f(i, j));

            m_pTiles.emplace_back(pTile);
        }
    }
}