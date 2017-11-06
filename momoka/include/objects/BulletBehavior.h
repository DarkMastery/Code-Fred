#pragma once
#include "Entity.h"
#define BulletMaxNum 1
class BulletBehavior : public Entity {
public:
	explicit BulletBehavior();
	~BulletBehavior();

	virtual void Update() override;
	virtual void Render(float dt) override;

	virtual void MoveLeft() override;
	virtual void MoveRight() override;
	virtual void MoveUp() override;
	virtual void MoveDown() override;

	virtual void Shoot();

};