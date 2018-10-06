#pragma once

#include "IScreen.h"
#include "FontManager.h"
#include "ScreenManager.h"

class PauseScreen : public IScreen
{
public:
	PauseScreen(const std::string);
	~PauseScreen();

	virtual void Init() override;
	virtual void Input(sf::Event&) override;
	virtual void Update(sf::Time&) override { }
	virtual void Render(sf::RenderWindow&) override;
	virtual void Activated() override;
	virtual void Deactivated() override;

	void SetCancelable(bool cancel) { m_Cancelable = cancel; }

private:
	std::string m_Text;
	sf::Font m_Font;
	sf::Text m_Label;
	sf::RectangleShape m_Rect;
	bool m_Cancelable;
};

