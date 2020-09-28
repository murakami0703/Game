#include "stdafx.h"
#include "StageGate.h"
#include "Player.h"

StageGate::StageGate()
{
}


StageGate::~StageGate()
{
}

bool StageGate::Start()
{
	//ゴーストの初期化。
	//ゴーストのワイヤーフレーム表示を有効にする。
	//g_physics.SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//ボックス形状のゴーストを作成する。
	m_ghostObject1.GhostBoxObject(
		{ -500.0f, 100.0f, 0.0f },	//第一引数は座標。
		CQuaternion().Identity(),		//第二引数は回転クォータニオン。
		{ 200.0f, 200.0f, 200.0f }	//第三引数はボックスのサイズ。
	);
	return true;
}

void StageGate::Update()
{
	Player* player = Player::GetInstance();
	g_physics.ContactTest(player->GetCharacon(), [&](const btCollisionObject& contactObject) {
		if (m_ghostObject1.IsSelf(contactObject) == true) {
			//m_ghostObjectとぶつかった
		}
	});
}