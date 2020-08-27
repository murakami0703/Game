/// <summary>
/// �{�b�N�X�R���C�_�[�B
/// </summary>

#pragma once
#include "Physics/ICollider.h"

/// <summary>
/// �{�b�N�X�R���C�_�[�B
/// </summary>
class BoxCollider : public ICollider
{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	BoxCollider();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~BoxCollider();
	/*!
	 * @brief	�{�b�N�X�R���C�_�[���쐬�B
	 */
	void Create(const CVector3& size);
	btCollisionShape* GetBody() const override
	{
		return shape;
	}
private:
	btBoxShape*		shape = nullptr;
};

