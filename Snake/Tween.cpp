#include "Tween.h"

Tween::Tween(sf::Vector2f position, std::string str, sf::Color color)
{
	auto font = FontManager::GetInstance()->GetFont("arcade");

	m_Tween.setColor(color);
	m_Tween.setString(str);
	m_Tween.setPosition(position);
	m_Tween.setCharacterSize(14);
	m_Tween.setFont(*font);

	m_Alpha = 255;
}

Tween::~Tween()
{
}

void Tween::Update(sf::Time& delta)
{
	m_Alpha -= 0.2f * delta.asMilliseconds();
	m_Tween.move(0, -0.02f * delta.asMilliseconds());

	if (m_Alpha < 0) m_Alpha = 0;

	auto color = m_Tween.getColor();
	m_Tween.setColor(sf::Color(color.r, color.g, color.b, m_Alpha));
}

void Tween::Render(sf::RenderWindow& window)
{
	window.draw(m_Tween);
}