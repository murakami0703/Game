#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	//cmoファイルの読み込み。
	m_mapModel.Init(L"Assets/modelData/test.cmo");
	m_mapModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_phyStaticObject.CreateMeshObject(m_mapModel, m_position, m_rotation);
}


Map::~Map()
{
}

void Map::Update()
{
	m_mapModel.Update();

}
void Map::Draw(int renderMode)
{
	m_mapModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
}