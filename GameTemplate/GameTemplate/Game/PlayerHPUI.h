#pragma once
class PlayerHPUI : public IGameObject
{
public:
	PlayerHPUI();
	~PlayerHPUI();

	bool Start() override;
	void Update() override;

private:
	void HPCalc(const float damegeValue);		//HP�̑����v�Z�����B

private:
	std::vector<SpriteRender*> m_spriteRender;			//�X�v���C�g�̓��I�z��B
	SpriteRender* m_hpRender;							//�X�v���C�g�����_�[�B

	float m_nowHP = 0;									//���݂�HP�̒l�B
	int m_hpSpriteNum = 0;								//HP�X�v���C�g�̕\�����̐��B

	CVector3 m_hpPos = { -650.0f,330.0f,0.0f };			//HP�̍��W�B

};

