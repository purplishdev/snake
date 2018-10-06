#pragma once

class IHudElement
{
public:
	virtual ~IHudElement() { }
	virtual void Reset() = 0;
	virtual void Update(sf::Time&) = 0;
	virtual void Render(sf::RenderWindow&) = 0;
};