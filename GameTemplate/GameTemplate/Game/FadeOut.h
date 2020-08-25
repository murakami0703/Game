#pragma once
class FadeOut : public IGameObject
{
public:
	FadeOut();
	~FadeOut();

	bool Start();
	void Update();

	/// <summary>
	/// �X�v���C�g�̐ݒ�B
	/// </summary>
	/// <param name="sprite">�X�v���C�g</param>
	void SetSprite(SpriteRender* sprite) {
		m_sptiteRender = sprite;
	}

private:
	SpriteRender* m_sptiteRender;				//�X�v���C�g�B
	CVector4 m_mulColor = CVector4().White();	//��Z�J���[�B

};

