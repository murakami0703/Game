#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	//cmoファイルの読み込み。
	m_mapModel.Init(L"Assets/modelData/test.cmo");
	m_mapModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}


Map::~Map()
{
}

void Map::Update()
{
}
void Map::Draw()
{
	m_mapModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}