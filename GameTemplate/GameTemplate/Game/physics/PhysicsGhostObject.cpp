#include "stdafx.h"
#include "physics/PhysicsGhostObject.h"
#include "physics/BoxCollider.h"


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

void PhysicsGhostObject::GhostBoxObject(CVector3 pos, CQuaternion rot, CVector3 size)
{
	//�{�b�N�X�R���C�_�[
	m_boxCollider.Create(size);

	m_ghostObject.setCollisionShape(m_boxCollider.GetBody());
	btTransform btTrans;
	btTrans.setOrigin({ pos.x, pos.y, pos.z });
	btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
	m_ghostObject.setWorldTransform(btTrans);

	//�����G���W���ɓo�^�B
	g_physics.AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;
}
