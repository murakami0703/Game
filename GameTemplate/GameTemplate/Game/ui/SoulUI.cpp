#include "stdafx.h"
#include "ui/SoulUI.h"
#include "data/GameData.h"

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const CVector3 SOUL_FRAME_POS = { -800.0f,200.0f,0.0f };			//�t���[���̍��W�B
const float SOUL_FLANE_ALPHA = 0.8f;								//�t���[���̓����x�B
const CVector3 SOUL_POS = { -840.0f,200.0f,0.0f };					//���̍��W�B
const CVector3 SOULANDFRAME_SCALE = { 0.35f,0.35f,0.35f };			//���ƃt���[���̊g�嗦�B

const float SOUL_FRAME_UPBOUND = -500.0f;							//�t���[���̃o�E���h��X���ɏ㏸����ʒu�B
const float SOUL_FRAME_DOWNBOUND = -540.0f;							//�t���[���̃o�E���h��X���ɉ��~����ʒu�B
const float SOUL_ICON_UPBOUND = -540.0f;							//���A�C�R���̃o�E���h��X���ɏ㏸����ʒu�B
const float SOUL_ICON_DOWNBOUND = -580.0f;							//���A�C�R���̃o�E���h��X���ɉ��~����ʒu�B

const float UPBOUND_ADD = 10.0f;									//�㏸�o�E���h�����Z����l�B
const float DOWNBOUND_ADD = 5.0f;									//���~�o�E���h�����Z����l�B

const CVector2 SOUL_COUNT_FONT_POS = { -780.0f,230.0f };			//�J�E���g�t�H���g�̍��W�B
const float SOUL_COUNT_FONT_SCALE = 2.0f;							//�J�E���g�t�H���g�̊g�嗦�B

const float SOUL_COUNT_FONT_X_UPBOUND = -480.0f;					//���J�E���g�t�H���g�̃o�E���h��X���ɏ㏸����ʒu�B
const float SOUL_COUNT_FONT_X_DOWNBOUND = -520.0f;					//���J�E���g�t�H���g�̃o�E���h��X���ɉ��~����ʒu�B

const float SOUL_COUNT_FONT_UPBOUND = 250.0f;						//�J�E���g�t�H���g�̃o�E���h��Y���ɏ㏸����ʒu�B
const float SOUL_COUNT_FONT_DOWNBOUND = 230.0f;						//�J�E���g�t�H���g�̃o�E���h��Y���ɉ��~����ʒu�B
const float SOUL_COUNT_FONT_BOUND_ADD = 5.0f;						//�J�E���g�t�H���g�̃o�E���h�����Z����l�B

