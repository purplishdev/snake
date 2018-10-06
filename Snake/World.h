#pragma once

#include "Snake.h"

class World
{
public:
	World(const sf::FloatRect, sf::Color);
	virtual ~World();

	void AddObject(sf::FloatRect, sf::Color);
	void LoadMap(int);
	void SetOpen(bool);
	inline bool IsOpen() { return m_OpenWorld; }
	static const sf::FloatRect& GetBounds()
	{
		return m_OpenWorld ? m_OpenWorldBounds : m_ClosedWorldBounds;
	};

	sf::Vector2f GetTeleport(const Snake*);
	bool Collides(const IEntity*, const IEntity*);
	bool CollideWithObjects(const IEntity*);
	bool CollideWithWorld(const IEntity*);
	static bool CollideWithObjects(const sf::FloatRect&);


	void Render(sf::RenderWindow&);


private:
	const float edgeThickness = 10.0f;
	sf::Color m_Color;
	static bool m_OpenWorld;
	sf::RectangleShape m_World;
	static sf::FloatRect m_OpenWorldBounds;
	static sf::FloatRect m_ClosedWorldBounds;

	static std::vector<sf::RectangleShape*> m_Objects;
	void DeleteObjects();
};

