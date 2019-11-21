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

	SkinModel* GetMapSkinModel() {
		return &m_mapModel;
	}
private:
	SkinModel m_mapModel;									//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();		//���W
	CQuaternion m_rotation = CQuaternion().Identity();		//��]
	CVector3 m_scale = CVector3().One();		//�g�嗦

	PhysicsStaticObject m_phyStaticObject;					//�ÓI�����I�u�W�F�N�g�B
};

