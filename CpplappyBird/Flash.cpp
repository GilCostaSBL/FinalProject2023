#include "Flash.h"

Flash::Flash(GameDataRef data) : mData(data)
{
	flashShape = sf::RectangleShape(sf::Vector2f(mData->window.getSize()));
	flashShape.setFillColor(sf::Color(255, 255, 255, 0));

	isFlashOn = true;
}

void Flash::Show(float deltaTime)
{
	if (isFlashOn)
	{
		int alpha = (int) flashShape.getFillColor().a + (FLASH_SPEED * deltaTime);
		if (alpha >= 255.0f)
		{
			alpha = 255.0f;
			isFlashOn = false;
		}

		flashShape.setFillColor(sf::Color(255, 255, 255, alpha));
	}
	else
	{
		int alpha = (int) flashShape.getFillColor().a - (FLASH_SPEED * deltaTime);
		if (alpha <= 0.0f)
		{
			alpha = 0.0f;
		}

		flashShape.setFillColor(sf::Color(255, 255, 255, alpha));
	}
}

void Flash::Draw()
{
	mData->window.draw(flashShape);
}