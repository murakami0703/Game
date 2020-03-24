#pragma once
class SpriteRender : public IGameObject
{
	/// <summary>
	/// スプライトレンダラー
	/// </summary>
	
	void Update();
	void Render();
	void PostRender();
public:
	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="texFilePath">テクスチャのファイルパス</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	void Init(const wchar_t* texFilePath, float w, float h);

	/// <summary>
	/// 座標を設定。
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を取得。
	/// </summary>
	/// <returns></returns>
	const CVector3& GetPosition() const
	{
		return m_position;
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
	/// 回転を取得。
	/// </summary>
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
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
	/// 拡大率を取得。
	/// </summary>
	/// <returns></returns>
	const CVector3& GetScale() const
	{
		return m_scale;
	}
	/// <summary>
	/// 乗算カラーを設定。
	/// </summary>
	/// <param name="mulColor">乗算カラー</param>
	void SetMulColor(const CVector4& mulColor)
	{
		m_sprite.SetMulColor(mulColor);
	}
private:
	Sprite	m_sprite;				//スプライト。
	CVector3 m_position;			//座標。
	CQuaternion m_rotation;			//回転。
	CVector3 m_scale = CVector3().One();			//拡大率。
	CVector2 m_pivot = { 0.5f,0.5f };	// ピボット。

};

