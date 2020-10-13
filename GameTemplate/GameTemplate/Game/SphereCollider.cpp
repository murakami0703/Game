#include "stdafx.h"
#include "SphereCollider.h"


SphereCollider::SphereCollider() :
	shape(NULL)
{
}
SphereCollider::~SphereCollider()
{
	delete shape;
}

/// <summary>
/// ���̃R���C�_�[���쐬�B
/// </summary>
/// <param name="radius"></param>
void SphereCollider::Create(const float radius)
{
	shape = new btSphereShape(radius);
}
}