#pragma once



class ICollider;

//���̏��B
struct RigidBodyInfo {

	CVector3 pos = CVector3::Zero();			//���W�B
	CQuaternion rot = CQuaternion::Identity();	//��]�B
	ICollider* collider = nullptr;				//�R���C�_�[�B
	float mass = 0.0f;							//���ʁB

};
//���̃N���X�B
class RigidBody
{
	btRigidBody*			rigidBody = nullptr;		//���́B
	btDefaultMotionState*	myMotionState = nullptr;	//���[�V�����X�e�[�g�B
	bool m_isAddPhysicsWorld = false;			//�������[���h�ɒǉ�����Ă���H
public:

	~RigidBody();
	void Release();
	void Create(RigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return rigidBody;
	}
	//�������[���h�ɓo�^���̈������B
	void SetMarkAddPhysicsWorld()
	{
		m_isAddPhysicsWorld = true;
	}
	//�������[���h�ɓo�^���̈���O���B
	void SetUnmarkAddPhysicsWorld()
	{
		m_isAddPhysicsWorld = false;
	}
	//�������[���h�ɒǉ�����Ă���H
	bool IsAddPhysicsWorld() const
	{
		return m_isAddPhysicsWorld;
	}
	/*!
	* @brief	�����I�u�W�F�N�g�̍��W�Ɖ�]���擾
	*@param[out]	pos			���W�B
	*@param[out]	rot			��]�B
	*/
	void GetPositionAndRotation(CVector3& pos, CQuaternion& rot) const
	{
		btTransform trans;
		myMotionState->getWorldTransform(trans);
		pos.Set(trans.getOrigin());
		rot.Set(trans.getRotation());
	}
	/*!
	* @brief	�����I�u�W�F�N�g�̍��W�Ɖ�]��ݒ�
	*@param[in]	pos			���W�B
	*@param[in]	rot			��]�B
	*/
	void SetPositionAndRotation(const CVector3& pos, const CQuaternion& rot)
	{
		btTransform trans;
		btVector3 btPos;
		pos.CopyTo(btPos);
		trans.setOrigin(btPos);
		btQuaternion btRot;
		rot.CopyTo(btRot);
		trans.setRotation(btRot);
		rigidBody->setWorldTransform(trans);
	}

};

