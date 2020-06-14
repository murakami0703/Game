#pragma once

class EffectEngine
{
public:
	EffectEngine();
	~EffectEngine();
	//�X�V
	void Update();
	//�`��
	void EffektRender();

	//Effekseer�̏������B
	void InitEffekseer();
	/// <summary>
	/// Effekseer�̃G�t�F�N�g���쐬�B
	/// </summary>
	Effekseer::Effect* CreateEffekseerEffect(const wchar_t* filePath);
	/// <summary>
	/// Effekseer�̃G�t�F�N�g���Đ��B
	/// </summary>
	Effekseer::Handle Play(Effekseer::Effect* effect, CVector3 pos = CVector3().Zero());
	/// <summary>
	/// Effekseer�}�l�[�W���̎擾�B
	/// </summary>
	Effekseer::Manager& GetEffekseerManager()
	{
		return *m_effekseerManager;
	}
	/// <summary>
	/// Effekseer�̃G�t�F�N�g�̒�~�B
	/// </summary>
	void Stop(Effekseer::Handle handle);

private:
	//Effekseer�}�l�[�W���Ǘ��B
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;

};

