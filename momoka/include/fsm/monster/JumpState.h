#pragma once
#include "fsm/MonsterState.h"

class JumpState : public MonsterState {

public:
	explicit JumpState(Monster& monster);

	~JumpState() override;
	MonsterState* JumpKeyState(bool) override;
	MonsterState* Update() override;

private:
	float m_jumpingDate_;
};
