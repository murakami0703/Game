#pragma once



class ICollider;

//剛体情報。
struct RigidBodyInfo {

	CVector3 pos = CVector3::Zero();			//座標。
	CQuaternion rot = CQuaternion::Identity();	//回転。
	ICollider* collider = nullptr;				//コライダー。
	float mass = 0.0f;							//質量。

};
//剛体クラス。
class RigidBody
{
	btRigidBody*			rigidBody = nullptr;		//剛体。
	btDefaultMotionState*	myMotionState = nullptr;	//モーションステート。
	bool m_isAddPhysicsWorld = false;			//物理ワールドに追加されている？
public:

	~RigidBody();
	void Release();
	void Create(RigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return rigidBody;
	}
	//物理ワールドに登録中の印をつける。
	void SetMarkAddPhysicsWorld()
	{
		m_isAddPhysicsWorld = true;
	}
	//物理ワールドに登録中の印を外す。
	void SetUnmarkAddPhysicsWorld()
	{
		m_isAddPhysicsWorld = false;
	}
	//物理ワールドに追加されている？
	bool IsAddPhysicsWorld() const
	{
		return m_isAddPhysicsWorld;
	}
	/*!
	* @brief	物理オブジェクトの座標と回転を取得
	*@param[out]	pos			座標。
	*@param[out]	rot			回転。
	*/
	void GetPositionAndRotation(CVector3& pos, CQuaternion& rot) const
	{
		btTransform trans;
		myMotionState->getWorldTransform(trans);
		pos.Set(trans.getOrigin());
		rot.Set(trans.getRotation());
	}
	/*!
	* @brief	物理オブジェクトの座標と回転を設定
	*@param[in]	pos			座標。
	*@param[in]	rot			回転。
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

