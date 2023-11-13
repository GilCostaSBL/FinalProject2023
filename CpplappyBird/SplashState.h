#pragma once

#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "MainMenuState.h"

class SplashState : public State
{

public:

	SplashState(GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:

	GameDataRef mData;
	sf::Clock mClock;

	sf::Texture mBackgroundTexture;
	sf::Sprite mBackground;
};