const int INDICATE_END = 200;										//���J�E���gUI�̕\���I���^�C���B
const float RETURN_MOVE_SPEED = 10.0f;								//���ɖ߂��Ƃ��̈ړ����x�B

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

	swprintf(soulNum, MAX_PATH - 1, L"%02d", m_soulNowNum);
	m_soulFont->SetText(soulNum);
	m_soulFont->SetPosition(SOUL_COUNT_FONT_POS);
	m_soulFont->SetScale(SOUL_COUNT_FONT_SCALE);

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
	CVector3 m_framePos = m_spriteRender[0]->GetPosition();		//�t���[�����W�B
	CVector3 m_soulIconPos = m_spriteRender[1]->GetPosition();	//���A�C�R�����W�B
	CVector2 m_soulCountPos = m_soulFont->GetPosition();		//�t�H���g���W�B
	
	if (m_framePos.x < SOUL_FRAME_UPBOUND &&
		m_soulIconPos.x < SOUL_ICON_UPBOUND &&
		m_soulCountPos.x < SOUL_COUNT_FONT_X_UPBOUND &&
		bound == false) {
		m_framePos.x += UPBOUND_ADD;
		m_soulIconPos.x += UPBOUND_ADD;
		m_soulCountPos.x += UPBOUND_ADD;
	}
	else {
		bound = true;
		//��������o�E���h����
		if (m_framePos.x > SOUL_FRAME_DOWNBOUND &&
			m_soulIconPos.x > SOUL_ICON_DOWNBOUND &&
			m_soulCountPos.x > SOUL_COUNT_FONT_X_DOWNBOUND &&
			bound == true) {
			m_framePos.x -= DOWNBOUND_ADD;
			m_soulIconPos.x -= DOWNBOUND_ADD;
			m_soulCountPos.x -= DOWNBOUND_ADD;
		}
		else {
			//�o�E���h�I���A���̏�����...�B
			bound = false;
			m_soulUiState = SoulUI_SoulCount;
		}

	}
	m_spriteRender[0]->SetPosition(m_framePos);
	m_spriteRender[1]->SetPosition(m_soulIconPos);
	m_soulFont->SetPosition(m_soulCountPos);

}		
void SoulUI::SoulCount()
{
	//���̉��Z�B
	GameData* gamedate = GameData::GetInstance();
	m_soulNowNum++;
	swprintf(soulNum, MAX_PATH - 1, L"%02d", gamedate->GetSoul());
	m_soulFont->SetText(soulNum);
	m_soulUiState = SoulUI_FontBoundMove;

}
void SoulUI::FontBoundMove()
{
	//���l�����t�H���g�̃J�E���g���o�E���h�����鏈���B
	//�o�E���h�����B	
	CVector2 m_position = m_soulFont->GetPosition();	//�t�H���g���W�B

	if (m_position.y < SOUL_COUNT_FONT_UPBOUND && bound == false) {
		m_position.y += SOUL_COUNT_FONT_BOUND_ADD;
	}
	else {
		bound = true;
		//��������o�E���h����
		if (bound == true && m_position.y > SOUL_COUNT_FONT_DOWNBOUND) {
			m_position.y -= SOUL_COUNT_FONT_BOUND_ADD;
		}
		else {
			//�o�E���h�I���A���̏�����...�B
			bound = false;
			m_soulUiState = SoulUI_Indicate;
		}

	}
	m_soulFont->SetPosition(m_position);

}
void SoulUI::SoulUIIndicate()
{
	GameData* gamedate = GameData::GetInstance();
	//��莞�Ԃ����\����Ԃ̂܂ܕۂB
	m_indicateTimer++;

	if (m_indicateTimer >= INDICATE_END) {
		m_indicateTimer = 0;
		m_soulUiState = SoulUI_Return;
	}

	//�����\����Ԓ��ɍ����擾������
	//�J�E���g�o�E���h��Ԃɖ߂�܂��B
	if (gamedate->GetSoul() > m_soulNowNum) {
		m_indicateTimer = 0;
		m_soulUiState = SoulUI_SoulCount;
	}
}
void SoulUI::SoulUIReturn()
{
	//���̏�Ԃɖ߂��B
	CVector3 m_framePos = m_spriteRender[0]->GetPosition();		//�t���[�����W�B
	CVector3 m_soulIconPos = m_spriteRender[1]->GetPosition();	//���A�C�R�����W�B
	CVector2 m_soulCountPos = m_soulFont->GetPosition();		//�t�H���g���W�B

	if (m_framePos.x > SOUL_FRAME_POS.x &&
		m_soulIconPos.x > SOUL_POS.x &&
		m_soulCountPos.x > SOUL_COUNT_FONT_POS.x) {
		m_framePos.x -= RETURN_MOVE_SPEED;
		m_soulIconPos.x -= RETURN_MOVE_SPEED;
		m_soulCountPos.x -= RETURN_MOVE_SPEED;
	}
	else {
		m_soulUiState = SoulUI_Default;
	}

	m_spriteRender[0]->SetPosition(m_framePos);
	m_spriteRender[1]->SetPosition(m_soulIconPos);
	m_soulFont->SetPosition(m_soulCountPos);

}
void SoulUI::Update()
{

	switch (m_soulUiState)
	{
	case SoulUI::SoulUI_Default:
		SoulUIDefault();
		break;
	case SoulUI::SoulUI_GetMove:
		SoulUIGetMove();
		break;
	case SoulUI::SoulUI_SoulCount:
		SoulCount();
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

}

