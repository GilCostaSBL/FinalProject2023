#include "Pipe.h"
#include <iostream>

Pipe::Pipe(GameDataRef data) : mData(data)
{
	mLandHeight = mData->assets.GetTexture("Land").getSize().y;
	mPipeYGap = 0;
}

void Pipe::SpawnBottomPipe()
{
	sf::Sprite landSprite1(mData->assets.GetTexture("PipeUp"));
	landSprite1.setPosition(mData->window.getSize().x, mData->window.getSize().y - landSprite1.getGlobalBounds().height - mPipeYGap);
	pipeSprites.push_back(landSprite1);
}

void Pipe::SpawnTopPipe()
{
	sf::Sprite landSprite1(mData->assets.GetTexture("PipeDown"));
	landSprite1.setPosition(mData->window.getSize().x, -mPipeYGap);
	pipeSprites.push_back(landSprite1);
}

void Pipe::SpawnInvisiblePipe()
{
	sf::Sprite landSprite1(mData->assets.GetTexture("PipeUp"));
	landSprite1.setPosition(mData->window.getSize().x, -mPipeYGap);
	landSprite1.setColor(sf::Color(0, 0, 0, 0));
	pipeSprites.push_back(landSprite1);
}

void Pipe::SpawnScoringPipe()
{
	sf::Sprite landSprite1(mData->assets.GetTexture("ScoringPipe"));
	landSprite1.setPosition(mData->window.getSize().x, 0);
	scoringPipes.push_back(landSprite1);
}

void Pipe::MovePipes(float deltaTime)
{
	for (unsigned int i = 0; i < pipeSprites.size(); i++)
	{
		// Check for pipes outside game area and deletes the ones passed the full screen
		if (pipeSprites.at(i).getPosition().x < 0 - pipeSprites.at(i).getGlobalBounds().width)
		{
			pipeSprites.erase(pipeSprites.begin() + i);
		}
		else
		{
			float movement = PIPE_MOVEMENT_SPEED * deltaTime;
			pipeSprites.at(i).move(-movement, 0);
		}
	}

	for (unsigned int i = 0; i < scoringPipes.size(); i++)
	{
		if (scoringPipes.at(i).getPosition().x < 0 - scoringPipes.at(i).getGlobalBounds().width)
		{
			scoringPipes.erase(scoringPipes.begin() + i);
		}
		else
		{
			float movement = PIPE_MOVEMENT_SPEED * deltaTime;
			scoringPipes.at(i).move(-movement, 0);
		}
	}
}

void Pipe::DrawPipes()
{
	for (unsigned short int i = 0; i < pipeSprites.size(); i++)
	{
		mData->window.draw(pipeSprites.at(i));
	}
}

void Pipe::RandomisePipeOffset()
{
	mPipeYGap = rand() % (mLandHeight + 1);
}

const std::vector<sf::Sprite>& Pipe::GetSprites() 
{
	return pipeSprites;
}

std::vector<sf::Sprite>& Pipe::GetScoringSprites()
{
	return scoringPipes;
}
