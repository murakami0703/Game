#pragma once
class FadeIn : public IGameObject
{
public:
	FadeIn();
	~FadeIn();

	bool Start();
	void Update();

	/// <summary>
	/// �X�v���C�g�̐ݒ�B
	/// </summary>
	/// <param name="sprite"></param>
	void SetSprite(SpriteRender* sprite) {
		m_sptiteRender = sprite;
	}
private:
	SpriteRender* m_sptiteRender;		//�X�v���C�g�B
	CVector4 m_mulColor;

};

