#pragma once

#include "physics/PhysicsStaticObject.h"

class Map : public IGameObject
{
public:
	Map();
	~Map();
	void Update();
	/// <summary>
	/// 座標を設定。
	/// </summary>
	void Map::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	void Map::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転率を設定。
	/// </summary>
	void Map::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

private:
	SkinModelRender* m_mapModel;									//スキンモデル。
	CVector3 m_position = CVector3().Zero();		//座標
	CQuaternion m_rotation = CQuaternion().Identity();		//回転
	CVector3 m_scale = CVector3().One();		//拡大率

	PhysicsStaticObject m_phyStaticObject;					//静的物理オブジェクト。
};

