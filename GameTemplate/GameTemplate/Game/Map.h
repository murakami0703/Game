#pragma once

#include "physics/PhysicsStaticObject.h"
#include "ShadowMap.h"

class Map
{
public:
	Map();
	~Map();
	void Update();
	void Draw(EnRenderMode renderMode);

	/// <summary>
	/// Map�̃��f�����擾�B
	/// </summary>
	/// <returns>Map�̃X�L�����f��</returns>
	SkinModel* GetMapSkinModel() {
		return &m_mapModel;
	}
	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void Map::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	void Map::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}

private:
	SkinModel m_mapModel;									//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();		//���W
	CQuaternion m_rotation = CQuaternion().Identity();		//��]
	CVector3 m_scale = CVector3().One();		//�g�嗦

	PhysicsStaticObject m_phyStaticObject;					//�ÓI�����I�u�W�F�N�g�B
};

