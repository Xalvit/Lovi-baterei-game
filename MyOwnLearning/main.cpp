#include "GameLovyBatareyi.h"
int main()
{
	srand(time(NULL));
	GameLoviBatareyi game;

	while (game.isWindowOpen())
	{
		try
		{
			game.pollEvents();
			game.update();
		}
		catch (const std::exception& sf)
		{
			sf.what();
		}


	}

	return 0;
}