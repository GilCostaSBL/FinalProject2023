#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include "Collision.hpp"
#include "Flash.hpp"
#include "HUD.hpp"

class GameState : public State
{

public:

	GameState(GameDataRef data);
	~GameState();
	void Init();
	void HandleInput();
	void Update(float deltaTime);
	void Draw(float deltaTime);

private:

	GameDataRef mData;

	sf::Sprite skyBackground;

	sf::Clock mClock;
	Pipe* pipe;
	Land* land;
	Bird* bird;
	Flash* flash;
	Collision collision;
	HUD* hud;

	sf::SoundBuffer hitSoundBuffer;
	sf::SoundBuffer wingSoundBuffer;
	sf::SoundBuffer pointSoundBuffer;

	sf::Sound hitSound;
	sf::Sound wingSound;
	sf::Sound pointSound;

	int mGameState;

	int mScore;

};

