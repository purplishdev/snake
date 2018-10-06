#pragma once

#include "MenuScreen.h"
#include "PauseScreen.h"

#include "World.h"
#include "Snake.h"
#include "Food.h"
#include "Hud.h"
#include "HudCounter.h"
#include "Tween.h"

class PlayScreen : public IScreen
{
public:
	PlayScreen(bool);
	~PlayScreen();

	virtual void Init() override;
	virtual void Input(sf::Event&) override;
	virtual void Update(sf::Time&) override;
	virtual void Render(sf::RenderWindow&) override;
	virtual void Activated() override;
	virtual void Deactivated() override;

private:
	World *m_World;
	Snake *m_SnakeOne;
	Snake *m_SnakeTwo;
	Food *m_Food;
	Hud *m_Hud;
	HudCounter *m_ScoreOne;
	HudCounter *m_ScoreTwo;

	std::vector<Tween*> m_Tweens;

	sf::Time m_Ticks;
	bool m_Playing;
	bool m_TwoPlayers;
	
	void PlayerOneUpdate(sf::Time&);
	void PlayerTwoUpdate(sf::Time&);
	void GameOver(const std::string);
	void CreateTween(const Snake*, const sf::Uint32, sf::Color);
};

