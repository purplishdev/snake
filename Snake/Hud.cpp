#include "Hud.h"


Hud::Hud(const sf::FloatRect hud, sf::Color color)
{
	m_Rect.setFillColor(color);
	m_Rect.setPosition(sf::Vector2f(hud.left, hud.top));
	m_Rect.setSize(sf::Vector2f(hud.width, hud.height));
}

Hud::~Hud()
{
	for (auto elem : m_Elems)
		delete elem;
	m_Elems.clear();
}

void Hud::Init()
{
}

void Hud::Reset()
{
	for (auto elem : m_Elems)
		elem->Reset();
}

void Hud::Update(sf::Time& delta)
{
	for (auto elem : m_Elems)
		elem->Update(delta);
}

void Hud::Render(sf::RenderWindow& window)
{
	window.draw(m_Rect);
	for (auto elem : m_Elems)
		elem->Render(window);
}