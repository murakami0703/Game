#include "stdafx.h"
#include "stage/LevelSet.h"

#include "stage/Map.h"
//�G�l�~�[
#include "enemy/Ghost.h"
#include "enemy/Bat.h"
#include "enemy/Slaim.h"

//�{�X
#include "boss/Golem.h"
#include "gimick/TreasureBox.h"

#include "data/GameData.h"
#include "level/MapChip.h"

LevelSet* LevelSet::m_instance = nullptr;
LevelSet::LevelSet()
{
	if (m_instance != nullptr) {
		std::abort();//���łɏo�Ă��邽�߃N���b�V��
	}
	m_instance = this;

	//���x���Z�b�g
	LevelSetting();
}


LevelSet::~LevelSet()
{
	m_instance = nullptr;
}

bool LevelSet::OnPreBuildMapchip(LevelObjectData& objData)
{
	static int hoge = 0;
	//�X�e�[�W
	if (objData.EqualObjectName(L"Floor")) {
		Map* m_map = g_goMgr->NewGameObject<Map>();
		m_map->SetPosition(objData.position);
		m_map->SetRotation(objData.rotation);
		m_map->SetScale(objData.scale);
		return true;
	}
	//�S�[�X�g
	if (objData.EqualObjectName(L"ghosts")) {
		
		Ghost* m_ghost = g_goMgr->NewGameObject<Ghost>();
		m_ghost->SetPosition(objData.position);
		m_ghost->SetRotation(objData.rotation);
		m_ghost->SetScale(objData.scale);

		m_enemyCount++;
			
		
		return true;
	}
	//�o�b�g
	if (objData.EqualObjectName(L"bat")) {

		Bat* m_bat = g_goMgr->NewGameObject<Bat>();
		m_bat->SetPosition(objData.position);
		m_bat->SetRotation(objData.rotation);
		m_bat->SetScale(objData.scale);

		m_enemyCount++;
		hoge++;
		return true;
	}
	//�X���C��
	if (objData.EqualObjectName(L"slaim")) {
		Slaim* m_slaim = g_goMgr->NewGameObject<Slaim>();
		m_slaim->SetPosition(objData.position);
		m_slaim->SetRotation(objData.rotation);
		m_slaim->SetScale(objData.scale);

		m_enemyCount++;

		return true;
	}
	//�{�X
	if (objData.EqualObjectName(L"Golem_Boss")) {
		Golem* m_golem = g_goMgr->NewGameObject<Golem>();
		m_golem->SetPosition(objData.position);
		m_golem->SetRotation(objData.rotation);
		m_golem->SetScale(objData.scale);

		m_enemyCount++;

		return true;
	}
	//��
	if (objData.EqualObjectName(L"Treasure_Box")) {
		TreasureBox* m_treasurebox = g_goMgr->NewGameObject<TreasureBox>();
		m_treasurebox->SetPosition(objData.position);
		m_treasurebox->SetRotation(objData.rotation);
		m_treasurebox->SetScale(objData.scale);
		return true;
	}

	return false;
}
void LevelSet::OnPostBuildMapChip(LevelObjectData& objData, MapChip& mapchip)
{
	if (objData.EqualObjectName(L"stage1_start")
		|| objData.EqualObjectName(L"stage1_1")
		|| objData.EqualObjectName(L"stage1_1_2")
		|| objData.EqualObjectName(L"stage1_1_3")
		|| objData.EqualObjectName(L"stage1_boss")) {
		//�@���}�b�v���܂�
		ID3D11ShaderResourceView* normal;

		DirectX::CreateDDSTextureFromFileEx(
			g_graphicsEngine->GetD3DDevice(), L"Assets/modelData/stage1_texture/Gravel_normal.dds", 0,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			false, nullptr, &normal
		);
		mapchip.SetNormalMap(normal);

	}
	if (objData.EqualObjectName(L"stage1_start")
		|| objData.EqualObjectName(L"stage1_1")
		|| objData.EqualObjectName(L"stage1_1_2")
		|| objData.EqualObjectName(L"stage1_1_3")
		|| objData.EqualObjectName(L"stage1_boss")) {
		//�X�؃L�����}�b�v���܂�
		ID3D11ShaderResourceView* specular;

		DirectX::CreateDDSTextureFromFileEx(
			g_graphicsEngine->GetD3DDevice(), L"Assets/modelData/stage1_texture/Gravel_SPE.dds", 0,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			false, nullptr, &specular
		);
		mapchip.SetSpecularMap(specular);
	}
	if (objData.EqualObjectName(L"stage1_start")
		|| objData.EqualObjectName(L"stage1_1")
		|| objData.EqualObjectName(L"stage1_1_2")
		|| objData.EqualObjectName(L"stage1_1_3")
		|| objData.EqualObjectName(L"stage1_boss")) {
		//�`�n�}�b�v���܂�
		ID3D11ShaderResourceView* AO;

		DirectX::CreateDDSTextureFromFileEx(
			g_graphicsEngine->GetD3DDevice(), L"Assets/modelData/stage1_texture/Gravel_AO.dds", 0,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			false, nullptr, &AO
		);
		mapchip.SetAoMap(AO);
	}


}
void LevelSet::LevelSetting()
{
	//level�Œu���܂����B
	m_level.Init(L"Assets/level/stage_02.tkl", 
		[&](LevelObjectData& objData) {
			return OnPreBuildMapchip(objData);
		}, 
		[&](LevelObjectData& objData, MapChip& mapchip) {
			OnPostBuildMapChip(objData, mapchip);
		}
	);
	//�G�̐���GameData�ɋ�����
	GameData* m_gamedate = GameData::GetInstance();
	m_gamedate->SetEnemyCount(m_enemyCount);
}
void LevelSet::Update()
{
	m_level.Update();
}
void LevelSet::Render()
{
	m_level.Draw();
}
