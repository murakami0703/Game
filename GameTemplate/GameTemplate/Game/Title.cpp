#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "FadeIn.h"
#include "FadeOut.h"

Title* Title::m_instance = nullptr;

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const CVector4 TITLE_SET_MULCOLOR = { 0.0f,0.0f ,0.0f ,1.0f };	//������Z�J���[�̐ݒ�B
const float LIGHT_SET_ALPHA = 0.3f;								//���C�g�̏��������x�B
const float TITLENAME_SET_ALPHA = 0.0f;							//�Q�[�����̏��������x�B
const CVector3 TITLENAME_SET_POSITION = { 0.0f,280.0f,0.0f };	//�Q�[�����̍��W�B
const CVector3 TITLENAME_SET_SCALE = { 0.65f,0.65f,0.65f };		//�Q�[�����̊g�嗦�B

const CVector3 VILLAIN1_POSITION = { 700.0f,-225.0f,0.0f };		//���l1�̍��W�B
const CVector3 VILLAIN_SCALE = { 0.6f,0.6f,0.6f };				//���l�̊g�嗦�B
const float VILLAUN_SET_ACTIVE_TRUE = 1.0f;						//���l�ɐݒ肷�铧���x(�\��)�B
const float VILLAUN_SET_ACTIVE_FALSE = 0.0f;					//���l�ɐݒ肷�铧���x(��\��)�B

const float FONT_SET_ALPHA = 0.0f;								//�t�H���g�̏��������x�B
const CVector2 FONT_START_SET_POSITION = { 250.0f,-250.0f };	//�u�͂��߂�v�̍��W�B
const CVector2 FONT_LOAD_SET_POSITION = { 460.0f,-250.0f };		//�u�Â���v�̍��W�B
const float FONT_SET_SCALE = 1.5f;								//�t�H���g�̊g�嗦�B

const float LIGHT_INCREASE_TIME = 120.0f;					//���C�g�̖��邳�𑝉������鎞�ԁB
const float LIGHT_DECREASE_TIME = 240.0f;					//���C�g�̖��邳�����������鎞�ԁB
const float LIGHT_DELTA_ALPHA = 0.7f/ 120.0f;				//�ψʂ����铧���x�̒l�B
const float LIGHT_TIMER_RESET = 0.0f;						//���C�g�̃^�C�}�[��������Ԃɂ���B

const CVector4 FADEIN_FINISHED = { 1.0f,1.0f,1.0f,1.0f };	//�t�F�[�h�C�����I���l�B
const CVector4 FADEOUTO_FINISHED = { 0.0f,0.0f,0.0f,1.0f };	//�t�F�[�h�A�E�g���I���l�B

const float TITLENAME_FADE_TIME = 30.0f;					//�^�C�g�������t�F�[�h�����鎞�ԁB
const float TITLENAME_FADE_FONT_TIME = 50.0f;				//�t�H���g���t�F�[�h�����鎞�ԁB
const float TITLENAME_FADE_DELTA_ALPHA = 1.0f / 30.0f;		//�^�C�g�����̓����x��ψʂ�����l�B
const float STARTFONT_FADE_DELTA_ALPHA = 1.0f / 20.0f;		//�u�͂��߂�v�̓����x��ψʂ�����l�B
const float LOADFONT_FADE_DELTA_ALPHA = 0.3f / 20.0f;		//�u�Â���v�̓����x��ψʂ�����l�B

const float FONT_SELECT = 1.0f;								//�I�𒆂̃t�H���g�B
const float FONT_NOT_SELECT = 0.3f;							//�I���O�̃t�H���g�B
const float DECIDED_SE_VOLUME = 0.5f;						//���肵���Ƃ������SE�̃{�����[���B
const float SELECT_SE_VOLUME = 0.1f;						//�I��ύX�����Ƃ������SE�̃{�����[���B


const int VILLAUN_MOVE_SPRITE1_TIME = 10;					//1���ڂ�Sprite���ړ�&�؂�ւ��鎞�ԁB
const int VILLAUN_MOVE_SPRITE2_TIME = 20;					//2���ڂ�Sprite���ړ�&�؂�ւ��鎞�ԁB
const int VILLAUN_MUL_VALUE = 2;							//2���ڂ�Sprite�̈ړ��ʂɏ�Z����l�B
const float VILLAUN_TIMER_RESET = 0.0f;						//���l�̃^�C�}�[��������Ԃɂ���B

