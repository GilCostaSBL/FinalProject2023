#pragma once
#include <SFML\Graphics.hpp>
#include "Definitions.hpp"
#include "Game.hpp"
#include <vector>

class Bird
{

public:

	Bird(GameDataRef data);

	void Draw();
	void Animate(float deltaTime);
	void Update(float deltaTime);
	void Tap();
	const sf::Sprite& GetSprite() const;

private:

	GameDataRef mData;

	sf::Sprite birdSprite;
	std::vector<sf::Texture> animationFrames;

	unsigned int animIter;
	sf::Clock mClock;
	sf::Clock movementClock;
	int birdState;

	float birdRotation;
};
