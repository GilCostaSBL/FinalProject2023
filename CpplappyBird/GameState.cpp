#include <sstream>
#include <iostream>
#include "GameState.hpp"
#include "Definitions.hpp"
#include "GameOverState.hpp"

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

	if (!hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))
	{
		std::cout << "[GameState::Init] Hit sound could not be loaded" << std::endl;
	}
	if (!wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH))
	{
		std::cout << "[GameState::Init] Wing sound could not be loaded" << std::endl;
	}
	if (!pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
	{
		std::cout << "[GameState::Init] Point sound could not be loaded" << std::endl;
	}

	hitSound.setBuffer(hitSoundBuffer);
	wingSound.setBuffer(wingSoundBuffer);
	pointSound.setBuffer(pointSoundBuffer);

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

	skyBackground.setTexture(this->mData->assets.GetTexture("GameStateBackground"));
	mGameState = GameStates::eReady;

}

void GameState::HandleInput()
{

	sf::Event event;

	while (mData->window.pollEvent(event))
	{

		if (sf::Event::Closed == event.type)
			mData->window.close();

		if (mData->input.IsSpriteClicked(skyBackground, sf::Mouse::Left, mData->window))
		{
			if (GameStates::eGameOver != mGameState)
			{

				mGameState = GameStates::ePlaying;
				bird->Tap();
				wingSound.play();
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

				hitSound.play();
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

				hitSound.play();
			}
		}


		if (GameStates::ePlaying == mGameState)
		{

			// Scoring pipe collision
			std::vector<sf::Sprite>& scoringSprites = pipe->GetScoringSprites();
			//std::cout << "Sp: " << scoringSprites.size() << std::endl;

			for (int i = 0; i < scoringSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, scoringSprites.at(i), 1.0f))
				{

					mScore++;

					hud->UpdateScore(mScore);

					scoringSprites.erase(scoringSprites.begin() + i);

					pointSound.play();
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

	mData->window.draw(skyBackground);
	pipe->DrawPipes();
	land->DrawLand();
	bird->Draw();
	flash->Draw();
	hud->Draw();

	mData->window.display();
}


