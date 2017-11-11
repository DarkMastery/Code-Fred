#include "stdafx.h"
#include "fsm/monster/JumpState.h"
#include "fsm/monster/FallingState.h"
#include "fsm/monster/HurtState.h"
#include "util/Log.h"

JumpState::JumpState(Monster& monster)
	: MonsterState(monster), m_jumpingDate_(0) {
	m_monster_.SetVelocityY(-1200);
}

JumpState::~JumpState() {
}

MonsterState* JumpState::JumpKeyState(bool release) {
	if(release) {
		return new FallingState(m_monster_);
	}
	return MonsterState::JumpKeyState(release);
}

MonsterState* JumpState::Update() {
	if (m_monster_.GetVelocityY() != 0) {  // 判断有没有碰到顶
		m_jumpingDate_ += 1 / momoka_global::REFRESH_RATE;
		if (m_jumpingDate_ > 0.15) {
			return new FallingState(m_monster_);
		}
		return MonsterState::Update();
	}
	else {
		return new FallingState(m_monster_);
	}
}
