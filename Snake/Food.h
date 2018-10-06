#pragma once

#include "Utils.h"
#include "IEntity.h"

class Food : public IEntity
{
public:
	Food();
	virtual ~Food();

	void Eaten();

	bool Spawned() { return !m_Eaten; };

	virtual void Init() override {};
	virtual void Input(sf::Event &) override {};
	virtual void Update(sf::Time&) override;
	virtual void Render(sf::RenderWindow&) override;
	virtual const sf::FloatRect GetBounds() const override
	{
		return m_Food.getGlobalBounds();
	};

private:
	sf::RectangleShape m_Food;
	bool m_Eaten;

	sf::Int32 m_RespawnTime;
	sf::Int32 m_DespawnTime;
	sf::Time m_Timer;
};