const float VILLAUN_MOVE_X = 5.0f;							//���l��X���̈ړ��ʁB
const float VILLAUN_FORWARD_LENGTH = 200.0f;				//����(�O��)�ړ����鋗���B
const float VILLAUN_FORWARD_MOVE_Y = 2.0f;					//���l�̍���(�O��)�ړ�����Y���̈ړ��ʁB
const float VILLAUN_STAY_LENGTH = 150.0f;					//���܂鋗���B
const int VILLAUN_CHANGE_TIME = 20;							//���l��؂�ւ��鎞�ԁB
const int VILLAUN_BACK_TIME = 480;							//�E��(���)�ړ����鎞�ԁB
const float VILLAUN_BACK_MOVE_X = 3.0f;						//���l�̉E��(���)�ړ�����X���̈ړ��ʁB
const float VILLAUN_BACK_MOVE_Y = -2.0f;					//���l�̉E��(���)�ړ�����Y���̈ړ��ʁB
const float VILLAUN_SIDEWAYS2_LENGTH = 50.0f;				//���ړ����鋗���B
const float VILLAUN_STOP_LENGTH = -450.0f;					//��~���鋗���B
const int VILLAUN_SIDEWAYS3_TIME = 60;						//���ړ����鎞�ԁB
const float VILLAUN_RESET_LENGTH = -750.0f;					//������Ԃɖ߂������B

Title::Title(){}

Title::~Title()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		g_goMgr->DeleteGameObject(m_spriteRender[i]);
	}
	//�t�H���g
	g_goMgr->DeleteGameObject(m_startFont);
	g_goMgr->DeleteGameObject(m_loadFont);
	g_goMgr->DeleteGameObject(m_titleBgm);

}

