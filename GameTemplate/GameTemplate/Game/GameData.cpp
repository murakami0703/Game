#include "stdafx.h"
#include "GameData.h"

GameData* GameData::m_instance = nullptr;

GameData::GameData()
{
	m_instance = this;
}
GameData::~GameData(){}

bool GameData::Start() {
	return true;
}
void GameData::Update(){
	//�G���S���|���ꂽ�̂Ń{�X�𓮂����܂��B
	if (EnemyCount <= 0)
	{
		m_bossMoveFlag = true;
	}
}
