#pragma once
class Effect
{
	/// <summary>
	/// �G�t�F�N�g
	/// </summary>
public:
	Effect();
	~Effect();
	void Update();
	void Drew();

	//Effekseer�̏������B
	void InitEffekseer();

	//Effect�̃Z�b�g�B
	void SetEffect();
private:
	//Effekseer�}�l�[�W���Ǘ��B
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
};

