#pragma once

#include <memory>
#include <stack>
#include "State.hpp"

typedef std::unique_ptr<State> StateRef;

class StateMachine
{
public:

	StateMachine();
	~StateMachine();

	void AddState(StateRef newState, bool isReplacing = true);
	void RemoveState();

	void ProcessStateChanges();

	const StateRef& GetActiveState();

private:

	std::stack<StateRef> mStates;		// All the states
	StateRef newState;					// Latest state to add

	bool isRemoving = false;
	bool isAdding = false;
	bool isReplacing = false;
};