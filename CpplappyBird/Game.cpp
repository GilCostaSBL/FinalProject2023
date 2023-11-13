#include "Game.hpp"
#include "SplashState.hpp"
#include <stdlib.h>
#include <time.h>

Game::Game(int width, int height, std::string title)
{

	srand(time(NULL));

	mData->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	mData->machine.AddState(StateRef(new SplashState(mData)));

	Run();
}

void Game::Run()
{

	float newTime, frameTime, interpolation;

	float currentTime = mClock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (mData->window.isOpen())
	{
		mData->machine.ProcessStateChanges();

		newTime = mClock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= deltaTime)
		{
			mData->machine.GetActiveState()->HandleInput();
			mData->machine.GetActiveState()->Update(deltaTime);

			accumulator -= deltaTime;
		}

		interpolation = accumulator / deltaTime;
		mData->machine.GetActiveState()->Draw(interpolation);
	}
}