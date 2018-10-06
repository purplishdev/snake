#pragma once

#include <deque>

#include "Utils.h"
#include "IEntity.h"

#define IS_PRESSED(key) sf::Keyboard::isKeyPressed(key) 

enum class Direction
{
	Left,
	Up,
	Right,
	Down
};

enum class Control
{
	Arrows,
	WSAD
};

class Snake : public IEntity
{
public:
	Snake(sf::Vector2f, sf::Uint8, sf::Color, Direction, Control);
	virtual ~Snake();

	void Grow(sf::Uint8 factor) { m_GrowDelta += factor; }
	bool Collide(const Snake*);
	void SetPosition(sf::Vector2f);
	void SetDirection(Direction);

	void Init() override;
	void Input(sf::Event&) override;
	void Update(sf::Time&) override;
	void Render(sf::RenderWindow&) override;
	const sf::FloatRect GetBounds() const override
	{
		auto snake = m_Nodes.front();
		return sf::FloatRect(snake->getPosition() + GetDirectionVector(), snake->getSize());
	};

private:
	sf::Uint8 m_GrowDelta;
	const sf::Uint8 m_InitLength;
	const sf::Vector2f m_Size;
	sf::Vector2f m_StartingPoint;
	bool m_CanMove;
	sf::Color m_Color;
	Direction m_Direction;
	Control m_Control;
	std::deque<sf::RectangleShape*> m_Nodes;

	sf::RectangleShape* CreateNode();

	const sf::Vector2f GetDirectionVector() const
	{
		switch (m_Direction)
		{
		case Direction::Up:		return sf::Vector2f(0, -m_Size.y);
		case Direction::Down:	return sf::Vector2f(0, m_Size.y);
		case Direction::Left:	return sf::Vector2f(-m_Size.x, 0);
		default:
		case Direction::Right:	return sf::Vector2f(m_Size.x, 0);
		}
	}

};