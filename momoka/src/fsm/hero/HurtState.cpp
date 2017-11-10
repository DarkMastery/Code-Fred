#include "stdafx.h"
#include "fsm/hero/FallingState.h"
#include "fsm/hero/StandState.h"
#include "fsm/hero/HurtState.h"
#include "util/Log.h"
#include "fsm/hero/JumpState.h"
#include "fsm/hero/RunningState.h"

bool m_ishurt_ = true;

HurtState::HurtState(Hero& hero)
	: HeroState(hero) {	
	m_hero_.SetVelocityX(-600);
	m_hero_.SetVelocityY(-1200);
	m_ishurt_ = true;
	MOMOKA_LOG(momoka::debug) << "Switch to Hurt State";
}

HurtState::~HurtState() {
}



HeroState* HurtState::LeftKeyState(INPUT_KEY_EVENT keyEvent) {
	return nullptr;
}

HeroState* HurtState::RightKeyState(INPUT_KEY_EVENT keyEvent) {
	return nullptr;
}

HeroState* HurtState::JumpKeyState(INPUT_KEY_EVENT keyEvent) {
	return nullptr;
}

HeroState* HurtState::Update() {
	if (m_ishurt_==false&&m_hero_.GetVelocityY() == 0)
		return new StandState(m_hero_);
	else if (m_hero_.GetVelocityY() < 1300.f) {
		m_hero_.SetVelocityY(m_hero_.GetVelocityY() + 200);
		m_ishurt_ = false;
	}
//	m_hero_.SetHp(m_hero_.GetHp()-);
	return HeroState::Update();
}