#include "Bird.hpp"


Bird::Bird(GameDataRef data) : mData(data)
{

	animIter = 0;

	animationFrames.push_back(mData->assets.GetTexture("BirdFrame1"));
	animationFrames.push_back(mData->assets.GetTexture("BirdFrame2"));
	animationFrames.push_back(mData->assets.GetTexture("BirdFrame3"));
	animationFrames.push_back(mData->assets.GetTexture("BirdFrame4"));


	birdSprite.setTexture(animationFrames.at(animIter));

	birdSprite.setPosition((mData->window.getSize().x / 4) - (birdSprite.getGlobalBounds().width / 2),
		(mData->window.getSize().y / 2) - (birdSprite.getGlobalBounds().height / 2));

	birdState = BIRD_STATE_STILL;

	sf::Vector2f origin = sf::Vector2f(birdSprite.getGlobalBounds().width / 2, birdSprite.getGlobalBounds().height / 2);

	birdSprite.setOrigin(origin);
	birdRotation = 0;

}


void Bird::Draw()
{

	mData->window.draw(birdSprite);
}

void Bird::Animate(float deltaTime)
{

	if (mClock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / animationFrames.size())
	{

		if (animIter < animationFrames.size() - 1)
		{

			animIter++;
		}
		else
		{
			animIter = 0;
		}

		birdSprite.setTexture(animationFrames.at(animIter));

		mClock.restart();
	}
}

void Bird::Update(float deltaTime)
{

	if (BIRD_STATE_FALLING == birdState)
	{

		birdSprite.move(0, GRAVITY * deltaTime);
		birdRotation += ROTATION_SPEED * deltaTime;

		if (birdRotation > 25.0f)
		{

			birdRotation = 25.0f;
		}

		birdSprite.setRotation(birdRotation);
	}
	else if (BIRD_STATE_FLYING == birdState)
	{

		birdSprite.move(0, -FLYING_SPEED * deltaTime);
		birdRotation -= ROTATION_SPEED * deltaTime;

		if (birdRotation < 25.0f)
		{

			birdRotation = -25.0f;
		}

		birdSprite.setRotation(birdRotation);
	}

	if (movementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
	{

		movementClock.restart();
		birdState = BIRD_STATE_FALLING;
	}

}

void Bird::Tap()
{

	movementClock.restart();
	birdState = BIRD_STATE_FLYING;
}

const sf::Sprite& Bird::GetSprite() const
{
	return birdSprite;
}
