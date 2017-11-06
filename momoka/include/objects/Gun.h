#pragma once
#include "BulletBehavior.h"
class Gun : public BulletBehavior {
public:
	Gun(float, float);
	void Shoot();
	float GetDefaultHorizontalVelocity() const;
private:
	float m_defaultHorizontalVelocity_;
};