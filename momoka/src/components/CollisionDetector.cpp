#include "stdafx.h"
#include "components/CollisionDetector.h"
#include "components/PhysicalBody.h"


CollisionDetector::CollisionDetector(TileMap& tileMap, TileTpyeMap& tileTpyeMap) : m_tileMap_(tileMap),
                                                                                   m_tileTypeMap_(tileTpyeMap) {
}

CollisionDetector::~CollisionDetector() {
}

TileCollisionInfoVector CollisionDetector::TileCollisionChecker(const PhysicalBody& physicalBody) const {
	TileCollisionInfoVector tileKeyVector;
	tileKeyVector.clear();

	/* ��һ��entity����߻��ϱ���tile���ڵ�δ�غ�ʱ�����ڲ�����������λ�ö�Ӧtileʱ���õ�������
	 * ��x:=40, y:=40��x/40=1, y/40=1����Ȼ(1,1)��û��tile�����ǲ�֪��(1,0����(0,1)���Ƿ���tile��
	 * ���Լ��entity��߻��ϱ�tileʱ����֪���������ڣ����������Ҳ������ײ��
	 * ������������entity�������ϻ�������ٶȷ��������ڶ�Ӧ�����ϼ�һ��λ��ƫ�ƣ�ʹ������߻��ϱߵ�tile�غϣ������ܹ�������ײ��� */

	auto x = physicalBody.posX;
	auto y = physicalBody.posY;

	auto vx = physicalBody.velocityX;
	auto vy = physicalBody.velocityY;

	if (vx < 0) x -= 0.1f;
	if (vy < 0) y -= 0.1f;

	// ��������ͼ��߽�
	if (x <= 0 && vx < 0) {
		tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_left, -1));
	}

	// ��������ͼ�ϱ߽�
	if (y <= 0 && vy < 0) {
		tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_up, -1));
	}

	float bodyWidth = physicalBody.collisionWidth;
	float bodHeight = physicalBody.collisionHeight;
	// �涨�������Ͻ�Ϊ��ʼ�㣨start�������½�Ϊ��ֹ�㣨end��
	__int64 xStartTile = int(x / momoka_global::TILE_SIZE);
	__int64 yStartTile = int(y / momoka_global::TILE_SIZE);
	__int64 xEndTile = int((x + bodyWidth) / momoka_global::TILE_SIZE);
	__int64 yEndTile = int((y + bodHeight) / momoka_global::TILE_SIZE);

	__int64 leftUpTileKey = TileMapKeyConvert(xStartTile, yStartTile);
	__int64 leftDownTileKey = TileMapKeyConvert(xStartTile, yEndTile);
	__int64 rightUpTileKey = TileMapKeyConvert(xEndTile, yStartTile);
	__int64 rightDownTileKey = TileMapKeyConvert(xEndTile, yEndTile);

	auto leftUpItem = m_tileMap_.find(leftUpTileKey);
	auto leftDownItem = m_tileMap_.find(leftDownTileKey);
	auto rightUpItem = m_tileMap_.find(rightUpTileKey);
	auto rightDownItem = m_tileMap_.find(rightDownTileKey);

	auto nullItem = m_tileMap_.end();

	float maxCollidedTime = 0.f;

	if (leftUpItem != nullItem) {
		float dx = x - (xStartTile + 1) * momoka_global::TILE_SIZE;
		float dy = y - (yStartTile + 1) * momoka_global::TILE_SIZE;

		if (vx < 0 && vy < 0) {
			float dx = x - (xStartTile + 1) * momoka_global::TILE_SIZE;
			float dy = y - (yStartTile + 1) * momoka_global::TILE_SIZE;
			if (abs(vy / vx) <= abs(dy / dx)) {
				tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_left, leftUpTileKey));
			}
			else {
				tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_up, leftUpTileKey));
			}
		}
		else if (vx < 0) { tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_left, leftUpTileKey)); }
		else if (vy < 0) { tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_up, leftUpTileKey)); }
	}

	if (leftDownItem != nullItem) {

		if (vx < 0 && vy > 0) {
			float dx = x - (xStartTile + 1) * momoka_global::TILE_SIZE;
			float dy = (y + bodHeight) - yEndTile * momoka_global::TILE_SIZE;
			if (abs(vy / vx) <= abs(dy / dx)) {
				tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_left, leftDownTileKey));
			}
			else {
				tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_down, leftDownTileKey));
			}
		}
		else if (vy >= 0) { tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_down, leftDownTileKey)); }
		else if (vx < 0) { tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_left, leftDownTileKey)); }
	}

	if (rightUpItem != nullItem) {

		if (vx > 0 && vy < 0) {
			float dx = x + bodyWidth - xEndTile * momoka_global::TILE_SIZE;
			float dy = y - (yStartTile + 1) * momoka_global::TILE_SIZE;
			if (abs(vy / vx) <= abs(dy / dx)) {
				tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_right, rightUpTileKey));
			}
			else {
				tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_up, rightUpTileKey));
			}
		}
		else if (vx > 0) {
			tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_right, rightUpTileKey));
		}
		else if (vy < 0) {
			if ((x + bodyWidth) - int(x + bodyWidth) != 0) {
				tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_up, rightUpTileKey));
			}
		}
	}

	if (rightDownItem != nullItem) {

		if (vx > 0 && vy > 0) {
			float dx = x + bodyWidth - xEndTile * momoka_global::TILE_SIZE;
			float dy = y + bodHeight - yEndTile * momoka_global::TILE_SIZE;
			if (abs(vy / vx) <= abs(dy / dx)) {
				tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_right, rightDownTileKey));
			}
			else {
				tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_down, rightDownTileKey));
			}
		}
		else {
			if (vy == 0) {
				if ((x + bodyWidth) - int(x + bodyWidth) != 0) {
					tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_down, rightDownTileKey));
				}
			}
			else if (vx > 0) {
				if ((y + bodHeight) - int(y + bodHeight) != 0) {
					tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_right, rightDownTileKey));
				}
			}
			else if (vy > 0) {
				if ((x + bodyWidth) - int(x + bodyWidth) != 0) {
					tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_down, rightDownTileKey));
				}
			}
		}
	}

	// �����ߵ���ײ���
	for (__int64 i = xStartTile + 1; i < xEndTile; i++) {
		auto key = TileMapKeyConvert(i, yStartTile);
		auto item = m_tileMap_.find(key);
		if (item != nullItem) {

			tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_up, key));
			break;
		}

		key = TileMapKeyConvert(i, yEndTile);
		item = m_tileMap_.find(key);
		if (item != nullItem) {
			tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_down, key));
			break;
		}
	}

	for (__int64 i = yStartTile + 1; i < yEndTile; i++) {
		auto key = TileMapKeyConvert(xStartTile, i);
		auto item = m_tileMap_.find(key);
		if (item != nullItem) {
			tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_left, key));
			break;
		}

		key = TileMapKeyConvert(xEndTile, i);
		item = m_tileMap_.find(key);
		if (item != nullItem) {
			tileKeyVector.push_back(GenerateTileCollisionInfo(Collision_right, key));
			break;
		}
	}

	return tileKeyVector;
}

