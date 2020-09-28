#include "stdafx.h"
#include "PhysicsGhostObject.h"
#include "BoxCollider.h"


PhysicsGhostObject::PhysicsGhostObject()
{
}


PhysicsGhostObject::~PhysicsGhostObject()
{
	if (m_isRegistPhysicsWorld == true) {
		g_physics.RemoveCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = false;
	}
}

void PhysicsGhostObject::GhostObject(CVector3 pos, CQuaternion rot)
{
	//m_ghostObject.setCollisionShape(m_collider->GetBody());
	btTransform btTrans;
	btTrans.setOrigin({ pos.x, pos.y, pos.z });
	btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
	m_ghostObject.setWorldTransform(btTrans);

	//�����G���W���ɓo�^�B
	g_physics.AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;
}
