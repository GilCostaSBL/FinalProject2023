#pragma once
#include <SFML\Graphics.hpp>
#include "Definitions.hpp"
#include "Game.hpp"

class HUD
{

public:

	HUD(GameDataRef data);

	void Draw();
	void UpdateScore(int score);

private:

	GameDataRef mData;
	sf::Text scoreText;
};