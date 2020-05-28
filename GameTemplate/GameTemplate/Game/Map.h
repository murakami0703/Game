#pragma once

#include "physics/PhysicsStaticObject.h"

class Map : public IGameObject
{
public:
	Map();
	~Map();
	void Update();
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
	/// <summary>
	/// ��]����ݒ�B
	/// </summary>
	void Map::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

private:
	SkinModelRender* m_mapModel;									//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();		//���W
	CQuaternion m_rotation = CQuaternion().Identity();		//��]
	CVector3 m_scale = CVector3().One();		//�g�嗦

	PhysicsStaticObject m_phyStaticObject;					//�ÓI�����I�u�W�F�N�g�B
};

