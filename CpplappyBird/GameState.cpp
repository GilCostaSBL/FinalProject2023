#include <sstream>
#include <iostream>
#include "GameState.h"
#include "Definitions.h"
#include "GameOverState.h"

GameState::GameState(GameDataRef data) : mData(data)
{
	std::cout << "[GameState::GameState] Game state" << std::endl;
}

GameState::~GameState()
{
	delete pipe;
	delete land;
	delete bird;
	delete flash;
	delete hud;
}

void GameState::Init()
{
	if (!mHitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))
	{
		std::cout << "[GameState::Init] Hit sound could not be loaded" << std::endl;
	}
	if (!mWingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH))
	{
		std::cout << "[GameState::Init] Wing sound could not be loaded" << std::endl;
	}
	if (!mPointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
	{
		std::cout << "[GameState::Init] Point sound could not be loaded" << std::endl;
	}

	mHitSound.setBuffer(mHitSoundBuffer);
	mWingSound.setBuffer(mWingSoundBuffer);
	mPointSound.setBuffer(mPointSoundBuffer);

	mData->assets.LoadTexture("GameStateBackground", GAME_STATE_BACKGROUND_FILEPATH);
	mData->assets.LoadTexture("PipeUp", PIPE_UP_FILEPATH);
	mData->assets.LoadTexture("PipeDown", PIPE_DOWN_FILEPATH);
	mData->assets.LoadTexture("ScoringPipe", PIPE_SCORING_FILEPATH);
	mData->assets.LoadTexture("Land", LAND_FILEPATH);
	mData->assets.LoadTexture("BirdFrame1", BIRD_FRAME_1_FILEPATH);
	mData->assets.LoadTexture("BirdFrame2", BIRD_FRAME_2_FILEPATH);
	mData->assets.LoadTexture("BirdFrame3", BIRD_FRAME_3_FILEPATH);
	mData->assets.LoadTexture("BirdFrame4", BIRD_FRAME_4_FILEPATH);
	mData->assets.LoadFont("FlappyFont", FLAPPY_FONT_FILEPATH);

	pipe = new Pipe(mData);
	land = new Land(mData);
	bird = new Bird(mData);
	flash = new Flash(mData);
	hud = new HUD(mData);

	mScore = 0;
	hud->UpdateScore(mScore);

	mBackground.setTexture(this->mData->assets.GetTexture("GameStateBackground"));
	mGameState = GameStates::eReady;

}

void GameState::HandleInput()
{
	sf::Event event;
	while (mData->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			mData->window.close();
		}
		if (mData->input.IsSpriteClicked(mBackground, sf::Mouse::Left, mData->window))
		{
			if (GameStates::eGameOver != mGameState)
			{
				mGameState = GameStates::ePlaying;
				bird->Fly();
				mWingSound.play();
			}
		}
	}
}

void GameState::Update(float deltaTime)
{
	if (GameStates::eGameOver != mGameState)
	{
		bird->Animate(deltaTime);
		land->MoveLand(deltaTime);
	}

	if (GameStates::ePlaying == mGameState)
	{
		pipe->MovePipes(deltaTime);
		if (mClock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
		{
			pipe->RandomisePipeOffset();

			pipe->SpawnInvisiblePipe();
			pipe->SpawnBottomPipe();
			pipe->SpawnTopPipe();
			pipe->SpawnScoringPipe();

			mClock.restart();
		}

		bird->Update(deltaTime);

		// Ground collision
		std::vector<sf::Sprite> landSprites = land->GetSprites();
		for (int i = 0; i < landSprites.size(); i++)
		{
			if (collision.CheckSpriteCollision(bird->GetSprite(), 0.7f, landSprites.at(i), 1.0f))
			{
				mGameState = GameStates::eGameOver;
				mClock.restart();
				mHitSound.play();
			}
		}

		// Pipe collision
		std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();

		for (int i = 0; i < pipeSprites.size(); i++)
		{
			if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, pipeSprites.at(i), 1.0f))
			{
				mGameState = GameStates::eGameOver;
				mClock.restart();
				mHitSound.play();
			}
		}

		if (GameStates::ePlaying == mGameState)
		{
			// Scoring pipe collision
			std::vector<sf::Sprite>& scoringSprites = pipe->GetScoringSprites();
			for (int i = 0; i < scoringSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, scoringSprites.at(i), 0.9f))
				{
					mScore++;
					hud->UpdateScore(mScore);
					scoringSprites.erase(scoringSprites.begin() + i);
					mPointSound.play();
				}
			}
		}
	}

	// GameOver flash
	if (GameStates::eGameOver == mGameState)
	{
		flash->Show(deltaTime);

		if (mClock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER)
			mData->machine.AddState(StateRef(new GameOverState(mData, mScore)), true);
	}
}

void GameState::Draw(float deltaTime)
{
	mData->window.clear();

	mData->window.draw(mBackground);
	pipe->DrawPipes();
	land->DrawLand();
	bird->Draw();
	flash->Draw();
	hud->Draw();

	mData->window.display();
}


