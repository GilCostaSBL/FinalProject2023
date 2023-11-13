#pragma once

#include <SFML\Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "MainMenuState.hpp"

class SplashState : public State
{

public:

	SplashState(GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float deltaTime);
	void Draw(float deltaTime);

private:

	GameDataRef mData;
	sf::Clock mClock;

	sf::Texture _backgroundTexture;
	sf::Sprite skyBackground;
};
