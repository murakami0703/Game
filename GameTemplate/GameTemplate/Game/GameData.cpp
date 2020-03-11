#include "stdafx.h"
#include "GameData.h"

GameData* GameData::m_instance = nullptr;

GameData::GameData()
{
	m_instance = this;

}


GameData::~GameData()
{
}
void GameData::Update(){}
void GameData::Render(){}
