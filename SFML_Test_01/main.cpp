#include <memory>

#include "Game.h"
#include "Tile.h"


void LoadTextures()
{

}

int main()
{
	Game game("Assets/");


	unsigned int tileSize = 32;
    unsigned int mapWidth = 1000;
    unsigned int mapHeight = 1000;
    
    Map map = Map(mapWidth, mapHeight, tileSize);
    
    std::vector<sf::Texture*> grassTextures;
    grassTextures.emplace_back(game.m_TextureMgr.GetTexture("grass01"));
    grassTextures.emplace_back(game.m_TextureMgr.GetTexture("grass02"));
    grassTextures.emplace_back(game.m_TextureMgr.GetTexture("grass03"));
    grassTextures.emplace_back(game.m_TextureMgr.GetTexture("dirt"));
    map.AddTexture("grass", grassTextures);
    map.Build();

    //Animation grassAnim = Animation(0, 3, 2.0f);
    
    // Add tiles to the list so it gets rendered
    for (auto& tile: map.GetTiles())
    {
        game.AddObject(tile);
    }
    

    // Test wheat
    std::vector<sf::Texture*> wheatTextures;
    wheatTextures.emplace_back(game.m_TextureMgr.GetTexture("wheat_stage1"));
    wheatTextures.emplace_back(game.m_TextureMgr.GetTexture("wheat_stage2"));
    wheatTextures.emplace_back(game.m_TextureMgr.GetTexture("wheat_stage3"));
    wheatTextures.emplace_back(game.m_TextureMgr.GetTexture("wheat_stage4"));
    Tile* pTile = new Tile(sf::Vector2f(tileSize, tileSize), wheatTextures, 127);
    pTile->SetPosition(sf::Vector2f(128.0f, 128.0f));
    Animation growAnim = Animation(0, 3, 0.5f);
    pTile->AddAnim(growAnim);
    game.AddObject(pTile); //, "wheat"


    // Test rock
    std::vector<sf::Texture*> rockTextures;
    rockTextures.emplace_back(game.m_TextureMgr.GetTexture("rock"));
    rockTextures.emplace_back(game.m_TextureMgr.GetTexture("rock_moss"));
    Tile* pTile2 = new Tile(sf::Vector2f(tileSize, tileSize), rockTextures, 127);
    Animation rockAnim = Animation(0, 1, 1.0f);
    //pTile2->AddAnim(rockAnim);
    pTile2->SetPosition(sf::Vector2f(196.0f, 196.0f));
    game.AddObject(pTile2); //, "wheat"


    game.AddObject(game.m_pPlayer); //, "ThePlayer"
	game.Run();
	


	return 0;
}