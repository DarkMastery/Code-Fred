#include "stdafx.h"
#include "Engine.h"
#include "objects/Monster.h"
#include "services/GraphicService.h"
#include "fsm/monster/StandState.h"

#include "util/Log.h"

Monster::Monster() : m_defaultHorizontalVelocity_(400.f), m_state_(new StandState(*this)), m_bulletnum_(0) {
	SecureZeroMemory(&m_physicalBody_, sizeof(PhysicalBody));
	SecureZeroMemory(&m_nextFramePhysicalBody_, sizeof(PhysicalBody));

	m_physicalBody_.collisionWidth = 1 * momoka_global::TILE_SIZE;
	m_physicalBody_.collisionHeight = 2 * momoka_global::TILE_SIZE;
}

Monster::~Monster() {
}

void Monster::Render(float dt) {
	auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(
		SERVICE_TYPE::Service_graphic).lock();
	float x = m_physicalBody_.posX + m_physicalBody_.velocityX * (dt / 1000);
	float y = m_physicalBody_.posY + m_physicalBody_.velocityY * (dt / 1000);

	float next_x = m_nextFramePhysicalBody_.posX;
	float next_y = m_nextFramePhysicalBody_.posY;

	//		if (x > next_x && m_physicalBody_.velocityX > 0 || x < next_x && m_physicalBody_.velocityX < 0) {
	//			x = next_x;
	//		}
	//	
	//		if (y > next_y && m_physicalBody_.velocityY > 0 || y < next_y && m_physicalBody_.velocityY < 0) {
	//			y = next_y;
	//		}

	pGraphicService->DrawRect(x, y, momoka_global::TILE_SIZE, momoka_global::TILE_SIZE * 2);

}

void Monster::MoveLeft() {

}

void Monster::MoveRight() {

}

void Monster::MoveUp() {
	//	m_velocityY_ = -m_defaultHorizontalVelocity_;
}

void Monster::MoveDown() {
	//	m_velocityY_ = m_defaultHorizontalVelocity_;
}

void Monster::Jump() {

}

int Monster::GetBulletNum() const {
	return m_bulletnum_;
}

void Monster::SetBulletNum(int bulletnum) {
	m_bulletnum_ = bulletnum;
}

int Monster::GetHp() const {
	return m_hp_;
}

void Monster::SetHp(int hp) {
	m_hp_ = hp;
}

void Monster::PerformShoot() {
	m_bulletbehavior_.Shoot();
}

void Monster::SetBulletBehavior(BulletBehavior bullet) {
	m_bulletbehavior_ = bullet;
}


bool Monster::SwitchState(MonsterState* state) {
	if (state != nullptr) {
		SafeDelete(&m_state_);
		m_state_ = state;
		return true;
	}
	return false;
}

void Monster::Onland() {
	SwitchState(m_state_->Onland());
}

float Monster::GetDefaultHorizontalVelocity() const {
	return m_defaultHorizontalVelocity_;
}



void Monster::Update() {
	auto dt = 1 / Engine::m_refreshRate;
	m_physicalBody_.posX += m_physicalBody_.velocityX * dt;
	m_physicalBody_.posY += m_physicalBody_.velocityY * dt;
	//	m_physicalBody_=m_nextFramePhysicalBody_;


	SwitchState(m_state_->Update());
	if (m_pCollisionDetector_ != nullptr) {
		auto tileCollisionVector = m_pCollisionDetector_->TileCollisionChecker(m_physicalBody_);
		// 如果你想针对不同的tile做出不同的行为，就在这个for循环中添加吧
		for (auto tileCollision : tileCollisionVector) {
			m_physicalBody_ = m_pCollisionDetector_->TileCollisionDefaultSolver(tileCollision, m_physicalBody_);

			switch (tileCollision.flag) {
			case Collision_down:
				SwitchState(m_state_->Onland());
				break;
			case Collision_right:
				SwitchState(m_state_->Update());
			default:
				break;
			}
		}
	}

	//		if (m_pCollisionDetector_ != nullptr) {
	//			m_nextFramePhysicalBody_ = m_physicalBody_;
	//			m_nextFramePhysicalBody_.posX += m_physicalBody_.velocityX * dt;
	//			m_nextFramePhysicalBody_.posY += m_physicalBody_.velocityY * dt;
	//			auto tileCollisionVector = m_pCollisionDetector_->TileCollisionChecker(m_nextFramePhysicalBody_);
	//			for (auto tileCollision : tileCollisionVector) {
	//				m_nextFramePhysicalBody_ = m_pCollisionDetector_->TileCollisionDefaultSolver(tileCollision, m_nextFramePhysicalBody_);
	//			}
	//		}
}
