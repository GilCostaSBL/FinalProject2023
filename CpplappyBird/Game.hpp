#pragma once

#include <memory>
#include <string>
#include <SFML\Graphics.hpp>
#include "Definitions.hpp"
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

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
	~Game() {}
private:

	// Making the game framerate indepedent
	const float deltaTime = 1.0f / FRAMERATE;
	sf::Clock mClock;

	GameDataRef mData = std::make_shared<GameData>();

	void Run();

};
