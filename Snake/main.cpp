
#if SFML_VERSION_MAJOR >= 2
	#if SFML_VERSION_MINOR <= 3
		#define _OLD_API
	#endif
#endif

#include "Game.h"

int main()
{
	srand(time(NULL));

	Game* game = new Game("Snake", 600, 500);
	game->Start();

	return 0;
}