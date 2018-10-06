#include "Food.h"

#include <iostream>

Food::Food()
{
	m_Food.setSize(sf::Vector2f(10.0f, 10.0f));
	m_Food.setPosition(Utils::GetRandomPosition(sf::Vector2f(10.0f, 10.0f)));
	m_Food.setFillColor(sf::Color::Green);

	m_Eaten = false;
	m_Timer = sf::Time::Zero;
	m_RespawnTime = 10000;
	m_DespawnTime = 10000;
}

Food::~Food()
{
}

void Food::Eaten()
{
	m_Eaten = true;
	m_Timer = sf::Time::Zero;
	m_RespawnTime = Utils::GetRandom(500, 2000);
	m_DespawnTime = Utils::GetRandom(3000, 5000);

	auto rand = Utils::GetRandomPosition(m_Food.getSize());
	m_Food.setPosition(rand);
}

void Food::Update(sf::Time& delta)
{
	m_Timer += delta;

	if (m_Eaten && m_Timer.asMilliseconds() > m_RespawnTime)
	{
		m_Timer = sf::Time::Zero;
		m_Eaten = false;

		std::cout << "[DEBUG] Food spawned, X:" << m_Food.getPosition().x << " Y:" << m_Food.getPosition().y << "\n";
	}
	else if (!m_Eaten && m_Timer.asMilliseconds() > m_DespawnTime)
	{
		Eaten();
		std::cout << "[DEBUG] Food despawned, timeout\n";
	}
}

void Food::Render(sf::RenderWindow& window)
{
	if (!m_Eaten) window.draw(m_Food);
}