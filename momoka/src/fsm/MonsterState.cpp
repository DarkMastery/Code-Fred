#include "stdafx.h"
#include "fsm/MonsterState.h"

MonsterState::MonsterState(Monster& monster) : m_monster_(monster),
m_isOnland_(true) {
}

void MonsterState::ClearFlag() {
	m_isOnland_ = false;
}

MonsterState* MonsterState::LeftKeyState(bool press) {
	if (press) {
		m_monster_.SetVelocityX(m_monster_.GetDefaultHorizontalVelocity());
	}
	else {
		m_monster_.SetVelocityX(0);
	}
	return nullptr;
}

MonsterState* MonsterState::ShootKeyState(bool b) {
	if (m_monster_.GetBulletNum() < BulletMaxNum) {
		/*switch():
		case:
		case:*/ //根据当前武器类型产生子弹
		BulletBehavior  *bullet;
		bullet = new Gun(m_monster_.GetX() + 1, m_monster_.GetY());
		m_monster_.SetBulletBehavior(*bullet);
		m_monster_.PerformShoot();
	}
	return nullptr;
}


MonsterState* MonsterState::RightKeyState(bool press) {
	if (press) {
		m_monster_.SetVelocityX(m_monster_.GetDefaultHorizontalVelocity());
	}
	else {
		m_monster_.SetVelocityX(0);
	}
	return nullptr;
}

MonsterState* MonsterState::JumpKeyState(bool b) {
	return nullptr;
}

MonsterState* MonsterState::Onland() {
	return nullptr;
}

MonsterState* MonsterState::Update() {
	ClearFlag();
	return nullptr;
}
