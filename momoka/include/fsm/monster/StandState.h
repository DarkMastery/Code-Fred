#pragma once
#include "fsm/MonsterState.h"

class StandState : public MonsterState {

public:
	explicit StandState(Monster& monster);

	~StandState() override;
	MonsterState* LeftKeyState(bool) override;
	MonsterState* RightKeyState(bool) override;
	MonsterState* JumpKeyState(bool) override;
	MonsterState* Onland() override;
	MonsterState* Update() override;
};
