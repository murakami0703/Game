#pragma once
class Effect
{
	/// <summary>
	/// エフェクト
	/// </summary>
public:
	Effect();
	~Effect();
	//更新
	void Update();
	//描画
	void Render();

	//Effekseerの初期化。
	void InitEffekseer();

private:
	//Effekseerマネージャ管理。
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
};

