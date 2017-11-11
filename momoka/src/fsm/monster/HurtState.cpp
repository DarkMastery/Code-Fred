#include "stdafx.h"
#include "fsm/monster/FallingState.h"
#include "fsm/monster/StandState.h"
#include "fsm/monster/HurtState.h"
#include "util/Log.h"
#include "fsm/monster/JumpState.h"
#include "fsm/monster/RunningState.h"

bool m_ishurt_ = true;

HurtState::HurtState(Monster& monster)
	: MonsterState(monster) {
	m_monster_.SetVelocityX(-300);
	m_monster_.SetVelocityY(-600);
	m_ishurt_ = true;
}

HurtState::~HurtState() {
}



MonsterState* HurtState::LeftKeyState(bool b) {
	return nullptr;
}

MonsterState* HurtState::RightKeyState(bool b) {
	return nullptr;
}

MonsterState* HurtState::JumpKeyState(bool b) {
	return nullptr;
}

MonsterState* HurtState::Update() {
	if (m_ishurt_==false&&m_monster_.GetVelocityY() == 0)
		return new StandState(m_monster_);
	else if (m_monster_.GetVelocityY() < 1300.f) {
		m_monster_.SetVelocityY(m_monster_.GetVelocityY() + 50);
		m_ishurt_ = false;
	}
//	m_hero_.SetHp(m_hero_.GetHp()-);
	return MonsterState::Update();
}