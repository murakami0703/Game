#include "stdafx.h"
#include "Map.h"

Map::Map()
{
	//cmoファイルの読み込み。
	m_mapModel = g_goMgr->NewGameObject<SkinModelRender>();
	m_mapModel->Init(L"Assets/modelData/Floor.cmo");
	m_mapModel->SetPosition(m_position);
	m_mapModel->SetRotation(m_rotation);
	m_mapModel->SetScale(m_scale);
	m_phyStaticObject.CreateMeshObject(m_mapModel->GetSkinModel(), m_position, m_rotation, m_scale);
	//m_mapModel->SetShadowReciever(true);
	//m_mapModel->SetShadowMap(true);
}


Map::~Map()
{
}

void Map::Update()
{
}
void Map::Render(){}
void Map::PostRender(){}