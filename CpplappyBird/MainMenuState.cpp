#include <sstream>
#include <iostream>
#include "MainMenuState.h"
#include "GameState.h"
#include "Definitions.h"

MainMenuState::MainMenuState(GameDataRef data) : mData(data)
{


}

void MainMenuState::Init()
{

	mData->assets.LoadTexture("MainMenuBackground", MAIN_MENU_BACKGROUND_FILEPATH);
	mData->assets.LoadTexture("GameTitle", GAME_TITLE_FILEPATH);
	mData->assets.LoadTexture("PlayButton", PLAY_BUTTON_FILEPATH);

	mBackground.setTexture(this->mData->assets.GetTexture("MainMenuBackground"));
	mMainTitle.setTexture(this->mData->assets.GetTexture("GameTitle"));
	mPlayButton.setTexture(this->mData->assets.GetTexture("PlayButton"));

	mMainTitle.setPosition((SCREEN_WIDTH / 2) - mMainTitle.getGlobalBounds().width / 2,
		mMainTitle.getGlobalBounds().height / 2);

	mPlayButton.setPosition((SCREEN_WIDTH / 2) - mPlayButton.getGlobalBounds().width / 2,
		(SCREEN_HEIGHT / 2) - mPlayButton.getGlobalBounds().height / 2);
}

void MainMenuState::HandleInput()
{

	sf::Event event;

	while (mData->window.pollEvent(event))
	{

		if (sf::Event::Closed == event.type)
			mData->window.close();

		if (mData->input.IsSpriteClicked(mPlayButton, sf::Mouse::Left, mData->window))
		{
			std::cout << "[MainMenuState::HandleInput] Go to Play state" << std::endl;
			mData->machine.AddState(StateRef(new GameState(this->mData)));
		}

	}
}

void MainMenuState::Update(float deltaTime)
{

	if (mClock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{


	}
}

void MainMenuState::Draw(float deltaTime)
{

	mData->window.clear();
	mData->window.draw(mBackground);
	mData->window.draw(mMainTitle);
	mData->window.draw(mPlayButton);
	mData->window.display();
}

