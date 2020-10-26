#include "stdafx.h"
#include "manager/EffectManager.h"
#include "graphics/effect/EffectPlay.h"

EffectManager* EffectManager::m_instance = nullptr;

EffectManager::EffectManager()
{

	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


EffectManager::~EffectManager()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool EffectManager::Start() { return true; }

//エフェクト再生
void EffectManager::EffectPlayer(EffectName EF, CVector3 position, CVector3 scale,CQuaternion m_rotation) {
	//作成
	EffectPlay* m_player = g_goMgr->NewGameObject<EffectPlay>();
	//名前を引っ張ってくる
	int len = (int)wcslen(DetaBase[EF]);
	for (int x = 0; x < len+1; x++) {
		EF_Name[x] = DetaBase[EF][x];
	}
	//設定
	m_player->SetAnimation(EF_Name);
	m_player->SetPosition(position);
	m_player->SetScale(scale);
	m_player->SetRotation(m_rotation);

}

void EffectManager::EffectPlayer(EffectName EF, CVector3 position, CVector3 scale) {
	//作成
	EffectPlay* m_player = g_goMgr->NewGameObject<EffectPlay>();
	//名前を引っ張ってくる
	int len = (int)wcslen(DetaBase[EF]);
	for (int x = 0; x < len + 1; x++) {
		EF_Name[x] = DetaBase[EF][x];
	}
	//設定
	m_player->SetAnimation(EF_Name);
	m_player->SetPosition(position);
	m_player->SetScale(scale);

}

void EffectManager::Update(){}
