#include <memory>

#include "Game.h"
#include "Tile.h"

int main()
{
	Game game;

    //sf::Texture tex;
    //tex.loadFromFile("Assets/grass01.png");

	int tileSize = 32;
    int mapWidth = 1000;
    int mapHeight = 1000;

    std::vector<sf::Texture*> grassTextures;
    grassTextures.emplace_back(game.m_TextureMgr.GetTexture("grass01"));
    grassTextures.emplace_back(game.m_TextureMgr.GetTexture("grass02"));
    grassTextures.emplace_back(game.m_TextureMgr.GetTexture("grass03"));
    grassTextures.emplace_back(game.m_TextureMgr.GetTexture("dirt"));
    Animation grassAnim = Animation(0, 3, 2.0f);

	for (size_t i = 0; i < mapWidth; i+= tileSize)
	{
		for (size_t j = 0; j < mapHeight; j+= tileSize)
		{
            // Pick the texture

            // Create the tile
            Tile* pTile = new Tile(sf::Vector2f(tileSize, tileSize), grassTextures, 0);
            //pTile->AddAnim(grassAnim);
            pTile->SetPosition(sf::Vector2f(i, j));

            // Add tile to the list so it gets rendered
			game.AddObject(pTile); //, "rect" + std::to_string(i) + "_" + std::to_string(j)
		}
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