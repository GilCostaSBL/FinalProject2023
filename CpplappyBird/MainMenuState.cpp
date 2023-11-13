#include <sstream>
#include <iostream>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "Definitions.hpp"

MainMenuState::MainMenuState(GameDataRef data) : mData(data)
{


}

void MainMenuState::Init()
{

	mData->assets.LoadTexture("MainMenuBackground", MAIN_MENU_BACKGROUND_FILEPATH);
	mData->assets.LoadTexture("GameTitle", GAME_TITLE_FILEPATH);
	mData->assets.LoadTexture("PlayButton", PLAY_BUTTON_FILEPATH);

	skyBackground.setTexture(this->mData->assets.GetTexture("MainMenuBackground"));
	mainTitle.setTexture(this->mData->assets.GetTexture("GameTitle"));
	playButton.setTexture(this->mData->assets.GetTexture("PlayButton"));

	mainTitle.setPosition((SCREEN_WIDTH / 2) - mainTitle.getGlobalBounds().width / 2,
		mainTitle.getGlobalBounds().height / 2);

	playButton.setPosition((SCREEN_WIDTH / 2) - playButton.getGlobalBounds().width / 2,
		(SCREEN_HEIGHT / 2) - playButton.getGlobalBounds().height / 2);
}

void MainMenuState::HandleInput()
{

	sf::Event event;

	while (mData->window.pollEvent(event))
	{

		if (sf::Event::Closed == event.type)
			mData->window.close();

		if (mData->input.IsSpriteClicked(playButton, sf::Mouse::Left, mData->window))
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
	mData->window.draw(skyBackground);
	mData->window.draw(mainTitle);
	mData->window.draw(playButton);
	mData->window.display();
}

