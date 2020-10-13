#pragma once

/// <summary>
/// �����I�u�W�F�N�g�̃x�[�X�N���X�B
/// </summary>
/// 
 #include "Physics/ICollider.h"

class PhysicsObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	PhysicsObjectBase();

	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~PhysicsObjectBase();

	/// <summary>
	/// �S�[�X�g�I�u�W�F�N�g������B
	/// </summary>
	virtual void Release() = 0;
private:
	/// <summary>
	/// �ÓI�����I�u�W�F�N�g�쐬�����̋��ʏ����B
	/// </summary>
	/// <param name="pos">���W�B</param>
	/// <param name="rot">��]�B</param>
	virtual void CreateCommon(CVector3 pos, CQuaternion rot) = 0;

public:
	/*!
		 * @brief	�{�b�N�X�`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		 *@param[in]	pos			���W�B
		 *@param[in]	rot			��]�B
		 *@param[in]	size		�T�C�Y�B
		 */
	void CreateBox(CVector3 pos, CQuaternion rot, CVector3 size);
	/*!
	 * @brief	�J�v�Z���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
	 *@param[in]	pos			���W�B
	 *@param[in]	rot			��]�B
	 *@param[in]	radius		�J�v�Z���̔��a�B
	 *@param[in]	height		�J�v�Z���̍����B
	 */
	void CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height);
	/*!
	* @brief	���̌`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
	*@param[in]	pos			���W�B
	*@param[in]	rot			��]�B
	*@param[in]	radius		���̂̔��a�B
	*/
	void CreateSphere(CVector3 pos, CQuaternion rot, float radius);
	/*!
	* @brief	���b�V���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
	*@param[in]	pos					���W�B
	*@param[in]	rot					��]�B
	*@param[in]	skinModelData		�X�L�����f���f�[�^�B
	*/
	void CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, const SkinModel& skinModel);
	void CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, SkinModelRender* skinModelRender);
protected:
	std::unique_ptr<ICollider> m_collider;	//!<�R���C�_�[�B

};

