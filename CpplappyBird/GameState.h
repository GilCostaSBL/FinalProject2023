#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "State.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Collision.h"
#include "Flash.h"
#include "HUD.h"

class GameState : public State
{

public:

	GameState(GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:

	GameDataRef mData;

	sf::Sprite mBackground;

	sf::Clock mClock;
	Pipe* pipe;
	Land* land;
	Bird* bird;
	Flash* flash;
	Collision collision;
	HUD* hud;

	sf::SoundBuffer mHitSoundBuffer;
	sf::SoundBuffer mWingSoundBuffer;
	sf::SoundBuffer mPointSoundBuffer;

	sf::Sound mHitSound;
	sf::Sound mWingSound;
	sf::Sound mPointSound;

	int mGameState;

	int mScore;

};
