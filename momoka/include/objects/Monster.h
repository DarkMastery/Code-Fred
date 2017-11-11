#pragma once
#include "objects/Entity.h"
#include "fsm/MonsterState.h"
#include "BulletBehavior.h"
#include "Gun.h"
class MonsterState;
class Monster : public Entity {

public:
	explicit Monster();

	~Monster();
	void Update() override;
	void Render(float dt) override;

	void MoveLeft() override;
	void MoveRight() override;
	void MoveUp() override;
	void MoveDown() override;

	void Jump() override;

	void Onland() override;

	int GetBulletNum() const;
	void SetBulletNum(int);

	int GetHp() const;
	void SetHp(int);

	void PerformShoot();
	void SetBulletBehavior(BulletBehavior);

	float GetDefaultHorizontalVelocity() const;

private:
	bool SwitchState(MonsterState* state);

	float m_defaultHorizontalVelocity_;
	MonsterState* m_state_;
	int m_hp_;
	int m_bulletnum_;
	BulletBehavior m_bulletbehavior_;
};
