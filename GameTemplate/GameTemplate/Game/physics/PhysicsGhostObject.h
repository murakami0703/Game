/// <summary>
/// ゴーストオブジェクト
/// </summary>
#pragma once
#include "physics/BoxCollider.h"

/// <summary>
/// ゴーストオブジェクト
/// </summary>

class PhysicsGhostObject
{
public:
	/*!
	* @brief	コンストラクタ。
	*/
	PhysicsGhostObject();
	/*!
	* @brief	デストラクタ。
	*/
	~PhysicsGhostObject();

	/*!
	* @brief	引数で渡されたゴーストオブジェクトが自分自身かどうか判定。
	*/
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}

	/// <summary>
	/// ゴーストオブジェクト。
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	void GhostBoxObject(CVector3 pos, CQuaternion rot, CVector3 size);

private:
	bool						m_isRegistPhysicsWorld = false;	//!<物理ワールドに登録しているかどうかのフラグ。
	BoxCollider					m_boxCollider;	//ボックスコライダー。
	btGhostObject				m_ghostObject;	//!<ゴースト。

};

