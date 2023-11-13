#include "Pipe.hpp"
#include <iostream>

Pipe::Pipe(GameDataRef data) : mData(data)
{
	landHeight = mData->assets.GetTexture("Land").getSize().y;
	pipeYDistance = 0;
}

void Pipe::SpawnBottomPipe()
{

	sf::Sprite sprite(mData->assets.GetTexture("PipeUp"));
	sprite.setPosition(mData->window.getSize().x, mData->window.getSize().y - sprite.getGlobalBounds().height - pipeYDistance);
	pipeSprites.push_back(sprite);
}

void Pipe::SpawnTopPipe()
{

	sf::Sprite sprite(mData->assets.GetTexture("PipeDown"));
	sprite.setPosition(mData->window.getSize().x, -pipeYDistance);
	pipeSprites.push_back(sprite);
}

void Pipe::SpawnInvisiblePipe()
{

	sf::Sprite sprite(mData->assets.GetTexture("PipeUp"));
	sprite.setPosition(mData->window.getSize().x, -pipeYDistance);
	sprite.setColor(sf::Color(0, 0, 0, 0));
	pipeSprites.push_back(sprite);
}

void Pipe::SpawnScoringPipe()
{

	sf::Sprite sprite(mData->assets.GetTexture("ScoringPipe"));
	sprite.setPosition(mData->window.getSize().x, 0);
	scoringPipes.push_back(sprite);
}

void Pipe::MovePipes(float deltaTime)
{
	for (unsigned int i = 0; i < pipeSprites.size(); i++)
	{

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

	pipeYDistance = rand() % (landHeight + 1);
}

const std::vector<sf::Sprite>& Pipe::GetSprites() const
{

	return pipeSprites;
}

std::vector<sf::Sprite>& Pipe::GetScoringSprites()
{

	return scoringPipes;
}

