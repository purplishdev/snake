#pragma once

#include <vector>

#include "IScreen.h"
#include "ScreenManager.h"
#include "FontManager.h"

#include "PlayScreen.h"

enum class Menu : sf::Uint8
{
	OnePlayer = 1,
	TwoPlayers,
	Exit
};

class MenuScreen : public IScreen
{
public:
	MenuScreen();
	~MenuScreen();

	virtual void Init() override;
	virtual void Input(sf::Event&) override;
	virtual void Update(sf::Time&) override;
	virtual void Render(sf::RenderWindow&) override;
	virtual void Activated() override;
	virtual void Deactivated() override;

private:
	std::vector<sf::Text*> m_Items;
	sf::Uint8 m_CurrentItem;
};

