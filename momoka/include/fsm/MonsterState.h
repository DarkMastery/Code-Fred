#pragma once
#include "objects/Monster.h" 

class Monster;
class MonsterState {
public:
	explicit MonsterState(Monster& monster);
	virtual ~MonsterState() = default;

	void ClearFlag();

	virtual MonsterState* LeftKeyState(bool);
	virtual MonsterState* RightKeyState(bool);
	virtual MonsterState* JumpKeyState(bool);
	virtual MonsterState* ShootKeyState(bool);

	virtual MonsterState* Onland();
	virtual MonsterState* Update();
protected:
	Monster& m_monster_;

	bool m_isOnland_;
};