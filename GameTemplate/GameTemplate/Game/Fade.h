#pragma once
class Fade
{
public:
	Fade();
	~Fade();
	enum State {
		None,
		Fadein,		//�t�F�[�h�C��
		FadeOut		//�t�F�[�h�A�E�g
	};
	void Update();
	/// <summary>
	/// �X�v���C�g�̐ݒ�B
	/// </summary>
	/// <param name="sprite"></param>
	void SetSprite(Sprite sprite) {
		m_sptite = &sprite;
	}
	/// <summary>
	/// �X�e�[�g�̐ݒ�
	/// </summary>
	void SetState(State state) {
		m_state = state;
	}
private:
	Sprite* m_sptite;		//�X�v���C�g�B
	State m_state = None;
};

