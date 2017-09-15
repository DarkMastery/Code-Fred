#pragma once

class Entity {
public:
	virtual ~Entity();
	float GetX();
	float GetY();

	float GetCollisionWidth();
	float GetCollisionHeight();

	bool IsObstructive();
	bool HasGravity();

	virtual bool Update();
	virtual bool Render(float dt);

	void SetX(float x);
	void SetY(float y);

protected:
	// ��ײ��־��false�����ᷢ����ײ���������ײָ�������ϰ�����ײ
	bool m_isObstructive_;
	bool m_hasGravity_;

	bool m_leftObstructFlag_;
	bool m_rightObstructFlag_;
	bool m_upObstructFlag_;
	bool m_downObstructFlag_;

	float m_posX_;
	float m_posY_;

	float m_collisionWidth_;
	float m_collisionHeight_;

};
