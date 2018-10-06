#include "PlayScreen.h"

#define ONE_WINS "White snake wins!\n\nPress enter to exit"
#define TWO_WINS "Yellow snake wins!\n\nPress enter to exit"
#define GAME_OVER "Game over!\n\nPress enter to exit"
#define PAUSED "Paused!\n\nPress enter to exit"
#define HUD_SIZE 40.f
#define GROW_LEN 3
#define RANDOM_SCORE Utils::GetRandom(25, 50)

PlayScreen::PlayScreen(bool tp)
{
	m_TwoPlayers = tp;
}

PlayScreen::~PlayScreen()
{
	delete m_SnakeOne;
	delete m_Food;
	delete m_World;
	delete m_Hud;

	if (m_TwoPlayers)
	{
		delete m_SnakeTwo;
	}
}

void PlayScreen::Init()
{
	auto sm = ScreenManager::GetInstance();

	m_World = new World(sf::FloatRect(0, HUD_SIZE, sm->ScreenSize.x, sm->ScreenSize.y - HUD_SIZE), sf::Color(50, 50, 50, 255));
	m_World->SetOpen(Utils::GetRandom(0, 1) != 0);
	m_World->LoadMap(Utils::GetRandom(0, 3));

	auto world = m_World->GetBounds();

	m_SnakeOne = new Snake(sf::Vector2f(world.left + 50, world.top + 30.0f), 3, sf::Color::White, Direction::Right, Control::Arrows);
	m_SnakeOne->Init();

	m_Food = new Food();
	m_Food->Init();

	m_Hud = new Hud(sf::FloatRect(0.f, 0.f, sm->ScreenSize.x, HUD_SIZE), sf::Color(30, 30, 30, 255));
	m_Hud->Init();

	m_ScoreOne = new HudCounter("Score: ", sf::Vector2f(10.f, 10.f), TextAlign::Left, sf::Color::White, 16, "arcade");
	m_Hud->AddElement(m_ScoreOne);

	if (m_TwoPlayers)
	{
		m_SnakeTwo = new Snake(sf::Vector2f((world.left + world.width) - 100, (world.top + world.height) - 60.0f), 3, sf::Color::Yellow, Direction::Left, Control::WSAD);
		m_SnakeTwo->Init();

		m_ScoreTwo = new HudCounter("Score: ", sf::Vector2f(sm->ScreenSize.x - 10.f, 10.f), TextAlign::Right, sf::Color::Yellow, 16, "arcade");
		m_Hud->AddElement(m_ScoreTwo);
	}
	
	m_Playing = true;
}

void PlayScreen::Input(sf::Event& events)
{
	if (events.type == sf::Event::KeyPressed)
	{
		auto sm = ScreenManager::GetInstance();

		switch (events.key.code)
		{
		case sf::Keyboard::Escape:
		{
			auto pscr = new PauseScreen(PAUSED);
			pscr->SetCancelable(true);
			sm->AddScreen(pscr);
		}
			break;

		case sf::Keyboard::BackSpace:
			sm->AddScreen(new MenuScreen());
			break;
		}
	}

	m_SnakeOne->Input(events);
	if (m_TwoPlayers) m_SnakeTwo->Input(events);
}

void PlayScreen::Update(sf::Time& time)
{
	if (!m_Playing) return;

	m_Ticks += time;

	PlayerOneUpdate(time);
	if (m_TwoPlayers) PlayerTwoUpdate(time);

	m_Food->Update(time);
	m_Hud->Update(time);

	// Tween update
	for (auto tween : m_Tweens)
		tween->Update(time);

	// Delete done tweens
	for (int i = m_Tweens.size() - 1; i >= 0; i--)
	{
		if (m_Tweens[i]->IsDone())
		{
			delete m_Tweens[i];
			m_Tweens.erase(m_Tweens.begin() + i);
		}
	}
}

void PlayScreen::Render(sf::RenderWindow& window)
{
	m_World->Render(window);
	m_Food->Render(window);
	m_SnakeOne->Render(window);
	if (m_TwoPlayers) m_SnakeTwo->Render(window);
	m_Hud->Render(window);

	// Tween render
	for (auto tween : m_Tweens)
		tween->Render(window);
}

void PlayScreen::Activated()
{
}

void PlayScreen::Deactivated()
{
}

void PlayScreen::PlayerOneUpdate(sf::Time& time)
{
	if (m_Food->Spawned() && m_World->Collides(m_SnakeOne, m_Food))
	{
		std::cout << "[DEBUG] SnakeOne head collision with food\n";
		m_Food->Eaten();

		sf::Int32 score = RANDOM_SCORE;
		m_ScoreOne->Add(score);
		m_SnakeOne->Grow(GROW_LEN);

		CreateTween(m_SnakeOne, score, sf::Color::White);
	}
	else if (m_SnakeOne->Collide(m_SnakeOne) || m_World->CollideWithObjects(m_SnakeOne))
	{
		std::cout << "[DEBUG] SnakeOne head collision\n";
		GameOver(m_TwoPlayers ? TWO_WINS : GAME_OVER);
		return;
	}
	else if (m_World->CollideWithWorld(m_SnakeOne))
	{
		std::cout << "[DEBUG] SnakeOne head collision with world\n";

		if (m_World->IsOpen())
			m_SnakeOne->SetPosition(m_World->GetTeleport(m_SnakeOne));
		else
			GameOver(m_TwoPlayers ? TWO_WINS : GAME_OVER);
		return;
	}

	m_SnakeOne->Update(time);
}

void PlayScreen::PlayerTwoUpdate(sf::Time& time)
{
	if (m_Food->Spawned() && m_World->Collides(m_SnakeTwo, m_Food))
	{
		std::cout << "[DEBUG] SnakeTwo head collision with food\n";
		m_Food->Eaten();

		sf::Int32 score = RANDOM_SCORE;
		m_ScoreTwo->Add(score);
		m_SnakeTwo->Grow(GROW_LEN);

		CreateTween(m_SnakeTwo, score, sf::Color::Yellow);
	}
	else if (m_SnakeOne->Collide(m_SnakeTwo) || m_SnakeTwo->Collide(m_SnakeTwo) || m_World->CollideWithObjects(m_SnakeTwo))
	{
		std::cout << "[DEBUG] SnakeTwo head collision, snake 1 wins!\n";
		GameOver(ONE_WINS);
		return;
	}
	else if (m_SnakeTwo->Collide(m_SnakeOne))
	{
		std::cout << "[DEBUG] SnakeOne head collision with SnakeTwo, snake 2 wins\n";
		GameOver(TWO_WINS);
		return;
	}
	else if (m_World->CollideWithWorld(m_SnakeTwo))
	{
		std::cout << "[DEBUG] SnakeTwo head collision with world\n";

		if (m_World->IsOpen())
			m_SnakeTwo->SetPosition(m_World->GetTeleport(m_SnakeTwo));
		else
			GameOver(ONE_WINS);
		return;
	}

	m_SnakeTwo->Update(time);
}

/* Metoda koñcz¹ca grê */
void PlayScreen::GameOver(const std::string text)
{
	m_Playing = false;

	ScreenManager::GetInstance()->AddScreen(new PauseScreen(text));
}

void PlayScreen::CreateTween(const Snake *snake, const sf::Uint32 str, sf::Color color)
{
	auto bounds = snake->GetBounds();
	m_Tweens.push_back(new Tween(sf::Vector2f(bounds.left, bounds.top), std::to_string(str), color));
}