bool Title::Start()
{
	m_instance = this;

	//���X�B
	{
		//0�ԁ�Title(�w�i)
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/title.dds", 1280.0f, 720.0f);
		m_titleSprite->SetMulColor(TITLE_SET_MULCOLOR);
		m_spriteRender.push_back(m_titleSprite);

		//1�ԁ�star_chips(����)
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/star_chips.dds", 1280.0f, 720.0f);
		m_titleSprite->SetMulColor(TITLE_SET_MULCOLOR);
		m_spriteRender.push_back(m_titleSprite);

		//2�ԁ�light
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/light.dds", 1280.0f, 720.0f);
		m_titleSprite->SetAlpha(LIGHT_SET_ALPHA);
		m_titleSprite->SetMulColor(TITLE_SET_MULCOLOR);
		m_spriteRender.push_back(m_titleSprite);

		//3�ԁ�Game_title
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/game_title.dds", 650.0f, 150.0f);
		m_titleSprite->SetAlpha(TITLENAME_SET_ALPHA);
		m_titleSprite->SetPosition(TITLENAME_SET_POSITION);
		m_titleSprite->SetScale(TITLENAME_SET_SCALE);
		m_spriteRender.push_back(m_titleSprite);

	}
	//���l�B
	{
		//4�ԁ�Villain1
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain1.dds", 100.0f, 200.0f);
		m_titleSprite->SetPosition(VILLAIN1_POSITION);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_TRUE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//5�ԁ�Villain2
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain2.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//6�ԁ�Villain3
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain3.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//7�ԁ�Villain4
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain4.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//8�ԁ�Villain5
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain5.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//9�ԁ�Villain6
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain6.dds", 120.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//10�ԁ�Villain7
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain7.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//11�ԁ�Villain8
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain8.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//12�ԁ�Villain9
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain9.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);
	}
	//�t�H���g�B
	{
		//�͂��߂�
		m_startFont = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* m_start = L"Start";
		m_startFont->SetText(m_start);
		m_startFont->SetAlpha(FONT_SET_ALPHA);
		m_startFont->SetPosition(FONT_START_SET_POSITION);
		m_startFont->SetScale(FONT_SET_SCALE);
		//��������
		m_loadFont = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* m_load = L"Load";
		m_loadFont->SetText(m_load);
		m_loadFont->SetAlpha(FONT_SET_ALPHA);
		m_loadFont->SetPosition(FONT_LOAD_SET_POSITION);
		m_loadFont->SetScale(FONT_SET_SCALE);

	}
	
	//���B
	m_titleBgm = g_goMgr->NewGameObject<CSoundSource>();
	m_titleBgm->Init(L"Assets/sound/TitleBGM.wav");

	return true;
}
void Title::LightFlashing()
{
	//���C�g�̓_��
	m_flashingTimer++;
	if (m_flashingTimer <= LIGHT_INCREASE_TIME) {
		m_spriteRender[2]->DeltaAlpha(LIGHT_DELTA_ALPHA);
	}
	else if (m_flashingTimer <= LIGHT_DECREASE_TIME)
	{
		m_spriteRender[2]->DeltaAlpha(-LIGHT_DELTA_ALPHA);
	}
	else {
		m_flashingTimer = LIGHT_TIMER_RESET;
	}

}
void Title::TitleFadeIn() 
{
	//�t�F�[�h�C���B
	FadeIn* fadein = g_goMgr->NewGameObject<FadeIn>();
	fadein->SetSprite(m_spriteRender[0]);
	fadein = g_goMgr->NewGameObject<FadeIn>();
	fadein->SetSprite(m_spriteRender[1]);
	fadein = g_goMgr->NewGameObject<FadeIn>();
	fadein->SetSprite(m_spriteRender[2]);

	m_spriteMul = m_spriteRender[2]->GetMulColor();	

	//�t�F�[�h�C�������������̂Ŏ��ցB
	if (m_spriteMul.x >= FADEIN_FINISHED.x && m_spriteMul.y >= FADEIN_FINISHED.y && m_spriteMul.z >= FADEIN_FINISHED.z)
	{
		//BGM�̍Đ�
		m_titleBgm->Play(true);
		m_state = Title_GameTitle;
	}
}
void Title::TitleGameTitle()
{
	//�����̕\���B
	//�^�C�g���̌�ɑI���{�^����\�������܂��B
	m_fontTimer++;
	if (m_fontTimer <= TITLENAME_FADE_TIME) {
		m_spriteRender[3]->DeltaAlpha(TITLENAME_FADE_DELTA_ALPHA);
	}
	else if (m_fontTimer > TITLENAME_FADE_TIME && m_fontTimer <= TITLENAME_FADE_FONT_TIME) {
		m_startFont->DeltaAlpha(STARTFONT_FADE_DELTA_ALPHA);
		m_loadFont->DeltaAlpha(LOADFONT_FADE_DELTA_ALPHA);
	}
	else if (m_fontTimer > TITLENAME_FADE_FONT_TIME) {
		m_state = Title_Select;
	}
}
void Title::TitleSelect()
{
	//���C�g�̓_�ŁB
	LightFlashing();

	//�{�^���I���B
	if (g_pad[0].IsTrigger(enButtonStart)) {
		m_startFont->SetAlpha(FONT_SET_ALPHA);
		m_loadFont->SetAlpha(FONT_SET_ALPHA);
		m_se = g_goMgr->NewGameObject<CSoundSource>();
		m_se->Init(L"Assets/sound/Decision.wav");
		m_se->SetVolume(DECIDED_SE_VOLUME);
		m_se->Play(false);
		m_state = Title_FadeOut;
	}
	else if (m_buttonState == Button_Load && g_pad[0].IsTrigger(enButtonLeft)) {
		//�u�͂��߂�v��I������B
		m_buttonState = Button_Start;
		m_startFont->SetAlpha(FONT_SELECT);
		m_loadFont->SetAlpha(FONT_NOT_SELECT);
		m_se = g_goMgr->NewGameObject<CSoundSource>();
		m_se->Init(L"Assets/sound/SelectButton.wav");
		m_se->SetVolume(SELECT_SE_VOLUME);
		m_se->Play(false);
	}
	else if (m_buttonState == Button_Start && g_pad[0].IsTrigger(enButtonRight)) {
		//�u�Â���v��I������B
		m_buttonState = Button_Load;
		m_startFont->SetAlpha(FONT_NOT_SELECT);
		m_loadFont->SetAlpha(FONT_SELECT);
		m_se = g_goMgr->NewGameObject<CSoundSource>();
		m_se->Init(L"Assets/sound/SelectButton.wav");
		m_se->SetVolume(SELECT_SE_VOLUME);
		m_se->Play(false);
	}
}
void Title::TitleFadeOut()
{
	//�t�F�[�h�A�E�g�B
	FadeOut* fadeout = g_goMgr->NewGameObject<FadeOut>();
	fadeout->SetSprite(m_spriteRender[0]);
	fadeout = g_goMgr->NewGameObject<FadeOut>();
	fadeout->SetSprite(m_spriteRender[1]);
	fadeout = g_goMgr->NewGameObject<FadeOut>();
	fadeout->SetSprite(m_spriteRender[2]);
	fadeout = g_goMgr->NewGameObject<FadeOut>();
	fadeout->SetSprite(m_spriteRender[3]);

	//�o�����̏��l���t�F�[�h�A�E�g�����那�B
	for (int villain = 4; villain <= 12; villain++) {
		if (m_spriteRender[villain]->GetAlpha() >= VILLAUN_SET_ACTIVE_TRUE) {
			fadeout = g_goMgr->NewGameObject<FadeOut>();
			fadeout->SetSprite(m_spriteRender[villain]);
		}
	}

	m_spriteMul = m_spriteRender[3]->GetMulColor();

	//�t�F�[�h�C�������������̂ŃQ�[���J�n�B
	if (m_spriteMul.x <= FADEOUTO_FINISHED.x && m_spriteMul.y <= FADEOUTO_FINISHED.y && m_spriteMul.z <= FADEOUTO_FINISHED.z)
	{
		g_goMgr->NewGameObject<Game>();
		g_goMgr->DeleteGameObject(this);
	}


}

