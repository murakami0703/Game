#include "stdafx.h"
#include "Map.h"

Map::Map()
{
	//cmoファイルの読み込み。
	m_mapModel = g_goMgr.NewGameObject<SkinModelRender>();
	m_mapModel->Init(L"Assets/modelData/Floor.cmo");
	m_mapModel->SetPosition(m_position);
	m_mapModel->SetRotation(m_rotation);
	m_mapModel->SetScale(m_scale);
	m_phyStaticObject.CreateMeshObject(m_mapModel->GetSkinModel(), m_position, m_rotation);
	//m_mapModel.SetShadowReciever(true);
}


Map::~Map()
{
}

void Map::Update()
{
	m_mapModel->Update();
}
void Map::Render()
{
}