#include <sstream>
#include <iostream>
#include "SplashState.hpp"
#include "Definitions.hpp"

SplashState::SplashState(GameDataRef data) : mData(data)
{


}

void SplashState::Init()
{

	mData->assets.LoadTexture("SplashStateBackground", SPLASH_SCENE_BACKGROUND_FILEPATH);
	skyBackground.setTexture(this->mData->assets.GetTexture("SplashStateBackground"));
}

void SplashState::HandleInput()
{

	sf::Event event;

	while (mData->window.pollEvent(event))
	{

		if (sf::Event::Closed == event.type)
			mData->window.close();

	}
}

void SplashState::Update(float deltaTime)
{

	if (mClock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{

		std::cout << "[SplashState::Update] Go to Main Menu" << std::endl;
		mData->machine.AddState(StateRef(new MainMenuState(this->mData)));
	}
}

void SplashState::Draw(float deltaTime)
{

	mData->window.clear();
	mData->window.display();
}


