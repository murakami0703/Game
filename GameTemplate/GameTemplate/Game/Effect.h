#pragma once
class Effect
{
	/// <summary>
	/// エフェクト
	/// </summary>
public:
	Effect();
	~Effect();
	void Update();
	void Drew();

	//Effekseerの初期化。
	void InitEffekseer();

	//Effectのセット。
	void SetEffect();
private:
	//Effekseerマネージャ管理。
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
};

