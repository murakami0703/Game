#include "stdafx.h"
#include "PointLight.h"


PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}

void PointLight::InitPointLight()
{
	//�|�C���g���C�g�̏������B
	for (int i = 0; i < NUM_POINT_LIGHT; i++) {
		light.position[i] = CVector3().Zero();
		light.color[i] = { 1.0f, 0.0f, 0.0f, 1.0f };
		light.attn[i] = { 0.0f, 0.0f, 0.0f, 0.0f };
	}

}

void PointLight::Update()
{
	//�X�V�B
}
