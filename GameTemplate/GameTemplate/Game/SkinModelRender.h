#pragma once
/// <summary>
/// 3Dモデルを表示する機能を提供するクラス。
/// </summary>
class SkinModelRender : public IGameObject
{
public:
	SkinModelRender();
	~SkinModelRender();
	
	/// <summary>
	/// 初期化。
	/// </summary>
	void Init();

	/// <summary>
	/// アニメーションの再生。
	/// </summary>
	void PlayAnimation();

	/// <summary>
	/// アニメーションの初期化。
	/// </summary>
	void InitAnimation();

	/// <summary>
	/// 座標を設定。
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	/// <param name="rotation">回転</param>
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// 拡大率を設定。
	/// </summary>
	/// <param name="scl">拡大率</param>
	void SetScale(const CVector3& scl)
	{
		m_scale = scl;
	}
	/// <summary>
	/// 更新前に呼ばれる関数。
	/// </summary>
	bool Start();

	/// <summary>
	/// 更新。
	/// </summary>
	void Update();

private:
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position;			//座標。
	CQuaternion m_rotation;			//回転。
	CVector3 m_scale = CVector3().One();			//拡大率。

};

