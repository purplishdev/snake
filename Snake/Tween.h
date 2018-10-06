#pragma once

#include "FontManager.h"
#include "IEntity.h"

class Tween : public IEntity
{
public:
	Tween(sf::Vector2f, std::string, sf::Color);
	~Tween();

	virtual void Init() override {}
	virtual void Input(sf::Event&) override {}
	virtual void Update(sf::Time&) override;
	virtual void Render(sf::RenderWindow&) override;
	virtual const sf::FloatRect GetBounds() const override { return sf::FloatRect(); }

	bool IsDone() { return m_Alpha <= 0; }

private:
	sf::Text m_Tween;
	sf::Int32 m_Alpha;
};

