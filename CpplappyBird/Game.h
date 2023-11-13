#pragma once

#include <memory>
#include <string>
#include <SFML\Graphics.hpp>
#include "Definitions.h"
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
	AssetManager assets;
	InputManager input;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{

public:

	Game(int width, int height, std::string title);

private:

	// FrameRate
	const float deltaTime = 1.0f / FRAMERATE;
	sf::Clock mClock;

	GameDataRef mData = std::make_shared<GameData>();

	void Run();

};

