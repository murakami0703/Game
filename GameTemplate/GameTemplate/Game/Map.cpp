#include "stdafx.h"
#include "Map.h"

Map::Map()
{
	//levelで置きますわよ。
	/*m_level.Init(L"level/level_01.tkl", [&](LevelObjectData& objData) {
		//ステージ

		//エネミー

		return false;
	});*/
	//cmoファイルの読み込み。
	m_mapModel.Init(L"Assets/modelData/test.cmo");
	m_mapModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_phyStaticObject.CreateMeshObject(m_mapModel, m_position, m_rotation);
	m_mapModel.SetShadowReciever(true);
}


Map::~Map()
{
}

void Map::Update()
{
	m_mapModel.Update();

}
void Map::Draw(EnRenderMode renderMode)
{
	m_mapModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
}