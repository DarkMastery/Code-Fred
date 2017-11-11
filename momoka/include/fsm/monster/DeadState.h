#pragma once
#include "fsm/MonsterState.h"

class DeadState : public MonsterState {

public:
	explicit DeadState(Monster& monster);

	~DeadState() override;
	MonsterState* Update() override;
};