PhysicalBody CollisionDetector::TileCollisionDefaultSolver(const TileCollisionInfo& tileCollisionInfo, PhysicalBody physicalBody) {

	auto x = physicalBody.posX;
	auto y = physicalBody.posY;
	auto vx = physicalBody.velocityX;
	auto vy = physicalBody.velocityY;
	if (vx < 0) x -= 0.1f;
	if (vy < 0) y -= 0.1f;

	if(tileCollisionInfo.tileMapKey==-1 && tileCollisionInfo.flag == Collision_up) {
		physicalBody.posY = 0;
		physicalBody.velocityY = 0;
		return physicalBody;
	}

	if (tileCollisionInfo.tileMapKey == -1 && tileCollisionInfo.flag == Collision_left) {
		physicalBody.posX = 0;
		physicalBody.velocityX = 0;
		return physicalBody;
	}

	float bodyWidth = physicalBody.collisionWidth;
	float bodyHeight = physicalBody.collisionHeight;

	__int64 xStartTile = int(x / momoka_global::TILE_SIZE);
	__int64 yStartTile = int(y / momoka_global::TILE_SIZE);
	__int64 xEndTile = int((x + bodyWidth) / momoka_global::TILE_SIZE);
	__int64 yEndTile = int((y + bodyHeight) / momoka_global::TILE_SIZE);

	switch (tileCollisionInfo.flag) {
	case Collision_up:
		physicalBody.posY = (yStartTile + 1) * momoka_global::TILE_SIZE;
		physicalBody.velocityY = 0;
		break;
	case Collision_down:
		physicalBody.posY = yEndTile * momoka_global::TILE_SIZE - bodyHeight;
		physicalBody.velocityY = 0;
		break;
	case Collision_left:
		physicalBody.posX = (xStartTile + 1) * momoka_global::TILE_SIZE;
		physicalBody.velocityX = 0;
		break;
	case Collision_right:
		physicalBody.posX = xEndTile * momoka_global::TILE_SIZE - bodyWidth;
		physicalBody.velocityX = 0;
		break;
	default:
		break;
	}
	return physicalBody;
}

TileCollisionInfo CollisionDetector::GenerateTileCollisionInfo(COLLISION_FLAG flag, TileMapKey key) const {
	TileCollisionInfo info;
	auto tileType = GetDefaultTileInfo();
	auto item = m_tileTypeMap_.find(key);
	if (item != m_tileTypeMap_.end()) {
		tileType = item->second;
	}
	info.flag = flag;
	info.tileMapKey = key;
	info.tileType = tileType;
	return info;
}
