#include "stdafx.h"
#include "services/GraphicService.h"
#include "game/GameTestState.h"
#include "Engine.h"
#include "objects/Entity.h"
#include "objects/Hero.h"
#include "commands/Command.h"
#include "commands/actor/MoveDownCommand.h"
#include "commands/actor/MoveLeftCommand.h"
#include "commands/actor/MoveRightCommand.h"
#include "commands/actor/MoveUpCommand.h"
#include "services/InputService.h"
#include "util/Log.h"


GameTestState::GameTestState(): m_pPlayerCharacter_(nullptr), m_commandW_(nullptr), m_commandA_(nullptr),
                                m_commandS_(nullptr), m_commandD_(nullptr),
                                m_collisionDetector_(m_tilesMap_, m_tileTypeMap_) {
	MOMOKA_LOG(momoka::info) << "GameTestState Initialized";
}

GameTestState::~GameTestState() {
}

void GameTestState::OnEnter() {
	m_pPlayerCharacter_ = new Hero();
	m_commandW_ = new MoveUpCommand(m_pPlayerCharacter_);
	m_commandA_ = new MoveLeftCommand(m_pPlayerCharacter_);
	m_commandS_ = new MoveDownCommand(m_pPlayerCharacter_);
	m_commandD_ = new MoveRightCommand(m_pPlayerCharacter_);
	WorldLoader();
}

void GameTestState::OnExit() {
	SafeDelete(&m_pPlayerCharacter_);
}

void GameTestState::Render(float dt) {
	auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(
		momoka_global::SERVICE_TYPE::Service_graphic).lock();
	pGraphicService->DrawTestWhiteBackGround();
	for (auto tile : m_tilesMap_) {
		int y = tile.first % 1000000;
		int x = (tile.first - y) / 1000000;
		auto type = tile.second;
		auto tileInfo = m_tileTypeMap_[type];
		pGraphicService->DrawRect(x * momoka_global::TILE_SIZE, y * momoka_global::TILE_SIZE, tileInfo.width,
		                          tileInfo.height);
	}
	m_pPlayerCharacter_->Render(dt);
}

void GameTestState::Update() {

	// �������ҳ�����һ������ģʽ
	auto pInputService = Engine::m_serviceLoader.LocateService<InputService>(momoka_global::SERVICE_TYPE::Service_input).
	                                             lock();


	if (pInputService->IsKeyPressed(DIK_W)) {
		m_commandW_->Execute();
	}

	if (pInputService->IsKeyPressed(DIK_S)) {
		m_commandS_->Execute();
	}

	if (pInputService->IsKeyPressed(DIK_A)) {
		m_commandA_->Execute();
	}

	if (pInputService->IsKeyPressed(DIK_D)) {
		m_commandD_->Execute();
	}

	if (pInputService->IsKeyPressed(DIK_K)) {
		m_pPlayerCharacter_->Jump();
	}

	//GlobalPhysicsSimulation(m_pPlayerCharacter_);
	m_pPlayerCharacter_->Update();
}

void GameTestState::WorldLoader() {
	TileType normalTile;
	normalTile.width = momoka_global::TILE_SIZE;
	normalTile.height = momoka_global::TILE_SIZE;
	normalTile.friction = 1;

	m_tileTypeMap_.insert(std::make_pair(0, normalTile));

	m_pPlayerCharacter_->SetX(momoka_global::TILE_SIZE);
	m_pPlayerCharacter_->SetY(momoka_global::TILE_SIZE);
	m_pPlayerCharacter_->SetCollisionDetector(&m_collisionDetector_);

	// Tile�������һ��__int64�����棬��Ϊmap��key��֧�ֽṹ��

	int y = 10;
	for (int x = 0; x < 21; x++) {
		m_tilesMap_[TileMapKeyConvert(x, y)] = 0;
	}

	m_tilesMap_[TileMapKeyConvert(6, 8)] = 0;
	m_tilesMap_[TileMapKeyConvert(8, 7)] = 0;

}

