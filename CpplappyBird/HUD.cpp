#include "HUD.hpp"

HUD::HUD(GameDataRef data) : mData(data)
{

	scoreText.setFont(mData->assets.GetFont("FlappyFont"));
	scoreText.setString("0");
	scoreText.setCharacterSize(128);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
	scoreText.setPosition(mData->window.getSize().x / 2, mData->window.getSize().y / 5);

}

void HUD::Draw()
{

	mData->window.draw(scoreText);
}

void  HUD::UpdateScore(int score)
{

	scoreText.setString(std::to_string(score));
}
