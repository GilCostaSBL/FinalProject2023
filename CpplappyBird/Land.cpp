#include "Land.h"

Land::Land(GameDataRef data) : mData(data)
{
	// Setting 2 sprites of the same graphic to have one move out of the screen and be repositioned behind the current one
	sf::Sprite landSprite1(mData->assets.GetTexture("Land"));
	sf::Sprite landSprite2(mData->assets.GetTexture("Land"));

	landSprite1.setPosition(0, mData->window.getSize().y - landSprite1.getGlobalBounds().height);
	landSprite2.setPosition(landSprite1.getGlobalBounds().width, mData->window.getSize().y - landSprite2.getGlobalBounds().height);

	mLandSprite.push_back(landSprite1);
	mLandSprite.push_back(landSprite2);
}

void Land::MoveLand(float deltaTime)
{
	for (unsigned int i = 0; i < mLandSprite.size(); i++)
	{
		float movement = PIPE_MOVEMENT_SPEED * deltaTime;
		mLandSprite.at(i).move(-movement, 0.0f);

		// Reached the left of the screen, moves back beghind the current sprite
		if (mLandSprite.at(i).getPosition().x < 0 - mLandSprite.at(i).getGlobalBounds().width)
		{
			sf::Vector2f position(mData->window.getSize().x, mLandSprite.at(i).getPosition().y);
			mLandSprite.at(i).setPosition(position);
		}
	}
}

void Land::DrawLand()
{
	for (unsigned int i = 0; i < mLandSprite.size(); i++)
	{
		mData->window.draw(mLandSprite.at(i));
	}
}

const std::vector<sf::Sprite>& Land::GetSprites() const
{
	return mLandSprite;
}
