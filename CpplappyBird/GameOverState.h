#pragma once

#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"

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

	sf::Sprite mBackground;

	sf::Sprite mGameOverTitle;
	sf::Sprite mGameOverContainer;
	sf::Sprite mRetryButton;
	sf::Sprite mMedal;

	sf::Text mScoreText;
	sf::Text mHighScoreText;

	int mScore;
	int mHighScore;

};

