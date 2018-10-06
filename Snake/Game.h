#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "SFML/Graphics.hpp"

#include "IEntity.h"

#include "FontManager.h"
#include "ScreenManager.h"

#include "PlayScreen.h"
#include "PauseScreen.h"
#include "MenuScreen.h"

class Game
{
public:
	Game(sf::String, sf::Uint32, sf::Uint32);
	~Game();

	void Start();

private:
	const std::string m_Name;
	sf::RenderWindow m_Window;

	ScreenManager* m_ScreenManager;
	FontManager* m_FontManager;

	void Init();
	void Input(sf::Event&);
	void Update(sf::Time&);
	void Render(sf::RenderWindow&);

};