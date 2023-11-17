#include <sstream>
#include <iostream>
#include <fstream>
#include "GameOverState.h"
#include "Definitions.h"
#include "GameState.h"

GameOverState::GameOverState(GameDataRef data, int score) : mData(data), mScore(score)
{
	std::cout << "[GameOverState::GameOverState] Game state" << std::endl;
}

void GameOverState::Init()
{
	std::ifstream readFile;
	readFile.open(HIGHEST_SCORE_PATH, std::ios::app);

	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> mHighScore;
		}
	}
	else
	{
		std::cout << "[GameOverState::Init] readFile could not open" << std::endl;
	}

	readFile.close();
	std::ofstream writeFile(HIGHEST_SCORE_PATH);

	if (writeFile.is_open())
	{
		if (mScore > mHighScore)
		{
			mHighScore = mScore;
		}
		writeFile << mHighScore;
	}
	else
	{
		std::cout << "[GameOverState::Init] writeFile could not open" << std::endl;
	}

	writeFile.close();

	mData->assets.LoadTexture("GameOverStateBackground", GAME_OVER_BACKGROUND_FILEPATH);
	mData->assets.LoadTexture("GameOverStateTitle", GAME_OVER_TITLE_FILEPATH);
	mData->assets.LoadTexture("GameOverStateBody", GAME_OVER_BODY_FILEPATH);
	mData->assets.LoadTexture("BronzeMedal", BRONZE_MEDAL_FILEPATH);
	mData->assets.LoadTexture("SilverMedal", SILVER_MEDAL_FILEPATH);
	mData->assets.LoadTexture("GoldMedal", GOLD_MEDAL_FILEPATH);
	mData->assets.LoadTexture("PlatinumMedal", PLATINUM_MEDAL_FILEPATH);

	mBackground.setTexture(this->mData->assets.GetTexture("GameOverStateBackground"));
	mGameOverTitle.setTexture(this->mData->assets.GetTexture("GameOverStateTitle"));
	mGameOverContainer.setTexture(this->mData->assets.GetTexture("GameOverStateBody"));
	mRetryButton.setTexture(this->mData->assets.GetTexture("PlayButton"));

	mGameOverContainer.setPosition(mData->window.getSize().x / 2 - (mGameOverContainer.getGlobalBounds().width / 2),
		(mData->window.getSize().y / 2) - (mGameOverContainer.getGlobalBounds().height / 2));

	mGameOverTitle.setPosition((mData->window.getSize().x / 2) - (mGameOverTitle.getGlobalBounds().width / 2),
		mGameOverContainer.getPosition().y - (mGameOverTitle.getGlobalBounds().height * 1.2));

	mRetryButton.setPosition((mData->window.getSize().x / 2) - (mGameOverTitle.getGlobalBounds().width / 2),
		mGameOverContainer.getPosition().y + mGameOverContainer.getGlobalBounds().height +
		mRetryButton.getLocalBounds().height * 0.2);

	mScoreText.setFont(mData->assets.GetFont("FlappyFont"));
	mScoreText.setString(std::to_string(mScore));
	mScoreText.setCharacterSize(56);
	mScoreText.setFillColor(sf::Color::White);
	mScoreText.setOrigin(mScoreText.getGlobalBounds().width / 2, mScoreText.getGlobalBounds().height / 2);
	mScoreText.setPosition(mData->window.getSize().x / 10 * 7.25, mData->window.getSize().y / 2.15);

	mHighScoreText.setFont(mData->assets.GetFont("FlappyFont"));
	mHighScoreText.setString(std::to_string(mHighScore));
	mHighScoreText.setCharacterSize(56);
	mHighScoreText.setFillColor(sf::Color::White);
	mHighScoreText.setOrigin(mHighScoreText.getGlobalBounds().width / 2, mHighScoreText.getGlobalBounds().height / 2);
	mHighScoreText.setPosition(mData->window.getSize().x / 10 * 7.25, mData->window.getSize().y / 1.78);

	if (mScore >= PLATINUM_MEDAL_SCORE)
	{
		mMedal.setTexture(mData->assets.GetTexture("PlatinumMedal"));
	}
	else if (mScore >= GOLD_MEDAL_SCORE)
	{
		mMedal.setTexture(mData->assets.GetTexture("GoldMedal"));
	}
	else if (mScore >= SILVER_MEDAL_SCORE)
	{
		mMedal.setTexture(mData->assets.GetTexture("SilverMedal"));
	}
	else
	{
		mMedal.setTexture(mData->assets.GetTexture("BronzeMedal"));
	}

	mMedal.setPosition(175, 465);
}

void GameOverState::HandleInput()
{
	sf::Event event;
	while (mData->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			mData->window.close();
		}
		if (mData->input.IsSpriteClicked(mRetryButton, sf::Mouse::Left, mData->window))
		{
			mData->machine.AddState(StateRef(new GameState(mData)), true);
		}
	}
}

void GameOverState::Update(float deltaTime)
{

}

void GameOverState::Draw(float deltaTime)
{
	mData->window.clear();
	mData->window.draw(mBackground);
	mData->window.draw(mGameOverContainer);
	mData->window.draw(mGameOverTitle);
	mData->window.draw(mRetryButton);
	mData->window.draw(mScoreText);
	mData->window.draw(mHighScoreText);
	mData->window.draw(mMedal);
	mData->window.display();
}

