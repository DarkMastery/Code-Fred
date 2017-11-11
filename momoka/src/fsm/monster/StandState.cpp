#include "stdafx.h"
#include "fsm/monster/StandState.h"
#include "fsm/monster/JumpState.h"
#include "fsm/monster/RunningState.h"
#include "fsm/monster/FallingState.h"
#include "fsm/monster/HurtState.h"
#include "util/Log.h"

StandState::StandState(Monster& monster)
	: MonsterState(monster) {
	m_monster_.SetVelocityX(0);
	m_monster_.SetVelocityY(0);
}

StandState::~StandState() {
}

MonsterState* StandState::LeftKeyState(bool press) {
	if (press) {
		return new RunningState(m_monster_, true);
	}
	return MonsterState::LeftKeyState(press);
}

MonsterState* StandState::RightKeyState(bool press) {
	if (press) {
		return new RunningState(m_monster_, false);
	}
	return MonsterState::RightKeyState(press);
}

MonsterState* StandState::JumpKeyState(bool press) {
	if (press) {
		return new JumpState(m_monster_);
	}
	return MonsterState::JumpKeyState(press);
}

MonsterState* StandState::Onland() {
	m_isOnland_ = true;
	return nullptr;
}

MonsterState* StandState::Update() {
	if (!m_isOnland_) {
		return new FallingState(m_monster_);
	}
	m_isOnland_ = false;
	return nullptr;
}
