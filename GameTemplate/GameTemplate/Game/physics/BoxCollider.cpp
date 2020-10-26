#include "stdafx.h"
#include "physics/BoxCollider.h"


BoxCollider::BoxCollider():
	shape(NULL)
{
}
BoxCollider::~BoxCollider()
{
	delete shape;
}
/*!
 * @brief	ボックスコライダーを作成。
 */
void BoxCollider::Create(const CVector3& size)
{
	shape = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
}
