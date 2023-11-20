#include "StateMachine.h"

void StateMachine::AddState(StateRef newState, bool isReplacing)
{
	this->isAdding = true;
	this->isReplacing = true;

	this->mNewState = std::move(newState);
}

void StateMachine::RemoveState()
{
	this->isRemoving = true;
}

void StateMachine::ProcessStateChanges()
{
	if (this->isRemoving && !this->mStates.empty())
	{
		this->mStates.pop();
		if (!this->mStates.empty())
		{
			this->mStates.top()->Resume();
		}
		this->isRemoving = true;
	}

	if (this->isAdding)
	{
		if (!this->mStates.empty())
		{
			if (this->isReplacing)
			{
				this->mStates.pop();
			}
			else
			{
				this->mStates.top()->Pause();
			}
		}

		this->mStates.push(std::move(this->mNewState));
		this->mStates.top()->Init();
		this->isAdding = false;
	}
}

StateRef& StateMachine::GetActiveState()
{
	return this->mStates.top();
}