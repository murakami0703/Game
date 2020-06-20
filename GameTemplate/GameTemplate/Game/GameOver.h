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
		Font_Set,			//GAMEOVER�̕����o���B

	};
	void SpriteMove(SpriteRender* m_sprite);		//�X�v���C�g�̉��~�ړ������B

private:
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* r;

};

