#include <stdio.h>
#include <raylib.h>
#include "game.h"




int main(void)
{
	Game game = {};
	bool success = initGame(&game);
	if (success)
	{
		runGameLoop(&game);
	}
	shutdown(&game);
	

	return 0;
}
