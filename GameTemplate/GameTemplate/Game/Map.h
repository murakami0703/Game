#pragma once

#include "physics/PhysicsStaticObject.h"
#include "ShadowMap.h"
#include "level/Level.h"

class Map
{
public:
	Map();
	~Map();
	void Update();
	void Draw(EnRenderMode renderMode);

	/// <summary>
	/// Mapのモデルを取得。
	/// </summary>
	/// <returns>Mapのスキンモデル</returns>
	SkinModel* GetMapSkinModel() {
		return &m_mapModel;
	}
private:
	Level m_level;	//レベルデータ。

	SkinModel m_mapModel;									//スキンモデル。
	CVector3 m_position = CVector3().Zero();		//座標
	CQuaternion m_rotation = CQuaternion().Identity();		//回転
	CVector3 m_scale = CVector3().One();		//拡大率

	PhysicsStaticObject m_phyStaticObject;					//静的物理オブジェクト。
};

