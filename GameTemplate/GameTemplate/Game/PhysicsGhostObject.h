/// <summary>
/// �S�[�X�g�I�u�W�F�N�g
/// </summary>
#pragma once
#include "BoxCollider.h"

/// <summary>
/// �S�[�X�g�I�u�W�F�N�g
/// </summary>

class PhysicsGhostObject
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
	void GhostBoxObject(CVector3 pos, CQuaternion rot, CVector3 size);

private:
	bool						m_isRegistPhysicsWorld = false;	//!<�������[���h�ɓo�^���Ă��邩�ǂ����̃t���O�B
	BoxCollider					m_boxCollider;	//�{�b�N�X�R���C�_�[�B
	btGhostObject				m_ghostObject;	//!<�S�[�X�g�B

};

