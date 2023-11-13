#pragma once
#include <SFML\Graphics.hpp>
#include "Definitions.h"
#include "Game.h"

class HUD
{

public:

	HUD(GameDataRef data);

	void Draw();
	void UpdateScore(int score);

private:

	GameDataRef mData;
	sf::Text mScoreText;
};

