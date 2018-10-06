#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics/Font.hpp>

class FontManager
{
public:

	static FontManager* GetInstance()
	{
		static FontManager instance;
		return &instance;
	}

	bool LoadFont(const std::string& fontName, const std::string& location);
	sf::Font* GetFont(const std::string& fontName);

private:
	FontManager() { }
	~FontManager();
	FontManager(FontManager const&);	// Don't Implement
	void operator=(FontManager const&);	// Don't implement

	std::vector< std::pair<std::string, sf::Font*> > m_Fonts;
};