////////////////////////////////���l�̈ړ�����////////////////////////////////

void Title::ChangeSprite(SpriteRender* m_sprite1, SpriteRender* m_sprite2, float moveX, float moveY)
{
	CVector3 pos1 = m_sprite1->GetPosition();

	m_changeTimer++;

	//Sprite�̐؂�ւ��B
	//2����Sprite���g���ĕ����Ă���悤�Ɍ����܂��B
	if (m_changeTimer == VILLAUN_MOVE_SPRITE1_TIME) {
		pos1.x -= moveX;
		pos1.y += moveY;
		m_sprite1->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_sprite2->SetAlpha(VILLAUN_SET_ACTIVE_TRUE);
	}
	else if (m_changeTimer == VILLAUN_MOVE_SPRITE2_TIME) {
		pos1.x -= moveX * VILLAUN_MUL_VALUE;
		pos1.y += moveY;
		m_sprite1->SetAlpha(VILLAUN_SET_ACTIVE_TRUE);
		m_sprite2->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_changeTimer = VILLAUN_TIMER_RESET;
	}
	//���W�̐ݒ�B
	m_sprite1->SetPosition(pos1);
	m_sprite2->SetPosition(pos1);
}
void Title::SpriteSetAlpha(SpriteRender* m_nextSprite1, SpriteRender* m_nextSprite2, SpriteRender* m_invisible1, SpriteRender* m_invisible2)
{
	//���l��Sptite�����ւ��B
	//�őO��̏��l�̈ʒu������Sprite�ɐݒ�B
	if (m_invisible1->GetPosition().x <= m_invisible2->GetPosition().x)
	{
		m_nextSprite1->SetPosition(m_invisible1->GetPosition());
		m_nextSprite2->SetPosition(m_invisible1->GetPosition());
	}
	else {
		m_nextSprite1->SetPosition(m_invisible2->GetPosition());
		m_nextSprite2->SetPosition(m_invisible2->GetPosition());
	}
	m_nextSprite1->SetAlpha(VILLAUN_SET_ACTIVE_TRUE);
	m_nextSprite2->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
	m_invisible1->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
	m_invisible2->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
}

