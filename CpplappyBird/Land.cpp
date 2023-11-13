#include "Land.hpp"


Land::Land(GameDataRef data) : mData(data)
{
	sf::Sprite sprite(mData->assets.GetTexture("Land"));
	sf::Sprite sprite2(mData->assets.GetTexture("Land"));

	sprite.setPosition(0, mData->window.getSize().y - sprite.getGlobalBounds().height);
	sprite2.setPosition(sprite.getGlobalBounds().width, mData->window.getSize().y - sprite2.getGlobalBounds().height);

	landSprite.push_back(sprite);
	landSprite.push_back(sprite2);
}

void Land::MoveLand(float deltaTime)
{

	for (unsigned int i = 0; i < landSprite.size(); i++)
	{

		float movement = PIPE_MOVEMENT_SPEED * deltaTime;
		landSprite.at(i).move(-movement, 0.0f);

		if (landSprite.at(i).getPosition().x < 0 - landSprite.at(i).getGlobalBounds().width)
		{
			sf::Vector2f position(mData->window.getSize().x, landSprite.at(i).getPosition().y);

			landSprite.at(i).setPosition(position);
		}
	}
}

void Land::DrawLand()
{

	for (unsigned int i = 0; i < landSprite.size(); i++)
	{

		mData->window.draw(landSprite.at(i));
	}
}

const std::vector<sf::Sprite>& Land::GetSprites() const
{

	return landSprite;
}
