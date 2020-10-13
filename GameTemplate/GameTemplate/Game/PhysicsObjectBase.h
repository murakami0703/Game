#pragma once

/// <summary>
/// 物理オブジェクトのベースクラス。
/// </summary>
/// 
 #include "Physics/ICollider.h"

class PhysicsObjectBase
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	PhysicsObjectBase();

	/// <summary>
	/// デストラクタ。
	/// </summary>
	~PhysicsObjectBase();

	/// <summary>
	/// ゴーストオブジェクトを解放。
	/// </summary>
	virtual void Release() = 0;
private:
	/// <summary>
	/// 静的物理オブジェクト作成処理の共通処理。
	/// </summary>
	/// <param name="pos">座標。</param>
	/// <param name="rot">回転。</param>
	virtual void CreateCommon(CVector3 pos, CQuaternion rot) = 0;

public:
	/*!
		 * @brief	ボックス形状のゴーストオブジェクトを作成。
		 *@param[in]	pos			座標。
		 *@param[in]	rot			回転。
		 *@param[in]	size		サイズ。
		 */
	void CreateBox(CVector3 pos, CQuaternion rot, CVector3 size);
	/*!
	 * @brief	カプセル形状のゴーストオブジェクトを作成。
	 *@param[in]	pos			座標。
	 *@param[in]	rot			回転。
	 *@param[in]	radius		カプセルの半径。
	 *@param[in]	height		カプセルの高さ。
	 */
	void CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height);
	/*!
	* @brief	球体形状のゴーストオブジェクトを作成。
	*@param[in]	pos			座標。
	*@param[in]	rot			回転。
	*@param[in]	radius		球体の半径。
	*/
	void CreateSphere(CVector3 pos, CQuaternion rot, float radius);
	/*!
	* @brief	メッシュ形状のゴーストオブジェクトを作成。
	*@param[in]	pos					座標。
	*@param[in]	rot					回転。
	*@param[in]	skinModelData		スキンモデルデータ。
	*/
	void CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, const SkinModel& skinModel);
	void CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, SkinModelRender* skinModelRender);
protected:
	std::unique_ptr<ICollider> m_collider;	//!<コライダー。

};

