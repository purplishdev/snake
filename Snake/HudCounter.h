#pragma once

#include <string>
#include "Hud.h"

class HudCounter : public IHudElement
{
public:
	HudCounter(const std::string, sf::Vector2f, TextAlign, sf::Color, sf::Uint32, const std::string);
	~HudCounter();

	void Add(sf::Int32 amount) { m_CountDelta += amount; }
	void SetValue(sf::Int32 amount) { m_Count = amount; }
	void SetTime(sf::Time time) { m_Time = time; }
	void Reset() { m_Count = 0; m_CountDelta = 0; ForceUpdate(); }
	void Update(sf::Time&);
	void Render(sf::RenderWindow&);

private:
	sf::Time m_Ticks;
	sf::Time m_Time;
	sf::Int32 m_Count;
	sf::Int32 m_CountDelta;
	const sf::Int8 m_Delta = 10;
	std::string m_Text;
	sf::Text m_Label;
	sf::Vector2f m_Position;
	TextAlign m_TextAlign;

	void ForceUpdate();
	void UpdateLabel();
	
};