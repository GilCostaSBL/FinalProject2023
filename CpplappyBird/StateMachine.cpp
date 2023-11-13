#include "StateMachine.hpp"

StateMachine::StateMachine()
{

}

StateMachine::~StateMachine()
{

}

void StateMachine::AddState(StateRef newState, bool isReplacing)
{
	isAdding = true;
	isReplacing = true;

	newState = std::move(newState);
}

void StateMachine::RemoveState()
{
	isRemoving = true;
}

void StateMachine::ProcessStateChanges()
{
	// Check for flags to change states && is the stack is not empty
	if (isRemoving && !mStates.empty())
	{
		mStates.pop();
		if (!mStates.empty())
		{
			mStates.top()->Resume();
		}
		isRemoving = true;
	}

	if (isAdding)
	{
		if (!mStates.empty())
		{
			if (isReplacing)
			{
				mStates.pop();
			}
			else
			{
				mStates.top()->Pause();
			}
		}

		mStates.push(std::move(newState));
		mStates.top()->Init();
		isAdding = false;
	}
}

const StateRef& StateMachine::GetActiveState()
{
	return mStates.top();
}