#pragma once

class State
{

public:

	virtual void Init() = 0;

	virtual void HandleInput() = 0;
	virtual void Update(float deltaTime) = 0;
	// deltaTime : time difference, allows to draw
	// independently from the frame rate
	virtual void Draw(float deltaTime) = 0;

	virtual void Pause() {}
	virtual void Resume() {}
};