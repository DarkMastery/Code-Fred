#include "stdafx.h"
#include "Objects/BulletBehavior.h"
#include "Engine.h"
#include "services/GraphicService.h"

BulletBehavior::BulletBehavior() {

}

BulletBehavior::~BulletBehavior() {

}

void BulletBehavior::Render(float dt) {
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


void BulletBehavior::Shoot() {

}

void BulletBehavior::Update() {
	auto dt = 1 / Engine::m_refreshRate;
	m_physicalBody_.posX += m_physicalBody_.velocityX * dt;
	m_physicalBody_.posY += m_physicalBody_.velocityY * dt;
	//	m_physicalBody_=m_nextFramePhysicalBody_;


	/*if (m_pCollisionDetector_ != nullptr) {
		auto tileCollisionVector = m_pCollisionDetector_->TileCollisionChecker(m_physicalBody_);
		// 如果你想针对不同的tile做出不同的行为，就在这个for循环中添加吧
		for (auto tileCollision : tileCollisionVector) {
			m_physicalBody_ = m_pCollisionDetector_->TileCollisionDefaultSolver(tileCollision, m_physicalBody_);

			switch (tileCollision.flag) {
			case Collision_down:
				
				break;
			default:
				break;
			}
		}*/
}

void BulletBehavior::MoveDown() {

}

void BulletBehavior::MoveUp() {

}

void BulletBehavior::MoveLeft() {

}

void BulletBehavior::MoveRight() {

}