void Title::VillainSideWays1()
{
	//���ړ�1�B
	ChangeSprite(m_spriteRender[4], m_spriteRender[5], VILLAUN_MOVE_X);

	//���B
	if (m_spriteRender[4]->GetPosition().x <= VILLAUN_FORWARD_LENGTH || m_spriteRender[5]->GetPosition().x <= VILLAUN_FORWARD_LENGTH) {
		SpriteSetAlpha(m_spriteRender[6], m_spriteRender[7], m_spriteRender[4], m_spriteRender[5]);
		m_villainState = Villain_Forward;
	}
}
void Title::VillainForward()
{
	//����ړ��B
	ChangeSprite(m_spriteRender[6], m_spriteRender[7], VILLAUN_MOVE_X, VILLAUN_FORWARD_MOVE_Y);

	//���B

	if (m_spriteRender[6]->GetPosition().x <= VILLAUN_STAY_LENGTH ||
		m_spriteRender[7]->GetPosition().x <= VILLAUN_STAY_LENGTH)
	{
		SpriteSetAlpha(m_spriteRender[8], m_spriteRender[9], m_spriteRender[6], m_spriteRender[7]);
		m_villainState = Villain_Stay;
	}

}
void Title::VillainStay()
{
	//���܂�B
	m_stopTimer++;

	if (m_stopTimer == VILLAUN_CHANGE_TIME) {
		//�X�v���C�g�̐؂�ւ��B
		m_spriteRender[8]->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_spriteRender[9]->SetAlpha(VILLAUN_SET_ACTIVE_TRUE);
	}
	else if (m_stopTimer > VILLAUN_BACK_TIME) {
		//���B
		m_stopTimer = VILLAUN_TIMER_RESET;
		SpriteSetAlpha(m_spriteRender[10], m_spriteRender[11], m_spriteRender[8], m_spriteRender[9]);
		m_villainState = Villain_Back;
	}
}
void Title::VillainBack()
{
	//�E���ړ��B
	ChangeSprite(m_spriteRender[10], m_spriteRender[11], VILLAUN_BACK_MOVE_X, VILLAUN_BACK_MOVE_Y);

	//���B
	if (m_spriteRender[10]->GetPosition().x <= VILLAUN_SIDEWAYS2_LENGTH ||
		m_spriteRender[11]->GetPosition().x <= VILLAUN_SIDEWAYS2_LENGTH) {
		SpriteSetAlpha(m_spriteRender[4], m_spriteRender[5], m_spriteRender[10], m_spriteRender[11]);
		m_villainState = Villain_SideWays2;
	}
}
void Title::VillainSideWays2()
{
	//���ړ�2�B
	ChangeSprite(m_spriteRender[4], m_spriteRender[5], VILLAUN_MOVE_X);

	//���B
	if (m_spriteRender[4]->GetPosition().x <= VILLAUN_STOP_LENGTH ||
		m_spriteRender[5]->GetPosition().x <= VILLAUN_STOP_LENGTH) {
		SpriteSetAlpha(m_spriteRender[8], m_spriteRender[12], m_spriteRender[4], m_spriteRender[5]);
		m_villainState = Villain_Stop;
	}
}
void Title::VillainStop()
{
	//��~�B
	m_stopTimer++;
	if (m_stopTimer == VILLAUN_CHANGE_TIME) {
		m_spriteRender[8]->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_spriteRender[12]->SetAlpha(VILLAUN_SET_ACTIVE_TRUE);
	}
	else if (m_stopTimer > VILLAUN_SIDEWAYS3_TIME) {
		//���B
		m_stopTimer = VILLAUN_TIMER_RESET;
		SpriteSetAlpha(m_spriteRender[4], m_spriteRender[5], m_spriteRender[8], m_spriteRender[12]);
		m_villainState = Villain_SideWays3;

	}

}
void Title::VillainSideWays3()
{
	//���ړ�3�B
	ChangeSprite(m_spriteRender[4], m_spriteRender[5], VILLAUN_MOVE_X);

	//���ړ�1�ցB
	if (m_spriteRender[4]->GetPosition().x <= VILLAUN_RESET_LENGTH ||
		m_spriteRender[5]->GetPosition().x <= VILLAUN_RESET_LENGTH) {
		//������Ԃɖ߂��B
		m_spriteRender[4]->SetAlpha(VILLAUN_SET_ACTIVE_TRUE);
		m_spriteRender[5]->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_spriteRender[4]->SetPosition(VILLAIN1_POSITION);
		m_villainState = Villain_SideWays1;
	}

}

//////////////////////////////////////////////////////////////////////////////

void Title::Update()
{
	switch (m_state)
	{
	case Title::Title_FadeIn:
		TitleFadeIn();			//�t�F�[�h�C���B
		break;
	case Title::Title_GameTitle:
		TitleGameTitle();		//�����̕\���B
		break;
	case Title::Title_Select:
		TitleSelect();			//�{�^���I���B
		break;
	case Title::Title_FadeOut:
		TitleFadeOut();		//�t�F�[�h�A�E�g�B
		break;
	}

	//���l�̈ړ�����
	//���[�v���܂��B
	switch (m_villainState)
	{
	case Title::Villain_SideWays1:
		//���ړ�1�B
		VillainSideWays1();
		break;
	case Title::Villain_Forward:
		//����ړ��B
		VillainForward();
		break;
	case Title::Villain_Stay:
		//���܂�B
		VillainStay();
		break;
	case Title::Villain_Back:
		//�E���ړ��B
		VillainBack();
		break;
	case Title::Villain_SideWays2:
		//���ړ�2�B
		VillainSideWays2();
		break;
	case Title::Villain_Stop:
		//��~�B
		VillainStop();
		break;
	case Title::Villain_SideWays3:
		//���ړ�3�B
		VillainSideWays3();
		break;
	}

}
