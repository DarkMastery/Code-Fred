#pragma once
#include "fsm/HeroState.h"

class DeadState : public HeroState {

public:
	explicit DeadState(Hero& hero);

	~DeadState() override;
	HeroState* Update() override;
};
