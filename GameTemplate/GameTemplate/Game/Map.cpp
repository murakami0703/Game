#include "stdafx.h"
#include "Map.h"


Map::Map()
{
}


Map::~Map()
{
}
bool Map::Start()
{
	//cmoファイルの読み込み。
	m_mapModel = g_goMgr->NewGameObject<SkinModelRender>();
	m_mapModel->Init(L"Assets/modelData/Floor.cmo");
	m_mapModel->SetPosition(m_position);
	m_mapModel->SetRotation(m_rotation);
	m_mapModel->SetScale(m_scale);

	//各マップの設定。
	m_mapModel->SetNormalMap(L"Assets/modelData/stage1_texture/ClumpMud_Normal.dds");
	m_mapModel->SetSpecularMap(L"Assets/modelData/stage1_texture/ClumpMud_smoothness.dds");
	m_mapModel->SetSpecularMap(L"Assets/modelData/stage1_texture/ClumpMud_Grass_Ao.dds");

	m_phyStaticObject.CreateMeshObject(m_mapModel->GetSkinModel(), m_position, m_rotation, m_scale);
	m_mapModel->SetShadowReciever(true);
	m_mapModel->SetShadowCaster(true);

	return true;
}

void Map::Update()
{
}
