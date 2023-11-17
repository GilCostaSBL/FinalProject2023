#pragma once
#include <SFML\Graphics.hpp>
#include "Definitions.h"
#include "Game.h"
#include <vector>

class Bird
{

public:

	Bird(GameDataRef data);

	void Draw();
	void Animate(float deltaTime);
	void Update(float deltaTime);
	void Fly();
	const sf::Sprite& GetSprite() const;

private:

	GameDataRef mData;

	sf::Sprite mBirdSprites;
	std::vector<sf::Texture> mAnimationFrames;
	unsigned int animIter;

	sf::Clock mAnimClock;
	sf::Clock mMovementClock;

	int mBirdState;
	float mRotation;
};
