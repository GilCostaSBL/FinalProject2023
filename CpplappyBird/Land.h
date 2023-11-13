#pragma once

#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Definitions.h"
#include <vector>

class Land
{

public:

	Land(GameDataRef data);

	void MoveLand(float deltaTime);
	void DrawLand();

	const std::vector<sf::Sprite>& GetSprites() const;

private:

	GameDataRef mData;

	std::vector<sf::Sprite> mLandSprite;
};
