#pragma once
#include "fsm/MonsterState.h"

class FallingState : public MonsterState {

public:
	explicit FallingState(Monster& monster);

	~FallingState() override;
	MonsterState* Onland() override;
	MonsterState* Update() override;
	MonsterState* JumpKeyState(bool) override;
};
