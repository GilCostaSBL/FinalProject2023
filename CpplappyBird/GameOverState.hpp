#pragma once

#include <SFML\Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

class GameOverState : public State
{

public:

	GameOverState(GameDataRef data, int score);

	void Init();
	void HandleInput();
	void Update(float deltaTime);
	void Draw(float deltaTime);

private:

	GameDataRef mData;

	sf::Sprite skyBackground;

	sf::Sprite gameOverTitle;
	sf::Sprite gameOverContainer;
	sf::Sprite retryButton;
	sf::Sprite medalSlot;

	sf::Text scoreText;
	sf::Text highScoreText;

	int mScore;
	int mHighScore;

};

