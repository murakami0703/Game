#include "stdafx.h"
#include "SoulUI.h"
#include "GameData.h"

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const CVector3 SOUL_FRAME_POS = { -800.0f,200.0f,0.0f };			//�t���[���̍��W
const float SOUL_FLANE_ALPHA = 0.8f;								//�t���[���̓����x�B
const CVector3 SOUL_POS = { -575.0f,200.0f,0.0f };					//���̍��W
const CVector3 SOULANDFRAME_SCALE = { 0.35f,0.35f,0.35f };			//���ƃt���[���̊g�嗦


SoulUI::SoulUI()
{
}


SoulUI::~SoulUI()
{
}

bool SoulUI::Start()
{
	//0�ԁ��t���[��
	m_soulRender = g_goMgr->NewGameObject<SpriteRender>();
	m_soulRender->Init(L"Assets/sprite/Ui_SouiFrame.dds", 800.0f, 300.0f);
	m_soulRender->SetPosition(SOUL_FRAME_POS);
	m_soulRender->SetScale(SOULANDFRAME_SCALE);
	m_soulRender->SetAlpha(SOUL_FLANE_ALPHA);
	m_spriteRender.push_back(m_soulRender);

	//1�ԁ���
	m_soulRender = g_goMgr->NewGameObject<SpriteRender>();
	m_soulRender->Init(L"Assets/sprite/Ui_Soui.dds", 400.0f, 300.0f);
	m_soulRender->SetPosition(SOUL_POS);
	m_soulRender->SetScale(SOULANDFRAME_SCALE);
	m_spriteRender.push_back(m_soulRender);

	//���J�E���g�t�H���g�̐ݒ�B
	GameData* gamedate = GameData::GetInstance();
	m_soulFont = g_goMgr->NewGameObject<FontRender>();
	m_soulNowNum = gamedate->GetSoul();
	wchar_t text[MAX_PATH];
	swprintf(text, MAX_PATH - 1, L"%02d", m_soulNowNum);
	m_soulFont->SetText(text);
	m_soulFont->SetScale(2.0f);
	m_soulFont->SetPosition({ -490.0f,230.0f });

	return true;
}
void SoulUI::SoulUIDefault()
{
	//�ʏ��ԁB(��\���j
	GameData* gamedate = GameData::GetInstance();

	//�������W�����Ƃ��B
	if (gamedate->GetSoul() > m_soulNowNum) {
		m_soulUiState = SoulUI_GetMove;
	}

}
void SoulUI::SoulUIGetMove()
{
	//���l���������o�[�̏o�������B
	//���U���g�����\���B
	//�E����\��������B
	CVector3 m_position = m_spriteRender[0]->GetPosition();	//���W�B

	if (m_position.x < -500.0f && bound == false) {
		m_position.x += 20.0f;
	}
	else {
		bound = true;
		//��������o�E���h����
		if (bound == true && m_position.x > -530.0f) {
			m_position.x -= 5.0f;
		}
		else {
			//�o�E���h�I���A���̏�����...�B
			bound = false;
			m_soulUiState = SoulUI_FontBoundMove;
		}

	}
	m_spriteRender[0]->SetAlpha(1.0f);
	m_spriteRender[0]->SetPosition(m_position);
}
void SoulUI::FontBoundMove()
{
	//���l�����t�H���g�̃J�E���g���o�E���h�����鏈���B
}
void SoulUI::SoulUIIndicate()
{
	//��莞�Ԃ����\����Ԃ̂܂ܕۂB
}
void SoulUI::SoulUIReturn()
{
	//���̏�Ԃɖ߂��B
}
void SoulUI::Update()
{
	GameData* gamedate = GameData::GetInstance();

	switch (m_soulUiState)
	{
	case SoulUI::SoulUI_Default:
		SoulUIDefault();
		break;
	case SoulUI::SoulUI_GetMove:
		SoulUIGetMove();
		break;
	case SoulUI::SoulUI_FontBoundMove:
		FontBoundMove();
		break;
	case SoulUI::SoulUI_Indicate:
		SoulUIIndicate();
		break;
	case SoulUI::SoulUI_Return:
		SoulUIReturn();
		break;
	}

	//���̉��Z�B
	//wchar_t text[MAX_PATH];
	//swprintf(text, MAX_PATH - 1, L"%02d", gamedate->GetSoul());
	//m_soulFont->SetText(text);
	//m_soulNowNum++;

}

