#include "stdafx.h"
#include "scene/GameOver.h"

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const CVector3 CONTINUITY_SET_POS = { 200.0f, -250.0f, 0.0f };	//�u�R���e�B�j���[�v�{�^���̍��W�B
const CVector3 EXIT_SET_POS = { 200.0f, -300.0f, 0.0f };		//�u�I���v�{�^���̍��W�B

const CVector3 GAMEOVER_SET_SCALE = { 0.5f, 0.5f, 0.5f };		//�Q�[���I�[�o�[�̊g�嗦�B
const CVector3 BUTTON_SET_SCALE = { 0.3f, 0.3f, 0.3f };			//�{�^���̊g�嗦�B

const float BG_SET_MULCOLOR = 0.3f;								//BG�̃J���[�̍ŏI��Z�l�B
const float BG_DECREASE_VALUE = 0.1f;							//BG�̃J���[�̌����l�B

const float ACTIVE_TRUE = 1.0f;									//�����x(�\��)�B
const float ACTIVE_FALSE = 0.0f;								//�����x(��\��)�B

const float GAMEOVER_SET_POSY = 400.0f;							//GameOver�̏����x�ʒu�B
const float GAMEOBER_BOUND_POSY = 220.0f;						//GameOver�̉��~�ʒu�B
const float GAMEOVER_BOUND_SET_POSY = 250.0f;					//GameOver�̃o�E���h��̈ʒu�B
const float GAMEOVER_MOVESPEED = 10.0f;							//GameOver�̈ړ����x�B

const float BUTTON_ACTIVE_TIME = 20.0f;							//�{�^����\�������鎞�ԁB�P�ʁF�t���[��
const float CONTINUITY_FADE_DELTA_ALPHA = 1.0f / 20.0f;			//�u�R���e�B�j���[�v�̓����x��ψʂ�����l�B
const float EXIT_FADE_DELTA_ALPHA = 0.3f / 20.0f;				//�u�I���v�̓����x��ψʂ�����l�B
const float BUTTON_SELECT = 1.0f;								//�I�𒆂̃t�H���g�B
const float BUTTON_NOT_SELECT = 0.3f;							//�I���O�̃t�H���g�B


GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}


bool GameOver::Start()
{

	//0�ԁ�GameOver
	m_gameOverSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_gameOverSprite->Init(L"Assets/sprite/gameover.dds", 700.0f, 150.0f);
	m_gameOverSprite->SetPosition({ 0.0f,GAMEOVER_SET_POSY ,0.0f });
	m_gameOverSprite->SetScale(GAMEOVER_SET_SCALE);
	m_gameOverSprite->SetAlpha(ACTIVE_FALSE);
	m_spriteRender.push_back(m_gameOverSprite);

	//�{�^���B
	{
		//1�ԁ�Continuity
		m_gameOverSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_gameOverSprite->Init(L"Assets/sprite/continuity.dds", 300.0f, 100.0f);
		m_gameOverSprite->SetPosition(CONTINUITY_SET_POS);
		m_gameOverSprite->SetScale(BUTTON_SET_SCALE);
		m_gameOverSprite->SetAlpha(ACTIVE_FALSE);
		m_spriteRender.push_back(m_gameOverSprite);

		//2�ԁ�Exit
		m_gameOverSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_gameOverSprite->Init(L"Assets/sprite/exit.dds", 150.0f, 100.0f);
		m_gameOverSprite->SetPosition(EXIT_SET_POS);
		m_gameOverSprite->SetScale(BUTTON_SET_SCALE);
		m_gameOverSprite->SetAlpha(ACTIVE_FALSE);
		m_spriteRender.push_back(m_gameOverSprite);

	}
	return true;
}


