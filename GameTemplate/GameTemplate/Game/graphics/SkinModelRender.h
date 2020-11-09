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
	/// <param name="filePath">ロードしたいcmoファイルのファイルパス</param>
	/// <param name="animationClips">アニメーションクリップの配列の先頭アドレス</param>
	/// <param name="numAnimationClips">アニメーションクリップの数</param>
	/// <param name="fbxUpAxis">fbxの上方向</param>
	void Init(const wchar_t* filePath, AnimationClip* animationClips = nullptr,int numAnimationClips = 0, EnFbxUpAxis fbxUpAxis = enFbxUpAxisZ);

	/// <summary>
	/// アニメーションの再生。
	/// </summary>
	/// <param name="animNo">アニメーションクリップの番号。</param>
	/// <param name="interpolateTime">補完時間</param>
	void PlayAnimation(int animNo, float interpolateTime = 0.0f)
	{
		m_animation.Play(animNo, interpolateTime);
	}
	/// <summary>
	/// アニメーションの再生中？
	/// </summary>
	/// <returns>true	アニメーションを再生中。</returns>
	/// <returns>false	アニメーションは再生していない。</returns>
	bool IsPlayingAnimation() const
	{
		return m_animation.IsPlaying();
	}

	/// <summary>
	/// アニメーションの初期化。
	/// </summary>
	/// <param name="animationClips">アニメーションクリップの配列の先頭アドレス</param>
	/// <param name="numAnimationClips">アニメーションクリップの数</param>
	void InitAnimation(AnimationClip* animationClips, int numAnimationClips);

	/// <summary>
	/// スキンモデル取得。
	/// </summary>
	/// <returns>スキンモデル</returns>
	SkinModel& GetSkinModel()
	{
		return m_skinModel;
	}

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
	/// シルエット描画フラグ
	/// </summary>
	/// <param name="flag">trueなら描画</param>
	void SetSilhouette(bool flag)
	{
		m_silhouetteflag = flag;
	}
	/// <summary>
	/// シャドウキャスター描画フラグ
	/// </summary>
	/// <param name="flag">trueなら描画</param>
	void SetShadowCaster(bool flag)
	{
		m_shadowMapFlag = flag;
	}
	/// <summary>
	/// シャドウレシーバーのフラグを設定。
	/// </summary>
	/// <param name="flag"></param>
	void SetShadowReciever(bool flag);

	/// <summary>
	/// ライトの設定。
	/// </summary>
	void SetLightColor(CVector4 color) {
		m_skinModel.SetLightColor(color);
	}

	/// <summary>
	/// a値の設定
	/// </summary>
	void SetAlpha(const float& alpha)
	{
		m_skinModel.SetAlpha(alpha);
	}
	/// <summary>
	/// a値を取得
	/// </summary>
	float GetAlpha()
	{
		return m_skinModel.GetAlpha();
	}

	/// <summary>
	/// α値を変位させる
	/// </summary>
	/// <param name="delta">乗算αを変位させる量</param>
	void DeltaAlpha(float delta)
	{
		m_skinModel.DeltaAlpha(delta);
	}

	/// <summary>
	/// 法線マップの設定。
	/// </summary>
	void SetNormalMap(const wchar_t* filePath)
	{
		//法線マップつけます
		DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), filePath, 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_normalMapSRV
		);
		m_skinModel.SetNormalMap(g_normalMapSRV);
	}
	/// <summary>
	/// スぺキュラマップの設定。
	/// </summary>
	void SetSpecularMap(const wchar_t* filePath)
	{
		//法線マップつけます
		DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), filePath, 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_specularMapSRV
		);
		m_skinModel.SetSpecularMap(g_specularMapSRV);
	}
	/// <summary>
	/// アンビエントマップの設定。
	/// </summary>
	void SetAmbientMap(const wchar_t* filePath)
	{
		//法線マップつけます
		DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), filePath, 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_ambientMapSRV
		);
		m_skinModel.SetAmbientMap(g_ambientMapSRV);
	}

	bool Start();
	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
	/// <summary>
	/// 描画。
	/// </summary>
	void Render();

 private:
	 std::wstring m_filepath;
	SkinModel					m_skinModel;						//スキンモデル。
	CVector3 m_position = CVector3().Zero();			//座標
	CQuaternion m_rotation = CQuaternion().Identity();	//回転
	CVector3 m_scale = CVector3().One();			//拡大率。
	AnimationClip*				m_animationClips = nullptr;			//アニメーションクリップ。
	int							m_numAnimationClips = 0;			//アニメーションクリップの数。
	Animation					m_animation;						//アニメーション。
	bool m_shadowMapFlag = false;		//シャドウマップ描画フラグ
	bool m_silhouetteflag = false;		//シルエット描画フラグ

	//各種マップの設定。
	ID3D11ShaderResourceView* g_normalMapSRV = nullptr;				//法線マップ。
	ID3D11ShaderResourceView* g_specularMapSRV = nullptr;			//スぺキュラマップ。
	ID3D11ShaderResourceView* g_ambientMapSRV = nullptr;			//アンビエントマップ

};

