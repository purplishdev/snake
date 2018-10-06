#include "PauseScreen.h"

PauseScreen::PauseScreen(const std::string text)
{
	m_Text = text;
	m_Cancelable = false;
}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::Init()
{
	auto sm = ScreenManager::GetInstance();
	auto font = FontManager::GetInstance()->GetFont("arcade");

	m_Label = sf::Text(m_Text, *font, 26);
	m_Label.setColor(sf::Color::White);
	m_Label.setStyle(sf::Text::Bold);
	m_Label.setPosition((sm->ScreenSize.x / 2) - (m_Label.getLocalBounds().width / 2),
		(sm->ScreenSize.y / 2) - (m_Label.getLocalBounds().height / 2));

	m_Rect.setFillColor(sf::Color(0, 0, 0, 150));
	m_Rect.setSize(sf::Vector2f(sm->ScreenSize.x, sm->ScreenSize.y));
}

void PauseScreen::Input(sf::Event& events)
{
	if (events.type == sf::Event::KeyPressed)
	{
		auto sm = ScreenManager::GetInstance();

		switch (events.key.code)
		{
		case sf::Keyboard::Escape:
			if (m_Cancelable) sm->DropScreen();
			break;

		case sf::Keyboard::Return:
			sm->LoadDefault();
			break;
		}
	}
}

void PauseScreen::Render(sf::RenderWindow& window)
{
	window.draw(m_Rect);
	window.draw(m_Label);
}

void PauseScreen::Activated()
{
}

void PauseScreen::Deactivated()
{
}
