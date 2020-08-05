#pragma once
class Fade : public IGameObject
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
	void SetSprite(SpriteRender sprite) {
		m_sptiteRender = &sprite;
	}
private:
	SpriteRender* m_sptiteRender;		//�X�v���C�g�B
	State m_state = None;
	CVector4 mulColorin;
	CVector4 mulColorout;

};

