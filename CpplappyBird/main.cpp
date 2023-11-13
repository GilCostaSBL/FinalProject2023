#include <iostream>
#include "Game.h"
#include "Definitions.h"

// switch to WinMain if it's configured for Subsystem::Windows
int main()
{

	Game game = Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");

	return EXIT_SUCCESS;
}