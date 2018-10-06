#include "FontManager.h"

bool FontManager::LoadFont(const std::string& fontName, const std::string& location)
{
	sf::Font* font = new sf::Font();

	if (font->loadFromFile(location))
	{
		m_Fonts.push_back(std::pair<std::string, sf::Font*>(fontName, font));
		std::cout << fontName << " font loaded!" << std::endl;
		return true;
	}

	delete font;
	return false;
}

sf::Font* FontManager::GetFont(const std::string& fontName)
{
	auto it = std::find_if(m_Fonts.begin(), m_Fonts.end(),
		[&fontName](const std::pair<std::string, sf::Font*>& element) { return element.first == fontName; });

	if (it == m_Fonts.end())
		return nullptr;
		
	return it->second;
}

FontManager::~FontManager()
{
}
