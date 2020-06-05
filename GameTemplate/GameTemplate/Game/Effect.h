#pragma once
class Effect
{
	/// <summary>
	/// �G�t�F�N�g
	/// </summary>
public:
	Effect();
	~Effect();
	//�X�V
	void Update();
	//�`��
	void Render();

	//Effekseer�̏������B
	void InitEffekseer();

private:
	//Effekseer�}�l�[�W���Ǘ��B
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
};

