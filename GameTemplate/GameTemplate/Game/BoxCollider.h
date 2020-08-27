/// <summary>
/// ボックスコライダー。
/// </summary>

#pragma once
#include "Physics/ICollider.h"

/// <summary>
/// ボックスコライダー。
/// </summary>
class BoxCollider : public ICollider
{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	BoxCollider();
	/*!
	 * @brief	デストラクタ。
	 */
	~BoxCollider();
	/*!
	 * @brief	ボックスコライダーを作成。
	 */
	void Create(const CVector3& size);
	btCollisionShape* GetBody() const override
	{
		return shape;
	}
private:
	btBoxShape*		shape = nullptr;
};

