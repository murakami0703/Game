/// <summary>
/// �S�[�X�g�I�u�W�F�N�g
/// </summary>
#pragma once
#include "physics/RigidBody.h"
#include "PhysicsObjectBase.h"

/// <summary>
/// �S�[�X�g�I�u�W�F�N�g
/// </summary>

class PhysicsGhostObject : public PhysicsObjectBase
{
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	PhysicsGhostObject();
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~PhysicsGhostObject();

	/*!
	* @brief	�����œn���ꂽ�S�[�X�g�I�u�W�F�N�g���������g���ǂ�������B
	*/
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}

	/// <summary>
	/// �S�[�X�g�I�u�W�F�N�g�B
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	void GhostObject(CVector3 pos, CQuaternion rot);

private:
	bool						m_isRegistPhysicsWorld = false;	//!<�������[���h�ɓo�^���Ă��邩�ǂ����̃t���O�B
	btGhostObject				m_ghostObject;	//!<�S�[�X�g

};

