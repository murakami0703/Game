/*!
 * @brief	静的オブジェクト。
 */


#include "stdafx.h"
#include "physics/PhysicsStaticObject.h"

using namespace std;

PhysicsStaticObject::PhysicsStaticObject()
{
}
PhysicsStaticObject::~PhysicsStaticObject()
{
	g_physics.RemoveRigidBody(m_rigidBody);
}
void PhysicsStaticObject::CreateCommon(CVector3 pos, CQuaternion rot)
{
	RigidBodyInfo rbInfo;
	rbInfo.collider = m_collider.get();
	rbInfo.mass = 0.0f;
	rbInfo.pos = pos;
	rbInfo.rot = rot;
	m_rigidBody.Create(rbInfo);
	PhysicsWorld().AddRigidBody(m_rigidBody);
}
