#include "Game.h"
#include "SplashState.h"
#include <stdlib.h>
#include <time.h>

Game::Game(int width, int height, std::string title)
{

	srand(time(NULL));

	mData->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	mData->machine.AddState(StateRef(new SplashState(this->mData)));

	this->Run();
}

void Game::Run()
{

	float newTime, frameTime, interpolation;

	float currentTime = this->mClock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->mData->window.isOpen())
	{

		this->mData->machine.ProcessStateChanges();

		newTime = this->mClock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= deltaTime)
		{
			this->mData->machine.GetActiveState()->HandleInput();
			this->mData->machine.GetActiveState()->Update(deltaTime);

			accumulator -= deltaTime;
		}

		interpolation = accumulator / deltaTime;
		this->mData->machine.GetActiveState()->Draw(interpolation);
	}
}