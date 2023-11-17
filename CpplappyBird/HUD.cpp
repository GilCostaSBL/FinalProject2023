#include "HUD.h"

HUD::HUD(GameDataRef data) : mData(data)
{
	mScoreText.setFont(mData->assets.GetFont("FlappyFont"));
	mScoreText.setString("0");
	mScoreText.setCharacterSize(128);
	mScoreText.setFillColor(sf::Color::White);
	mScoreText.setOrigin(mScoreText.getGlobalBounds().width / 2, mScoreText.getGlobalBounds().height / 2);
	mScoreText.setPosition(mData->window.getSize().x / 2, mData->window.getSize().y - 150);
}

void HUD::Draw()
{
	mData->window.draw(mScoreText);
}

void  HUD::UpdateScore(int score)
{
	mScoreText.setString(std::to_string(score));
}
