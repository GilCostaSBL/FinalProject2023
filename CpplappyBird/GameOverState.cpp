#include <sstream>
#include <iostream>
#include <fstream>
#include "GameOverState.hpp"
#include "Definitions.hpp"
#include "GameState.hpp"

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

	skyBackground.setTexture(mData->assets.GetTexture("GameOverStateBackground"));
	gameOverTitle.setTexture(mData->assets.GetTexture("GameOverStateTitle"));
	gameOverContainer.setTexture(mData->assets.GetTexture("GameOverStateBody"));
	retryButton.setTexture(mData->assets.GetTexture("PlayButton"));

	gameOverContainer.setPosition(mData->window.getSize().x / 2 - (gameOverContainer.getGlobalBounds().width / 2),
		(mData->window.getSize().y / 2) - (gameOverContainer.getGlobalBounds().height / 2));

	gameOverTitle.setPosition((mData->window.getSize().x / 2) - (gameOverTitle.getGlobalBounds().width / 2),
		gameOverContainer.getPosition().y - (gameOverTitle.getGlobalBounds().height * 1.2));

	retryButton.setPosition((mData->window.getSize().x / 2) - (gameOverTitle.getGlobalBounds().width / 2),
		gameOverContainer.getPosition().y + gameOverContainer.getGlobalBounds().height +
		retryButton.getLocalBounds().height * 0.2);

	scoreText.setFont(mData->assets.GetFont("FlappyFont"));
	scoreText.setString(std::to_string(mScore));
	scoreText.setCharacterSize(56);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
	scoreText.setPosition(mData->window.getSize().x / 10 * 7.25, mData->window.getSize().y / 2.15);

	highScoreText.setFont(mData->assets.GetFont("FlappyFont"));
	highScoreText.setString(std::to_string(mHighScore));
	highScoreText.setCharacterSize(56);
	highScoreText.setFillColor(sf::Color::White);
	highScoreText.setOrigin(highScoreText.getGlobalBounds().width / 2, highScoreText.getGlobalBounds().height / 2);
	highScoreText.setPosition(mData->window.getSize().x / 10 * 7.25, mData->window.getSize().y / 1.78);

	if (mScore >= PLATINUM_MEDAL_SCORE)
	{
		medalSlot.setTexture(mData->assets.GetTexture("PlatinumMedal"));
	}
	else if (mScore >= GOLD_MEDAL_SCORE)
	{
		medalSlot.setTexture(mData->assets.GetTexture("GoldMedal"));
	}
	else if (mScore >= SILVER_MEDAL_SCORE)
	{
		medalSlot.setTexture(mData->assets.GetTexture("SilverMedal"));
	}
	else
	{
		medalSlot.setTexture(mData->assets.GetTexture("BronzeMedal"));
	}

	medalSlot.setPosition(175, 465);
}

void GameOverState::HandleInput()
{

	sf::Event event;

	while (mData->window.pollEvent(event))
	{

		if (sf::Event::Closed == event.type)
			mData->window.close();

		if (mData->input.IsSpriteClicked(retryButton, sf::Mouse::Left, mData->window))
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
	mData->window.draw(skyBackground);
	mData->window.draw(gameOverContainer);
	mData->window.draw(gameOverTitle);
	mData->window.draw(retryButton);
	mData->window.draw(scoreText);
	mData->window.draw(highScoreText);
	mData->window.draw(medalSlot);
	mData->window.display();
}

