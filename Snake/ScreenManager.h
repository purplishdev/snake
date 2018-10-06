#pragma once

#include <list>
#include <memory>

#include "IScreen.h"

class ScreenManager
{
public:

	static sf::Vector2u ScreenSize;

	static ScreenManager* GetInstance()
	{
		static ScreenManager instance;
		return &instance;
	}

	void LoadDefault();
	void AddScreen(IScreen*);
	void DropScreen();
	std::list<std::shared_ptr<IScreen>>& GetScreens();
	std::shared_ptr<IScreen> GetTopScreen();

private:
	ScreenManager() { }
	~ScreenManager();
	ScreenManager(ScreenManager const&);	// Don't Implement
	void operator=(ScreenManager const&);	// Don't implement

	std::list<std::shared_ptr<IScreen>> m_Screens;
};