void GameOver::BackGDDark()
{
	//�w�i���Â����܂����B
	if (m_mulColor > BG_SET_MULCOLOR) {
		m_mulColor -= BG_DECREASE_VALUE;
		g_goMgr->SetMainSpriteMulColor({ m_mulColor,m_mulColor, m_mulColor, ACTIVE_TRUE });
	}
	else {
		//���̏����ցB
		m_state = GameOver_Set;
	}
}
void GameOver::GameOverSet()
{
	//�Q�[���I�[�o�[�̕������o���B

	CVector3 m_position = m_spriteRender[0]->GetPosition();

	if (m_position.y > GAMEOBER_BOUND_POSY && m_bound == false) {
		m_position.y -= GAMEOVER_MOVESPEED;
	}
	else {
		m_bound = true;
		//��������o�E���h����
		if (m_bound == true && m_position.y < GAMEOVER_BOUND_SET_POSY) {
			m_position.y += GAMEOVER_MOVESPEED;
		}
		else {
			//�o�E���h�I���A���̏�����...�B
			m_bound = false;
			m_state = SelectButton_Set;
		}

	}
	m_spriteRender[0]->SetAlpha(1.0f);
	m_spriteRender[0]->SetPosition(m_position);

}
void GameOver::SelectButtonSet()
{
	//�I���{�^���̕\���B
	//�����x�����Z���ĕ\�������܂��B
	m_buttonActiveTimer++;
	if(m_buttonActiveTimer < BUTTON_ACTIVE_TIME) {
		m_spriteRender[1]->SetAlpha(CONTINUITY_FADE_DELTA_ALPHA);
		m_spriteRender[2]->SetAlpha(EXIT_FADE_DELTA_ALPHA);
	}
	else{
		m_state = Button_Select;
	}

}

void GameOver::ButtonSelect()
{
	//�{�^���I���B
	if (g_pad[0].IsTrigger(enButtonA)) {
		m_spriteRender[1]->SetAlpha(ACTIVE_FALSE);
		m_spriteRender[2]->SetAlpha(ACTIVE_FALSE);
		//m_se = g_goMgr->NewGameObject<CSoundSource>();
		//m_se->Init(L"Assets/sound/Decision.wav");
		//m_se->SetVolume(DECIDED_SE_VOLUME);
		//m_se->Play(false);
		m_state = Scene_Switching;
	}
	else if (m_buttonState == Button_Exit && g_pad[0].IsTrigger(enButtonLeft)) {
		//�u�R���e�B�j���[�v��I������B
		m_buttonState = Button_Continuity;
		m_spriteRender[1]->SetAlpha(BUTTON_SELECT);
		m_spriteRender[2]->SetAlpha(BUTTON_NOT_SELECT);
		//m_se = g_goMgr->NewGameObject<CSoundSource>();
		//m_se->Init(L"Assets/sound/SelectButton.wav");
		//m_se->SetVolume(SELECT_SE_VOLUME);
		//m_se->Play(false);
	}
	else if (m_buttonState == Button_Continuity && g_pad[0].IsTrigger(enButtonRight)) {
		//�u�I���v��I������B
		m_buttonState = Button_Exit;
		m_spriteRender[1]->SetAlpha(BUTTON_SELECT);
		m_spriteRender[2]->SetAlpha(BUTTON_NOT_SELECT);
		//m_se = g_goMgr->NewGameObject<CSoundSource>();
		//m_se->Init(L"Assets/sound/SelectButton.wav");
		//m_se->SetVolume(SELECT_SE_VOLUME);
		//m_se->Play(false);
	}

}

void GameOver::Continuity()
{
	//�R���e�B�j���[�B
	//�F�X���̏�Ԃɖ߂��܂��傤�B
}
void GameOver::Exit()
{
	//�I���B
	//�S�������܂��B
}

void GameOver::SceneSwitching()
{
	//�V�[���؂�ւ��B
	switch (m_buttonState)
	{
	case GameOver::Button_Continuity:
		Continuity();
		break;
	case GameOver::Button_Exit:
		Exit();
		break;
	}
}


void GameOver::Update()
{
	switch (m_state)
	{
	case GameOver::BackGD_Dark:
		BackGDDark();
		break;
	case GameOver::GameOver_Set:
		GameOverSet();
		break;
	case GameOver::SelectButton_Set:
		SelectButtonSet();
		break;
	case GameOver::Button_Select:
		ButtonSelect();
		break;
	case GameOver::Scene_Switching:
		SceneSwitching();
		break;
	}	


}

