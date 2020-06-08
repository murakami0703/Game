#pragma once
class Effect : public IGameObject
{
	/// <summary>
	/// エフェクト
	/// </summary>
public:
	Effect();
	~Effect();
	/// <summary>
	/// 解放。
	/// </summary>
	void Release();
	/// <summary>
	/// エフェクトを再生。
	/// </summary>
	/// <param name="filePath">再生するエフェクトのファイルパス。</param>
	void Play(const wchar_t* filePath);
	/// <summary>
	/// 座標を設定。
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転の設定。
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 拡大率を設定。
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// エフェクトが再生中か判定。
	/// </summary>
	bool IsPlay() const
	{
		return g_graphicsEngine->GetEffectEngine().GetEffekseerManager().GetShown(m_handle);
	}
	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
private:
	Effekseer::Effect*	m_effect = nullptr;
	Effekseer::Handle	m_handle = -1;
	CVector3 m_position = CVector3().Zero();			//!<座標。
	CQuaternion m_rotation = CQuaternion().Identity();	//!<回転。
	CVector3 m_scale = CVector3().One();				//!<拡大率。
};
