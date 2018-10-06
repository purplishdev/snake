#pragma once

#include <SFML/Graphics.hpp>

namespace Utils {

	sf::Uint32 GetRandom(sf::Uint32, sf::Uint32);
	sf::Vector2f GetRandomPosition(sf::Vector2f size);

	template<typename T>
	inline T clamp(const T & val, const T & min, const T & max)
	{
		return std::min(std::max(val, min), max);
	}

};