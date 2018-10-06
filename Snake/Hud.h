#pragma once

#include <vector>
#include "IEntity.h"
#include "FontManager.h"
#include "IHudElement.h"

enum class TextAlign
{
	Left,
	Center,
	Right
};

class Hud : public IEntity
{
public:
	Hud(const sf::FloatRect, sf::Color);
	virtual ~Hud();

	void AddElement(IHudElement* elem) { m_Elems.push_back(elem); }
	void Reset();

	virtual void Init() override;
	virtual void Input(sf::Event&) override {};
	virtual void Update(sf::Time&) override;
	virtual void Render(sf::RenderWindow&) override;
	virtual const sf::FloatRect GetBounds() const override
	{
		return m_Rect.getGlobalBounds();
	}

private:

	sf::RectangleShape m_Rect;
	std::vector< IHudElement* > m_Elems;

};

