#pragma once

#include "SFML/Graphics.hpp"

class IEntity
{
public:
	virtual ~IEntity() { }
	virtual void Init() = 0;
	virtual void Input(sf::Event&) = 0;
	virtual void Update(sf::Time&) = 0;
	virtual void Render(sf::RenderWindow&) = 0;
	virtual const sf::FloatRect GetBounds() const = 0;
};