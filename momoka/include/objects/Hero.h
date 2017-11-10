#pragma once
#include "objects/Entity.h"
#include "fsm/HeroState.h"
#include "BulletBehavior.h"
#include "Gun.h"
#define MaxOwnedGun 3
class HeroState;
class Hero : public Entity {

public:
	explicit Hero();

	~Hero();
	void Update() override;
	void Render(float dt) override;

	void MoveLeft() override;
	void MoveRight() override;
	void MoveUp() override;
	void MoveDown() override;

	void Jump() override;

	void Onland() override;

	int GetJumpNum() const;
	void SetJumpNum(int);

	int GetBulletNum() const;
	void SetBulletNum(int);

	int GetHp() const;
	void SetHp(int);

	void PerformShoot();
	void SetBulletBehavior(BulletBehavior);

	float GetDefaultHorizontalVelocity() const;

private:
	void HandleInput() override;
	bool SwitchState(HeroState* state);

	float m_defaultHorizontalVelocity_;
	HeroState* m_state_;
	int m_hp_;
	int m_jumpnumber_;
	int m_bulletnum_;
	//int m_gunowned_[MaxOwnedGun];
	BulletBehavior m_bulletbehavior_;//[BulletMaxNum];
};
