#include "stdafx.h"
#include "fsm/HeroState.h"
#include "util/Log.h"

HeroState::HeroState(Hero& hero) : m_hero_(hero),
                                   m_isOnland_(true) {
}

void HeroState::ClearFlag() {
	m_isOnland_ = false;
}

HeroState* HeroState::LeftKeyState(INPUT_KEY_EVENT keyEvent) {
	if(keyEvent == Key_press || keyEvent == Key_down) {
		m_hero_.SetVelocityX(-m_hero_.GetDefaultHorizontalVelocity());
	}
	else if(keyEvent == Key_release) {
		m_hero_.SetVelocityX(0);
	}
	return nullptr;
}

HeroState* HeroState::ShootKeyState(INPUT_KEY_EVENT keyEvent) {
	if (m_hero_.GetBulletNum() < BulletMaxNum) {
		MOMOKA_LOG(momoka::debug) << "Shoot a bullet";
		/*switch():
		case:
		case:*/ //根据当前武器类型产生子弹
		BulletBehavior  *bullet;
		bullet = new Gun(m_hero_.GetX() + 1, m_hero_.GetY());
		m_hero_.SetBulletBehavior(*bullet);
		m_hero_.PerformShoot();
	}
	return nullptr;
}


HeroState* HeroState::RightKeyState(INPUT_KEY_EVENT keyEvent) {
	if (keyEvent == Key_press || keyEvent == Key_down) {
		m_hero_.SetVelocityX(m_hero_.GetDefaultHorizontalVelocity());
	}
	else if (keyEvent == Key_release) {
		m_hero_.SetVelocityX(0);
	}
	return nullptr;
}

HeroState* HeroState::JumpKeyState(INPUT_KEY_EVENT keyEvent) {
	return nullptr;
}

HeroState* HeroState::Onland() {
	return nullptr;
}

HeroState* HeroState::Update() {
	ClearFlag();
	return nullptr;
}
