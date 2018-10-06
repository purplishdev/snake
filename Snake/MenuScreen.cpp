#include "MenuScreen.h"

MenuScreen::MenuScreen()
{
	m_CurrentItem = 1;
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::Init()
{
	auto sm = ScreenManager::GetInstance();
	auto fm = FontManager::GetInstance();
	auto font = fm->GetFont("arcade");
	
	m_Items.push_back(new sf::Text("Classic Snake", *font, 36));
	m_Items.push_back(new sf::Text("One player", *font, 24));
	m_Items.push_back(new sf::Text("Two players", *font, 24));
	m_Items.push_back(new sf::Text("Exit", *font, 24));

	for (size_t i = 0; i < m_Items.size(); i++)
	{
		auto item = m_Items.at(i);
		item->setStyle(sf::Text::Bold);
		item->setPosition(
			(sm->ScreenSize.x / 2) - (item->getLocalBounds().width / 2),
			(sm->ScreenSize.y / 3) - (item->getLocalBounds().height / 2) + 50.0f * i
		);
	}
}

void MenuScreen::Input(sf::Event& events)
{
	if (events.type == sf::Event::KeyPressed)
	{
		auto sm = ScreenManager::GetInstance();

		switch (events.key.code)
		{
		case sf::Keyboard::Up:
			if (m_CurrentItem > 1) 
				m_CurrentItem--;
			break;
		
		case sf::Keyboard::Down:
			if (m_CurrentItem < m_Items.size() - 1) 
				m_CurrentItem++;
			break;

		case sf::Keyboard::Return:

			switch (static_cast<Menu>(m_CurrentItem))
			{
			case Menu::OnePlayer:
				sm->AddScreen(new PlayScreen(false));
				break;

			case Menu::TwoPlayers:
				sm->AddScreen(new PlayScreen(true));
				break;

			case Menu::Exit:
				exit(0);
			}

			break;
		}
	}
}

void MenuScreen::Update(sf::Time& delta)
{
	for (auto item : m_Items)
		item->setColor(sf::Color::White);

	m_Items.at(m_CurrentItem)->setColor(sf::Color::Red);
}

void MenuScreen::Render(sf::RenderWindow& window)
{
	for (auto item : m_Items)
		window.draw(*item);
}

void MenuScreen::Activated()
{
}

void MenuScreen::Deactivated()
{
}
