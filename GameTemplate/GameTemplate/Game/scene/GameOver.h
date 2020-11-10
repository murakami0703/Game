#pragma once
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();

	bool Start();
	void Update();

private:
	enum eState {
		BackGD_Dark,		//�Q�[���V�[�����D�F�ɁB
		Sprite_Set,			//GAMEOVER�̕����o���B
		Font_Set
	};

	void BackGDDark();
	void GameOverSet();
	void NextSet();

private:
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_gameOverSprite;
	eState m_state = BackGD_Dark;

	const float m_startYPos = 400.0f;	//GameOver�̏����x�ʒu�B
	const float m_moveYPos = 150.0f;	//GameOver�̉��~�ʒu�B
	const float m_setYPos = 170.0f;		//GameOver�̈ʒu�B

	const float m_overSpeed = 10.0f;	//GameOver�̈ړ����x�B
	bool m_bound = false;

	float m_mulColor = 1.0f;			//BG�̏�Z�J���[
	const float m_SetMulColor = 0.2f;	//BG�̍ŏI��Z�l

};

