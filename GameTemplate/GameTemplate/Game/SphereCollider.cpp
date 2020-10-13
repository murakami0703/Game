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
/// 球体コライダーを作成。
/// </summary>
/// <param name="radius"></param>
void SphereCollider::Create(const float radius)
{
	shape = new btSphereShape(radius);
}
}