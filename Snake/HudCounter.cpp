#include "HudCounter.h"

HudCounter::HudCounter(const std::string text, sf::Vector2f position, TextAlign align,
	sf::Color fontColor, sf::Uint32 fontSize, const std::string fontName)
{
	m_Text = text;
	m_Position = position;
	m_TextAlign = align;

	m_Count = 0;
	m_CountDelta = 0;
	m_Time = sf::microseconds(100);

	auto font = FontManager::GetInstance()->GetFont(fontName);

	m_Label.setFont(*font);
	m_Label.setCharacterSize(fontSize);
	m_Label.setColor(fontColor);

	ForceUpdate();
}

HudCounter::~HudCounter()
{
}

void HudCounter::Update(sf::Time& delta)
{
	m_Ticks += delta;

	if (m_Ticks >= m_Time)
	{
		if (m_CountDelta != 0)
		{
			sf::Int8 d = m_CountDelta % m_Delta;
			if (d == 0) d = m_Delta;

			m_Count += d;
			m_CountDelta -= d;

			UpdateLabel();
		}

		m_Ticks = sf::Time::Zero;
	}
}

void HudCounter::Render(sf::RenderWindow& window)
{
	window.draw(m_Label);
}

void HudCounter::ForceUpdate()
{
	UpdateLabel();
	m_Ticks = sf::Time::Zero;
}

void HudCounter::UpdateLabel()
{
	m_Label.setString(m_Text + std::to_string(m_Count));

	auto bounds = m_Label.getLocalBounds();

	switch (m_TextAlign)
	{
	case TextAlign::Left:
		m_Label.setPosition(m_Position);
		break;
	case TextAlign::Center:
		m_Label.setPosition(sf::Vector2f(m_Position.x - (bounds.width / 2), m_Position.y));
		break;
	case TextAlign::Right:
		m_Label.setPosition(sf::Vector2f(m_Position.x - bounds.width, m_Position.y));
		break;
	}	
}
