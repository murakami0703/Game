#pragma once

class EffectEngine
{
public:
	EffectEngine();
	~EffectEngine();
	//更新
	void Update();
	//描画
	void EffektRender();

	//Effekseerの初期化。
	void InitEffekseer();
	/// <summary>
	/// Effekseerのエフェクトを作成。
	/// </summary>
	Effekseer::Effect* CreateEffekseerEffect(const wchar_t* filePath);
	/// <summary>
	/// Effekseerのエフェクトを再生。
	/// </summary>
	Effekseer::Handle Play(Effekseer::Effect* effect, CVector3 pos = CVector3().Zero());
	/// <summary>
	/// Effekseerマネージャの取得。
	/// </summary>
	Effekseer::Manager& GetEffekseerManager()
	{
		return *m_effekseerManager;
	}
	/// <summary>
	/// Effekseerのエフェクトの停止。
	/// </summary>
	void Stop(Effekseer::Handle handle);


	//更新
	void Update2D();
	//描画
	void EffektRender2D();
	//2DEffekseerの初期化。
	void InitEffekseer2D();
	/// <summary>
	/// Effekseerのエフェクトを作成。
	/// </summary>
	Effekseer::Effect* CreateEffekseerEffect2D(const wchar_t* filePath);
	/// <summary>
	/// Effekseerのエフェクトを再生。
	/// </summary>
	Effekseer::Handle Play2D(Effekseer::Effect* effect, CVector3 pos = CVector3().Zero());
	/// <summary>
	/// Effekseerマネージャの取得。
	/// </summary>
	Effekseer::Manager& GetEffekseerManager2D()
	{
		return *m_effekseerManager2D;
	}
	/// <summary>
	/// Effekseerのエフェクトの停止。
	/// </summary>
	void Stop2D(Effekseer::Handle handle);


private:
	//Effekseerマネージャ管理。
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;

	Effekseer::Manager*	m_effekseerManager2D = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer2D = nullptr;

};