//void GameTestState::GlobalPhysicsSimulation(Entity* entity) {
//	// ����������ȫ������ģ�⣬��Ҫ����Entity��Tile����ײ���
//	// TODO: ׼���Ƴ����������ת��ʹ��CollisionDetector��
//
//	/* ����˵һ����ײ�������̣��������entity��ײ�����ĸ��������꣬�������ĸ��������ڵ�λ���Ƿ���tile
//	 * ����У�˵����������ײ����ô�͸����˶������������x��y�����Ϸ�����ײ���Ӷ����÷����ٶȷ�����Ϊ0
//	 * ���û�У���ȥ�������������λ���Ƿ���tile��Ȼ���ظ���������̣������ײ */
//
//	const auto defaultTileInfo = GetDefaultTileInfo();
//	entity->ClearObstructFlags();
//
//	auto x = entity->GetX();
//	auto y = entity->GetY();
//
//	auto vx = entity->GetVelocityX();
//	auto vy = entity->GetVelocityY();
//
//	/* ��һ��entity����߻��ϱ���tile���ڵ�δ�غ�ʱ�����ڲ�����������λ�ö�Ӧtileʱ���õ�������
//	 * ��x:=40, y:=40��x/40=1, y/40=1����Ȼ(1,1)��û��tile�����ǲ�֪��(1,0����(0,1)���Ƿ���tile��
//	 * ���Լ��entity��߻��ϱ�tileʱ����֪���������ڣ����������Ҳ������ײ��
//	 * ������������entity�������ϻ�������ٶȷ��������ڶ�Ӧ�����ϼ�һ��λ��ƫ�ƣ�ʹ������߻��ϱߵ�tile�غϣ������ܹ�������ײ��� */
//	if (vx < 0) x -= 0.1;
//	if (vy < 0) y -= 0.1;
//
//	// ��������ͼ��߽�
//	if (x <= 0 && entity->GetVelocityX() < 0) {
//		m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo);
//		entity->SetX(0);
//	}
//
//	// ��������ͼ�ϱ߽�
//	if (y <= 0 && entity->GetVelocityY() < 0) {
//		m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo);
//		entity->SetY(0);
//	}
//
//	float entityWidth = entity->GetCollisionWidth();
//	float entityHeight = entity->GetCollisionHeight();
//	// �涨�������Ͻ�Ϊ��ʼ�㣨start�������½�Ϊ��ֹ�㣨end��
//	__int64 xStartTile = int(x / momoka_global::TILE_SIZE);
//	__int64 yStartTile = int(y / momoka_global::TILE_SIZE);
//	__int64 xEndTile = int((x + entityWidth) / momoka_global::TILE_SIZE);
//	__int64 yEndTile = int((y + entityHeight) / momoka_global::TILE_SIZE);
//
//	__int64 leftUpTileKey = TileMapKeyConvert(xStartTile, yStartTile);
//	__int64 leftDownTileKey = TileMapKeyConvert(xStartTile, yEndTile);
//	__int64 rightUpTileKey = TileMapKeyConvert(xEndTile, yStartTile);
//	__int64 rightDownTileKey = TileMapKeyConvert(xEndTile, yEndTile);
//
//	auto leftUpItem = m_tilesMap_.find(leftUpTileKey);
//	auto leftDownItem = m_tilesMap_.find(leftDownTileKey);
//	auto rightUpItem = m_tilesMap_.find(rightUpTileKey);
//	auto rightDownItem = m_tilesMap_.find(rightDownTileKey);
//
//	auto nullItem = m_tilesMap_.end();
//
//	/* �����ĸ�if������������ײ�����ӵ�һ���ִ��룬��δ�������ĸ��ǵ���ײ��⡣
//	 * ������ͨ�����ϳ��ٶ�б����������ײ�ķ��򣬴Ӷ�������x��y�����ٶȷ�����Ϊ0
//	 * ע��Ҫ���� vx == 0 �� vy == 0 ����������±߷����Ӵ�����Ҫ���ǵ������������Ҫ��������ű��˶������ */
//
//	if (leftUpItem != nullItem) {
//		if (vx < 0 && vy < 0) {
//			float dx = x - (xStartTile + 1) * momoka_global::TILE_SIZE;
//			float dy = y - (yStartTile + 1) * momoka_global::TILE_SIZE;
//			if (abs(vy / vx) <= abs(dy / dx)) {
//				if (m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo)) {
//					m_pPlayerCharacter_->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
//				}
//			}
//			else {
//				if (m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo)) {
//					m_pPlayerCharacter_->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
//				}
//			}
//		}
//		else if (vx < 0) {
//			if (m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo)) {
//				m_pPlayerCharacter_->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
//			}
//		}
//		else if (vy < 0) {
//			if (m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo)) {
//				m_pPlayerCharacter_->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
//			}
//		}
//	}
//
//	if (leftDownItem != nullItem) {
//		if (vx < 0 && vy > 0) {
//			float dx = x - (xStartTile + 1) * momoka_global::TILE_SIZE;
//			float dy = (y + entityHeight) - yEndTile * momoka_global::TILE_SIZE;
//			if (abs(vy / vx) <= abs(dy / dx)) {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo)) {
//					entity->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
//				}
//			}
//			else {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_down, defaultTileInfo)) {
//					entity->SetY((yEndTile) * momoka_global::TILE_SIZE - entityHeight);
//				}
//			}
//		}
//		else if (vy >= 0) {
//			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_down, defaultTileInfo)) {
//				entity->SetY((yEndTile) * momoka_global::TILE_SIZE - entityHeight);
//			}
//		}
//		else if (vx < 0) {
//			if ((y + entityHeight) - int(y + entityHeight) != 0) {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo)) {
//					entity->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
//				}
//			}
//		}
//	}
//
//	if (rightUpItem != nullItem) {
//		if (vx > 0 && vy < 0) {
//			float dx = x + entityWidth - xEndTile * momoka_global::TILE_SIZE;
//			float dy = y - (yStartTile + 1) * momoka_global::TILE_SIZE;
//			if (abs(vy / vx) <= abs(dy / dx)) {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_right, defaultTileInfo)) {
//					entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
//				}
//			}
//			else {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo)) {
//					entity->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
//				}
//			}
//		}
//		else if (vx > 0) {
//			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_right, defaultTileInfo)) {
//				entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
//			}
//		}
//		else if (vy < 0) {
//			if ((x + entityWidth) - int(x + entityWidth) != 0) {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo)) {
//					entity->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
//				}
//			}
//		}
//	}
//
//	if (rightDownItem != nullItem) {
//		if (vx > 0 && vy > 0) {
//			float dx = x + entityWidth - xEndTile * momoka_global::TILE_SIZE;
//			float dy = y + entityHeight - yEndTile * momoka_global::TILE_SIZE;
//			if (abs(vy / vx) <= abs(dy / dx)) {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_right, defaultTileInfo)) {
//					entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
//				}
//			}
//			else {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_down, defaultTileInfo)) {
//					entity->SetY(yEndTile * momoka_global::TILE_SIZE - entityHeight);
//				}
//			}
//		}
//		else {
//			if (vy == 0) {
//				if ((x + entityWidth) - int(x + entityWidth) != 0) {
//					if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_down, defaultTileInfo)) {
//						entity->SetY(yEndTile * momoka_global::TILE_SIZE - entityHeight);
//					}
//				}
//			}
//			else if (vx > 0) {
//				if ((y + entityHeight) - int(y + entityHeight) != 0) {
//					if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_right, defaultTileInfo)) {
//						entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
//					}
//				}
//			}
//			else if (vy > 0) {
//				if ((x + entityWidth) - int(x + entityWidth) != 0) {
//					if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_down, defaultTileInfo)) {
//						entity->SetY(yEndTile * momoka_global::TILE_SIZE - entityHeight);
//					}
//				}
//			}
//		}
//	}
//
//	// �����ߵ���ײ���
//	for (int i = xStartTile + 1; i < xEndTile; i++) {
//		auto key = TileMapKeyConvert(i, yStartTile);
//		auto item = m_tilesMap_.find(key);
//		if (item != nullItem) {
//			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo)) {
//				entity->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
//			}
//			break;
//		}
//
//		key = TileMapKeyConvert(i, yEndTile);
//		item = m_tilesMap_.find(key);
//		if (item != nullItem) {
//			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_down, defaultTileInfo)) {
//				entity->SetY(yEndTile * momoka_global::TILE_SIZE - entityHeight);
//
//			}
//			break;
//		}
//	}
//
//	for (int i = yStartTile + 1; i < yEndTile; i++) {
//		auto key = TileMapKeyConvert(xStartTile, i);
//		auto item = m_tilesMap_.find(key);
//		if (item != nullItem) {
//			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo)) {
//				entity->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
//			}
//			break;
//		}
//
//		key = TileMapKeyConvert(xEndTile, i);
//		item = m_tilesMap_.find(key);
//		if (item != nullItem) {
//			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_right, defaultTileInfo)) {
//				entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
//			}
//			break;
//		}
//	}
//
//}
