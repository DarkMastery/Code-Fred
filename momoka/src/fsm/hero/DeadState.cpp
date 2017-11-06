#include "stdafx.h"
#include "fsm/hero/FallingState.h"
#include "fsm/hero/StandState.h"
#include "fsm/hero/DeadState.h"
#include "util/Log.h"
#include "Engine.h"

extern bool gameover;

DeadState::DeadState(Hero& hero)
	: HeroState(hero) {
	MOMOKA_LOG(momoka::debug) << "Switch to Dead State";
}

DeadState::~DeadState()
{}

HeroState* DeadState::Update()
{
	gameover = true;
	return nullptr;
}