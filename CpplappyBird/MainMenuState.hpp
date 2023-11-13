#pragma once

#include <SFML\Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

class MainMenuState : public State
{

public:

	MainMenuState(GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float deltaTime);
	void Draw(float deltaTime);

private:

	GameDataRef mData;
	sf::Clock mClock;

	sf::Sprite skyBackground;
	sf::Sprite mainTitle;
	sf::Sprite playButton;
};

