#include "World.h"

bool World::m_OpenWorld;
sf::FloatRect World::m_OpenWorldBounds;
sf::FloatRect World::m_ClosedWorldBounds;
std::vector<sf::RectangleShape*> World::m_Objects;

World::World(const sf::FloatRect world, sf::Color color)
{
	// 1. Set up Closed World drawable
	m_World.setPosition(world.left, world.top);
	m_World.setSize(sf::Vector2f(world.width, world.height));
	m_World.setFillColor(sf::Color::Black);
	m_World.setOutlineThickness(-edgeThickness);

	// 2. Set up Closed World bounds.
	m_ClosedWorldBounds = sf::FloatRect(
		world.left + edgeThickness,
		world.top + edgeThickness,
		world.width - edgeThickness*2,
		world.height - edgeThickness*2
		);

	// 3. Set up Open World bounds.
	m_OpenWorldBounds = sf::FloatRect(
		world.left - edgeThickness,
		world.top - edgeThickness,
		world.width + edgeThickness * 2,
		world.height + edgeThickness * 2
		);

	m_Color = color;
}

World::~World()
{
	DeleteObjects();
}

sf::Vector2f World::GetTeleport(const Snake* snake)
{
	auto snakeBounds = snake->GetBounds();

	if (snakeBounds.top <= m_OpenWorldBounds.top)
		return sf::Vector2f(snakeBounds.left, m_OpenWorldBounds.top + m_OpenWorldBounds.height - snakeBounds.height);

	else if (snakeBounds.top >= m_OpenWorldBounds.top + m_OpenWorldBounds.height)
		return sf::Vector2f(snakeBounds.left, m_OpenWorldBounds.top);

	else if (snakeBounds.left <= m_OpenWorldBounds.left)
		return sf::Vector2f(m_OpenWorldBounds.left + m_OpenWorldBounds.width - snakeBounds.width, snakeBounds.top);

	else if (snakeBounds.left >= m_OpenWorldBounds.left + m_OpenWorldBounds.width)
		return sf::Vector2f(m_OpenWorldBounds.left, snakeBounds.top);

	return sf::Vector2f(0, 0);
}

void World::AddObject(sf::FloatRect rect, sf::Color color)
{
	auto obj = new sf::RectangleShape(sf::Vector2f(rect.width, rect.height));
	obj->setPosition(sf::Vector2f(rect.left, rect.top));
	obj->setFillColor(color);
	m_Objects.push_back(obj);
}

void World::Render(sf::RenderWindow& window)
{
	window.draw(m_World);

	for (auto obj : m_Objects)
		window.draw(*obj);
}

void World::DeleteObjects()
{
	for (auto obj : m_Objects)
		delete obj;
	m_Objects.clear();
}

bool World::Collides(const IEntity* e1, const IEntity* e2)
{
	auto r1 = e1->GetBounds();
	auto r2 = e2->GetBounds();
	return r1.intersects(r2);
}

bool World::CollideWithObjects(const IEntity* entity)
{
	auto rect = entity->GetBounds();

	for (auto obj : m_Objects)
	{
		if (obj->getGlobalBounds().intersects(rect))
			return true;
	}

	return false;
}

bool World::CollideWithObjects(const sf::FloatRect& rect)
{
	for (auto obj : m_Objects)
	{
		if (obj->getGlobalBounds().intersects(rect))
			return true;
	}

	return false;
}

bool World::CollideWithWorld(const IEntity* entity)
{
	auto rect = entity->GetBounds();
	auto& worldBounds = this->GetBounds();

	if (rect.top < worldBounds.top)
		return true;
	else if (rect.top > worldBounds.top + worldBounds.height - rect.height)
		return true;
	else if (rect.left < worldBounds.left)
		return true;
	else if (rect.left > worldBounds.left + worldBounds.width - rect.width)
		return true;

	return false;
}

void World::LoadMap(int i)
{
	DeleteObjects();

	auto& world = this->GetBounds();

	if (i == 0)
	{
		AddObject(sf::FloatRect(
			world.left + 80, 
			world.top + 80, 
			80.f, 80.f), m_Color);

		AddObject(sf::FloatRect(
			world.left + world.width - 160, 
			world.top + 80, 
			80.f, 80.f), m_Color);

		AddObject(sf::FloatRect(
			world.left + 80,
			world.top + world.height - 160,
			80.f, 80.f), m_Color);

		AddObject(sf::FloatRect(
			world.left + world.width - 160,
			world.top + world.height - 160,
			80.f, 80.f), m_Color);

		AddObject(sf::FloatRect(
			(world.left + world.width / 2) - 40,
			(world.top + world.height / 2) - 40,
			80.f, 80.f), m_Color);
	}
	else if (i == 1 && this->IsOpen())
	{
		AddObject(sf::FloatRect(
			world.left,
			(world.top + world.height) / 2 - 15.f,
			world.width, 10.f), m_Color);

		AddObject(sf::FloatRect(
			(world.left + world.width) / 2 - 15.f,
			world.top,
			10.f, world.height), m_Color);
	}
}

void World::SetOpen(bool open)
{
	m_World.setOutlineColor(open ? sf::Color::Transparent : m_Color);
	m_OpenWorld = open;
}
