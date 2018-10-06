
#include "Utils.h"
#include "World.h"

namespace Utils {

	sf::Uint32 GetRandom(sf::Uint32 min, sf::Uint32 max)
	{
		return rand() % (max - min + 1) + min;
	}

	sf::Vector2f GetRandomPosition(sf::Vector2f size)
	{
		auto& world = World::GetBounds();

		sf::FloatRect vec(0, 0, size.x, size.y);
		do
		{
			vec.left = GetRandom(world.left / 10 + 2, world.width / 10 - 2) * 10.f;
			vec.top  = GetRandom(world.top / 10 + 2, (world.top + world.height) / 10 - 2) * 10.f;
		} while (World::CollideWithObjects(vec));

		return sf::Vector2f(vec.left, vec.top);
	};

}