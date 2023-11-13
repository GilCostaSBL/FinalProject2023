#pragma once

#include <SFML\Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"

class Flash
{

public:

	Flash(GameDataRef data);

	void Show(float deltaTime);
	void Draw();

private:

	GameDataRef mData;

	sf::RectangleShape mFlashShape;
	bool isFlashOn;

};