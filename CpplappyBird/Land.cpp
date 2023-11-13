#include "Land.h"


Land::Land(GameDataRef data) : mData(data)
{
	sf::Sprite sprite(mData->assets.GetTexture("Land"));
	sf::Sprite sprite2(mData->assets.GetTexture("Land"));

	sprite.setPosition(0, mData->window.getSize().y - sprite.getGlobalBounds().height);
	sprite2.setPosition(sprite.getGlobalBounds().width, mData->window.getSize().y - sprite2.getGlobalBounds().height);

	mLandSprite.push_back(sprite);
	mLandSprite.push_back(sprite2);
}

void Land::MoveLand(float deltaTime)
{

	for (unsigned int i = 0; i < mLandSprite.size(); i++)
	{

		float movement = PIPE_MOVEMENT_SPEED * deltaTime;
		mLandSprite.at(i).move(-movement, 0.0f);

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
