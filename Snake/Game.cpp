#include "Game.h"

Game::Game(sf::String name, sf::Uint32 width, sf::Uint32 height)
	: m_Name(name)
{
	m_Window.create(sf::VideoMode(width, height), m_Name, sf::Style::Titlebar | sf::Style::Close);
	m_Window.setFramerateLimit(18);
	m_Window.setKeyRepeatEnabled(false);

	m_ScreenManager = ScreenManager::GetInstance();
	m_FontManager = FontManager::GetInstance();
}

Game::~Game()
{
}

/* G³ówna metoda z pêtl¹ gry, wywo³uje metody Input,Update,Render */
void Game::Start()
{
	Init();

	sf::Time delta;
	sf::Clock clock;
	sf::Uint32 fps = 0;

	sf::Event events;
	while (m_Window.isOpen())
	{
		while (m_Window.pollEvent(events))
		{
			if (events.type == sf::Event::Closed)
				m_Window.close();

			Input(events);
		}

		delta = clock.restart();

		Update(delta);
		Render(m_Window);

		++fps;
	}
}

/* Metoda inicjuj¹ca, inicjowanie menad¿erów */
void Game::Init()
{
	m_FontManager->LoadFont("arcade", "./arcade.ttf");

	m_ScreenManager->ScreenSize = m_Window.getSize();
	m_ScreenManager->LoadDefault();
}

/* Metoda przekazuj¹ca naciœniêcia klawiszy do ekranów (IScreen) */
void Game::Input(sf::Event& events)
{
	m_ScreenManager->GetTopScreen()->Input(events);
}

/* Metoda uaktualniaj¹ca ekrany (IScreen) */
void Game::Update(sf::Time& time)
{
	m_ScreenManager->GetTopScreen()->Update(time);
}

/* Metoda renderuj¹ca ekrany (IScreen) */
void Game::Render(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	for (auto screen : m_ScreenManager->GetScreens())
		screen->Render(window);
	window.display();
}
