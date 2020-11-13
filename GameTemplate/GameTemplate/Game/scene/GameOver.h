#pragma once
#include "SpriteIActor.h"

class GameOver : public SpriteIActor
{
public:
	GameOver();
	~GameOver();

	bool Start();
	void Update();

private:

	enum eState {
		BackGD_Dark,			//�Q�[���V�[�����D�F�ɁB
		GameOver_Set,			//GAMEOVER�̕����o���B
		SelectButton_Set,		//�I���{�^���̕\���B
		Button_Select,			//�{�^���I���B
		Scene_Switching			//�V�[���؂�ւ��B
	};

	//�I���{�^��
	enum EButton {
		Button_Continuity,
		Button_Exit
	};

private:

	void BackGDDark();			//�Q�[���V�[�����D�F�ɁB
	void GameOverSet();			//GAMEOVER�̕����o���B
	void SelectButtonSet();		//�I���{�^���̕\���B
	void ButtonSelect();		//�{�^���I���B
	void SceneSwitching();		//�V�[���؂�ւ��B

	void Continuity();			//�R���e�B�j���[�B
	void Exit();				//�I���B
private:
	std::vector<SpriteRender*> m_spriteRenderArray;		//�X�v���C�g�̓��I�z��

	eState m_state = BackGD_Dark;					//��ԁB
	EButton m_buttonState = Button_Continuity;		//Button�̑I����ԁB

	bool m_bound = false;				//�o�E���h����B

	float m_mulColor = 1.0f;			//BG�̏�Z�J���[
	
	int m_buttonActiveTimer = 0;		//�{�^����\��������Ƃ��Ɏg���^�C�}�[�B
};

