#pragma once

#include "SFML/Graphics.hpp"

class IScreen
{
public:
	virtual ~IScreen() { }
	virtual void Init() = 0;
	virtual void Input(sf::Event&) = 0;
	virtual void Update(sf::Time&) = 0;
	virtual void Render(sf::RenderWindow&) = 0;
	virtual void Activated() = 0;
	virtual void Deactivated() = 0;
};