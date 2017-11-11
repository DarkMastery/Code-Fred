#pragma once
#include "fsm/MonsterState.h"

class RunningState : public MonsterState {

public:
	explicit RunningState(Monster& monster, bool isMoveLeft);

	~RunningState() override;

	MonsterState* LeftKeyState(bool) override;
	MonsterState* RightKeyState(bool) override;
	MonsterState* JumpKeyState(bool) override;
	MonsterState* Onland() override;
	MonsterState* Update() override;
};
