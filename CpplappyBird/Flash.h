#pragma once

#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Definitions.h"

class Flash
{

public:

	Flash(GameDataRef data);

	void Show(float deltaTime);
	void Draw();

private:

	GameDataRef mData;

	sf::RectangleShape flashShape;
	bool isFlashOn;

};
