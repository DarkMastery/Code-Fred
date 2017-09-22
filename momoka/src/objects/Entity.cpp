#include "stdafx.h"
#include "objects/Entity.h"
#include "util/TileInfo.h"

Entity::~Entity() {
}

float Entity::GetX() const {
	return m_posX_;
}

float Entity::GetY() const {
	return m_posY_;
}

float Entity::GetCollisionWidth() const {
	return m_collisionWidth_;
}

float Entity::GetCollisionHeight() const {
	return m_collisionHeight_;
}

bool Entity::IsObstructive() const {
	return m_isObstructive_;
}

bool Entity::HasGravity() const {
	return m_hasGravity_;
}

void Entity::Update() {
}

void Entity::Render(float dt) {
}

void Entity::SetX(float x) {
	m_posX_ = x;
}

void Entity::SetY(float y) {
	m_posY_ = y;
}

void Entity::MoveLeft() {
}

void Entity::MoveRight() {
}

void Entity::MoveUp() {
}

void Entity::MoveDown() {
}

void Entity::Jump() {
}

bool Entity::TakeTileCollision(COLLISION_FLAG flag, TileInfo tileInfo) {
	if(flag == COLLISION_FLAG::Collision_left) {
		m_leftObstructFlag_ = true;
		if(m_velocityX_<=0) {
			m_velocityX_ = 0;
		}
	}
	if (flag == COLLISION_FLAG::Collision_right) {
		m_rightObstructFlag_ = true;
		if (m_velocityX_ >= 0) {
			m_velocityX_ = 0;
		}
	}
	if (flag == COLLISION_FLAG::Collision_up) {
		m_upObstructFlag_ = true;
		if (m_velocityY_ <= 0) {
			m_velocityY_ = 0;
		}
	}
	if (flag == COLLISION_FLAG::Collision_down) {
		m_downObstructFlag_ = true;
		if (m_velocityY_ >= 0) {
			m_velocityY_ = 0;
		}
	}

	return true;
}

void Entity::ClearObstructFlags() {
	m_downObstructFlag_ = false;
	m_upObstructFlag_ = false;
	m_leftObstructFlag_ = false;
	m_rightObstructFlag_ = false;
}

float Entity::GetVelocityX() const {
	return m_velocityX_;
}

float Entity::GetVelocityY() const {
	return m_velocityY_;
}

void Entity::SetVelocityX(float velocityX) {
	m_velocityX_ = velocityX;
}

void Entity::SetVelocityY(float velocityY) {
	m_velocityY_ = velocityY;
}

void Entity::SetOnLandFlag(bool flag) {
	m_isOnLand_ = flag;
}