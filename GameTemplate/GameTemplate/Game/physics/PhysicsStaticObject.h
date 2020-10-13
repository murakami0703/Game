/*!
 * @brief	�ÓI�I�u�W�F�N�g�B
 */

#pragma once

#include "physics/MeshCollider.h"
#include "physics/RigidBody.h"
#include "PhysicsObjectBase.h"

/*!
* @brief	�ÓI�����I�u�W�F�N�g
*/
class PhysicsStaticObject : public PhysicsObjectBase {
public:
	/*!
		* @brief	�R���X�g���N�^�B
		*/
	PhysicsStaticObject();
	/*!
		* @brief	�f�X�g���N�^�B
		*/
	~PhysicsStaticObject();
	/*!
		* @brief	����B
		*/
	void Release() override final;
	/*!
	* @brief	���W�Ɖ�]��ݒ�B
	*/
	void SetPositionAndRotation(const CVector3& pos, const CQuaternion& rot)
	{
		m_rigidBody.SetPositionAndRotation(pos, rot);
	}
	RigidBody& GetRigidBody()
	{
		return m_rigidBody;
	}
private:

	/*!
	* @brief	�ÓI�����I�u�W�F�N�g�쐬�����̋��ʏ����B
	*/
	void CreateCommon(CVector3 pos, CQuaternion rot) override final;
private:
	RigidBody m_rigidBody;				//!<���́B
};
