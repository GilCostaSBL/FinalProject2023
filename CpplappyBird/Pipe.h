#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "Game.h"
#include "Definitions.h"

class Pipe
{

public:

	Pipe(GameDataRef data);

	void SpawnBottomPipe();
	void SpawnTopPipe();
	void SpawnInvisiblePipe();
	void SpawnScoringPipe();
	void MovePipes(float deltaTime);
	void DrawPipes();
	void RandomisePipeOffset();

	const std::vector<sf::Sprite>& GetSprites();
	std::vector<sf::Sprite>& GetScoringSprites();

private:

	GameDataRef mData;
	std::vector<sf::Sprite> pipeSprites;
	std::vector<sf::Sprite> scoringPipes;

	int mLandHeight;
	int mPipeYGap;
};
