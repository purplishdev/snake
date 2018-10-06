#include "ScreenManager.h"
#include "MenuScreen.h"

sf::Vector2u ScreenManager::ScreenSize;

ScreenManager::~ScreenManager()
{
}

void ScreenManager::LoadDefault()
{
	m_Screens.clear();
	AddScreen(new MenuScreen());
}

void ScreenManager::AddScreen(IScreen* screen)
{
	if (screen == nullptr)
		return;

	if (m_Screens.size() > 0)
		GetTopScreen()->Deactivated();

	screen->Init();
	screen->Activated();
	m_Screens.push_back(std::shared_ptr<IScreen>(screen));
}

void ScreenManager::DropScreen()
{
	if (m_Screens.size() <= 1)
		return;

	m_Screens.pop_back();

	GetTopScreen()->Activated();
}

std::list<std::shared_ptr<IScreen>>& ScreenManager::GetScreens()
{
	return m_Screens;
}

std::shared_ptr<IScreen> ScreenManager::GetTopScreen()
{
	return m_Screens.back();
}
