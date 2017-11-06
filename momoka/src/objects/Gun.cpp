#include "stdafx.h"
#include "Objects/Gun.h"
#include "Engine.h"
#include "services/GraphicService.h"

Gun::Gun(float x, float y) :m_defaultHorizontalVelocity_(400.f) {
	SecureZeroMemory(&m_physicalBody_, sizeof(PhysicalBody));
	SecureZeroMemory(&m_nextFramePhysicalBody_, sizeof(PhysicalBody));

	m_physicalBody_.collisionWidth = 1 * momoka_global::TILE_SIZE;
	m_physicalBody_.collisionHeight = 1 * momoka_global::TILE_SIZE;

	SetX(x);
	SetY(y);

}

float Gun::GetDefaultHorizontalVelocity() const{
	return m_defaultHorizontalVelocity_;
}

void Gun::Shoot() {
	this->SetVelocityX(GetDefaultHorizontalVelocity());
}