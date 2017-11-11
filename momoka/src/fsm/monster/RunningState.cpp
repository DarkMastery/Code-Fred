#include "stdafx.h"
#include "fsm/monster/RunningState.h"
#include "fsm/monster/FallingState.h"
#include "fsm/monster/JumpState.h"
#include "fsm/monster/StandState.h"
#include "fsm/monster/HurtState.h"
#include "util/Log.h"

RunningState::RunningState(Monster& monster, bool isMoveLeft)
	: MonsterState(monster) {
	if(isMoveLeft) {
		m_monster_.SetVelocityX(-m_monster_.GetDefaultHorizontalVelocity());
	}
	else {
		m_monster_.SetVelocityX(m_monster_.GetDefaultHorizontalVelocity());
	}

}

RunningState::~RunningState() {
}

MonsterState* RunningState::LeftKeyState(bool release) {
	if(release) {
		return new StandState(m_monster_);
	}
	return MonsterState::LeftKeyState(release);
}

MonsterState* RunningState::RightKeyState(bool release) {
	if (release) {
		return new StandState(m_monster_);
	}
	return MonsterState::RightKeyState(release);
}

MonsterState* RunningState::JumpKeyState(bool press) {
	if(press) {
		return new JumpState(m_monster_);
	}
	return MonsterState::JumpKeyState(press);
}

MonsterState* RunningState::Onland() {
	m_isOnland_ = true;
	return nullptr;
}

MonsterState* RunningState::Update() {
	if (!m_isOnland_) 
		return new FallingState(m_monster_);
/*	if (m_hero_.GetVelocityX() == 0)
		return new HurtState(m_hero_); *///HurtState≤‚ ‘
	return MonsterState::Update();
}
