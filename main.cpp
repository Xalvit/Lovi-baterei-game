#include "GameLovyBatareyi.h"

int main()
{
	srand(time(NULL));
	GameLoviBatareyi game;

	while (game.isWindowOpen())
	{
			game.pollEvents();
			game.update();
	}

	return 0;
}