#include "stdafx.h"
#include "fsm/monster/FallingState.h"
#include "fsm/monster/StandState.h"
#include "util/Log.h"
#include "fsm/monster/JumpState.h"
#include "fsm/monster/DeadState.h"

FallingState::FallingState(Monster& monster)
	: MonsterState(monster) {
}

FallingState::~FallingState() {
}

MonsterState* FallingState::Onland() {
	return new StandState(m_monster_);
}


MonsterState* FallingState::JumpKeyState(bool b) {
	return MonsterState::JumpKeyState(b);
}

MonsterState* FallingState::Update() {
	if (m_monster_.GetVelocityY() < 1300.f) {
		m_monster_.SetVelocityY(m_monster_.GetVelocityY() + 200);
	}
	if (m_monster_.GetY() > 800) {
		return new DeadState(m_monster_);
	}
	return MonsterState::Update();
}