#pragma once
#include "fsm/MonsterState.h"

class HurtState : public MonsterState {

public:
	explicit HurtState(Monster& monster);

	~HurtState() override;
	MonsterState* LeftKeyState(bool) override;
	MonsterState* RightKeyState(bool) override;
	MonsterState* JumpKeyState(bool) override;
	MonsterState* Update() override;

};