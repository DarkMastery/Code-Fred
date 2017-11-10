#pragma once
#include "fsm/HeroState.h"

class HurtState : public HeroState {

public:
	explicit HurtState(Hero& hero);

	~HurtState() override;
	HeroState* LeftKeyState(INPUT_KEY_EVENT keyEvent) override;
	HeroState* RightKeyState(INPUT_KEY_EVENT keyEvent) override;
	HeroState* JumpKeyState(INPUT_KEY_EVENT keyEvent) override;
	HeroState* Update() override;

};