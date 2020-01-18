#include "Game.h"
#include "AnimationHandler.h"
#include <SFML/System.hpp>

#define TILE_SIZE 32


// TODO: Create map editor from txt file
// TODO: Move map/view when close to the edges
// TODO: Create "options" class
Game::Game(const std::filesystem::path& assetsDir): m_AssetsDir(assetsDir)
{
	m_Window.create(sf::VideoMode(640, 480), "SFML Test 01");
	m_Window.setVerticalSyncEnabled(false);
	m_Window.setFramerateLimit(MAX_FRAMES);
	m_GameView.setSize(sf::Vector2f(640, 480));

    LoadTextures();

    m_pPlayer = new Character(sf::Vector2f(32.0f, 32.0f), 
        m_TextureMgr.GetTexture("c1_stand_left01"), 
        m_TextureMgr.GetTexture("c1_stand_up01"), 
        m_TextureMgr.GetTexture("c1_stand_right01"), 
        m_TextureMgr.GetTexture("c1_stand_down01"),
        m_TextureMgr.GetTexture("c1_move_left01"),
        m_TextureMgr.GetTexture("c1_move_left02"),
        m_TextureMgr.GetTexture("c1_move_up01"),
        m_TextureMgr.GetTexture("c1_move_up02"),
        m_TextureMgr.GetTexture("c1_move_right01"),
        m_TextureMgr.GetTexture("c1_move_right02"),
        m_TextureMgr.GetTexture("c1_move_down01"),
        m_TextureMgr.GetTexture("c1_move_down02"), 255);
    m_pPlayer->SetPosition(sf::Vector2f(150.0f, 150.0f));
    Animation standAnim = Animation(0, 3, 1.0f);
    Animation leftAnim = Animation(0, 1, 0.5f);
    Animation upAnim = Animation(0, 1, 0.5f);
    Animation rightAnim = Animation(0, 1, 0.5f);
    Animation downAnim = Animation(0, 1, 0.5f);
    m_pPlayer->AddAnim(standAnim);
    m_pPlayer->AddAnim(leftAnim);
    m_pPlayer->AddAnim(upAnim);
    m_pPlayer->AddAnim(rightAnim);
    m_pPlayer->AddAnim(downAnim);
}

void Game::Run()
{
    sf::Clock clock;

    // Sort sprites once by their ZLevel.
    //   This may be needed per render or maybe per level load
    m_Tiles.sort([](ITile* tile1, ITile* tile2) { return tile1->ZLevel < tile2->ZLevel; });

	while (m_Window.isOpen())
	{
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

		HandleEvents();

		Render(dt);
        //std::cout << dt << "\n"; //DBG
	}
}

void Game::HandleEvents()
{
	sf::Event event;

	while (m_Window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				m_Window.close();
				break;
			}
			case sf::Event::Resized:
			{
				m_GameView.setSize(event.size.width, event.size.height);
				m_GameView.setCenter(event.size.width / 2.0f, event.size.height / 2.0f);
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_Window.close();
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					const sf::Vector2f centerPt = m_GameView.getCenter();
					m_GameView.setCenter(centerPt.x + TILE_SIZE, centerPt.y);
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					const sf::Vector2f centerPt = m_GameView.getCenter();
					m_GameView.setCenter(centerPt.x - TILE_SIZE, centerPt.y);
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					const sf::Vector2f centerPt = m_GameView.getCenter();
					m_GameView.setCenter(centerPt.x, centerPt.y - TILE_SIZE);
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					const sf::Vector2f centerPt = m_GameView.getCenter();
					m_GameView.setCenter(centerPt.x, centerPt.y + TILE_SIZE);
                    
				}
                else if (event.key.code == sf::Keyboard::W)
                {
                    m_pPlayer->Turn(MapDirection::UP);
                    m_pPlayer->Move(MapDirection::UP);
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    m_pPlayer->Turn(MapDirection::DOWN);
                    m_pPlayer->Move(MapDirection::DOWN);
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    m_pPlayer->Turn(MapDirection::LEFT);
                    m_pPlayer->Move(MapDirection::LEFT);
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    m_pPlayer->Turn(MapDirection::RIGHT);
                    m_pPlayer->Move(MapDirection::RIGHT);
                }
				break;
			}
			/*case sf::Event::MouseWheelScrolled:
			{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					float delta = event.mouseWheelScroll.delta;
					sf::FloatRect view = m_GameView.getViewport();
					view.top
					m_GameView.setViewport()
				}
				break;
			}*/
			default:
				break;
		}
	}
}

void Game::Render(float dt)
{
	m_Window.setView(m_GameView);
	m_Window.clear();

	// Draw all objects
	for (const auto val : m_Tiles)
	{
		m_Window.draw(*val->Get(dt));
	}

	m_Window.display();
}

void Game::LoadTextures()
{
    std::cout << "Loading textures...\n";

	// Load characters
    std::filesystem::path charDir = m_AssetsDir / "characters";
    for (const auto& entry : std::filesystem::directory_iterator(charDir))
    {
        std::filesystem::path path = entry.path();
        m_TextureMgr.LoadTexture(path.filename().stem().string(), path.string());
        std::cout << "Loading texture: " << path.filename().stem() << std::endl; //DBG
    }

	// Load all the tiles
	std::filesystem::path tilesDir = m_AssetsDir / "tiles/";
    for (const auto& entry : std::filesystem::directory_iterator(tilesDir))
    {
        std::filesystem::path path = entry.path();
        m_TextureMgr.LoadTexture(path.filename().stem().string(), path.string());
        std::cout << "Loading texture: " << path.filename().stem() << std::endl; //DBG
    }

    std::cout << "Loaded textures.\n";
}

bool Game::AddObject(ITile* pObj)
{
    m_Tiles.emplace_back(pObj);
	return true;
}

// TODO: Fix this
bool Game::RemoveObject(int id)
{
    //m_DrawablesMap.remove()
	return true;
}
