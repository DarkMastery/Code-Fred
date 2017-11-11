#include "stdafx.h"
#include "fsm/monster/FallingState.h"
#include "fsm/monster/StandState.h"
#include "fsm/monster/DeadState.h"
#include "util/Log.h"
#include "Engine.h"


DeadState::DeadState(Monster& monster)
	: MonsterState(monster) {
	
}

DeadState::~DeadState()
{}

MonsterState* DeadState::Update()
{
	return nullptr;
}