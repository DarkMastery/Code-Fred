#include "stdafx.h"
#include "components/CollisionDetector.h"
#include "components/PhysicalBody.h"


const TileKeyVector& CollisionDetector::EntityToTile(PhysicalBody& physicalBody) {
	m_tileKeyVector_.clear();

	/* ��һ��entity����߻��ϱ���tile���ڵ�δ�غ�ʱ�����ڲ�����������λ�ö�Ӧtileʱ���õ�������
	 * ��x:=40, y:=40��x/40=1, y/40=1����Ȼ(1,1)��û��tile�����ǲ�֪��(1,0����(0,1)���Ƿ���tile��
	 * ���Լ��entity��߻��ϱ�tileʱ����֪���������ڣ����������Ҳ������ײ��
	 * ������������entity�������ϻ�������ٶȷ��������ڶ�Ӧ�����ϼ�һ��λ��ƫ�ƣ�ʹ������߻��ϱߵ�tile�غϣ������ܹ�������ײ��� */

	const auto defaultTileInfo = GetDefaultTileInfo();

	auto x = physicalBody.posX;
	auto y = physicalBody.posY;

	auto vx = physicalBody.velocityX;
	auto vy = physicalBody.velocityY;

	if (vx < 0) x -= 0.1;
	if (vy < 0) y -= 0.1;

//	// ��������ͼ��߽�
//	if (x <= 0 && vx < 0) {
//		m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo);
//		entity->SetX(0);
//	}
//
//	// ��������ͼ�ϱ߽�
//	if (y <= 0 && vy < 0) {
//		m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo);
//		entity->SetY(0);
//	}

	return m_tileKeyVector_;
}
