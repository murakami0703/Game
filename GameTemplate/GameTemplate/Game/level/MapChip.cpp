#include "stdafx.h"
#include "MapChip.h"
#include "Level.h"

MapChip::MapChip(LevelObjectData& objData,
	std::function<void(LevelObjectData& objData, MapChip& mapchip)> onBuildMapchip)
{
	wchar_t filePath[256];
	swprintf_s(filePath, L"Assets/modelData/%s.cmo", objData.name);
	m_model.Init(filePath);
	m_model.UpdateWorldMatrix(objData.position, objData.rotation, objData.scale);

	if (onBuildMapchip) {
		onBuildMapchip(objData, *this);
	}
	//静的物理オブジェクトをメッシュコライダーから作成する。
	m_physicsStaticObject.CreateMeshObject(m_model, objData.position, objData.rotation, objData.scale);

	m_model.SetShadowReciever(true);

}
MapChip::~MapChip()
{
	if (g_normalMapSRV) {
		g_normalMapSRV->Release();
	}
}
void MapChip::Update()
{
	g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);

}
void MapChip::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		EnRenderMode::enRenderMode_Normal
	);
}