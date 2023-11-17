#include "Bird.h"

Bird::Bird(GameDataRef data) : mData(data)
{
	animIter = 0;

	mAnimationFrames.push_back(mData->assets.GetTexture("BirdFrame1"));
	mAnimationFrames.push_back(mData->assets.GetTexture("BirdFrame2"));
	mAnimationFrames.push_back(mData->assets.GetTexture("BirdFrame3"));
	mAnimationFrames.push_back(mData->assets.GetTexture("BirdFrame4"));

	mBirdSprites.setTexture(mAnimationFrames.at(animIter));

	mBirdSprites.setPosition((mData->window.getSize().x / 4) - (mBirdSprites.getGlobalBounds().width / 2),
		(mData->window.getSize().y / 2) - (mBirdSprites.getGlobalBounds().height / 2));

	mBirdState = BIRD_STATE_STILL;

	sf::Vector2f origin = sf::Vector2f(mBirdSprites.getGlobalBounds().width / 2, mBirdSprites.getGlobalBounds().height / 2);

	mBirdSprites.setOrigin(origin);
	mRotation = 0;
}


void Bird::Draw()
{

	mData->window.draw(mBirdSprites);
}

void Bird::Animate(float deltaTime)
{
	if (mAnimClock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / mAnimationFrames.size())
	{
		if (animIter < mAnimationFrames.size() - 1)
		{
			animIter++;
		}
		else
		{
			animIter = 0;
		}

		mBirdSprites.setTexture(mAnimationFrames.at(animIter));
		mAnimClock.restart();
	}
}

void Bird::Update(float deltaTime)
{
	if (BIRD_STATE_FALLING == mBirdState)
	{
		mBirdSprites.move(0, GRAVITY * deltaTime);
		mRotation += ROTATION_SPEED * deltaTime;

		if (mRotation > 25.0f)
		{
			mRotation = 25.0f;
		}

		mBirdSprites.setRotation(mRotation);
	}
	else if (BIRD_STATE_FLYING == mBirdState)
	{
		mBirdSprites.move(0, -FLYING_SPEED * deltaTime);
		mRotation -= ROTATION_SPEED * deltaTime;

		if (mRotation < 25.0f)
		{
			mRotation = -25.0f;
		}

		mBirdSprites.setRotation(mRotation);
	}

	if (mMovementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
	{
		mMovementClock.restart();
		mBirdState = BIRD_STATE_FALLING;
	}
}

void Bird::Fly()
{
	mMovementClock.restart();
	mBirdState = BIRD_STATE_FLYING;
}

const sf::Sprite& Bird::GetSprite() const
{
	return mBirdSprites;
}
