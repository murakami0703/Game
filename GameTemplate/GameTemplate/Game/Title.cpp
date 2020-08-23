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

const float LIGHT_TIMER_RESET = 0.0f;						//���C�g�̃^�C�}�[��������Ԃɂ���B

const float TITLENAME_FADEE_IN = 1.0f / 30.0f;
const float STARTFONT_FADEE_IN = 1.0f / 20.0f;
const float LOADFONT_FADEE_IN = 0.3f / 20.0f;

const CVector4 a = { 1.0f,1.0f ,1.0f ,1.0f };		//�u�Â���v�̍��W
const CVector3 VILLAIN_SCALE = { 0.6f,0.6f,0.6f };		//�u�Â���v�̍��W

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
		m_titleSprite->SetPosition({ 700.0f,-225.0f,0.0f });
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_TRUE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//5�ԁ�Villain2
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain2.dds", 100.0f, 200.0f);
		m_titleSprite->SetPosition({ 450.0f,-225.0f,0.0f });
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

	if (m_spriteRender[2]->GetMulColor().x >= 1.0f &&
		m_spriteRender[2]->GetMulColor().y >= 1.0f &&
		m_spriteRender[2]->GetMulColor().z >= 1.0f ) 
	{
		m_state = Title_GameTitle;
		m_titleBgm->Play(true);

	}
}
void Title::TitleGameTitle()
{
	//�����̕\���B
	//�^�C�g���̌�ɑI���{�^����\�������܂��B
	m_fontTimer++;
	if (m_fontTimer <= 30) {
		m_spriteRender[3]->DeltaAlpha(TITLENAME_FADEE_IN);
	}
	else if (m_fontTimer > 30 && m_fontTimer <= 50) {
		m_startFont->DeltaAlpha(STARTFONT_FADEE_IN);
		m_loadFont->DeltaAlpha(LOADFONT_FADEE_IN);
	}
	else if (m_fontTimer > 50) {
		m_state = Title_Select;
	}

}
void Title::TitleSelect()
{
	LightFlashing();

	//�{�^���I���B
	if (g_pad[0].IsTrigger(enButtonStart)) {
		m_startFont->SetAlpha(0.0f);
		m_loadFont->SetAlpha(0.0f);
		m_se = g_goMgr->NewGameObject<CSoundSource>();
		m_se->Init(L"Assets/sound/Decision.wav");
		m_se->SetVolume(0.5f);
		m_se->Play(false);
		m_state = Title_FadeOut;
	}
	else if (m_buttonState == Button_Load && g_pad[0].IsTrigger(enButtonLeft)) {
		m_buttonState = Button_Start;
		m_startFont->SetAlpha(1.0f);
		m_loadFont->SetAlpha(0.3f);
		m_se = g_goMgr->NewGameObject<CSoundSource>();
		m_se->Init(L"Assets/sound/SelectButton.wav");
		m_se->SetVolume(0.1f);
		m_se->Play(false);
	}
	else if (m_buttonState == Button_Start && g_pad[0].IsTrigger(enButtonRight)) {
		m_buttonState = Button_Load;
		m_startFont->SetAlpha(0.3f);
		m_loadFont->SetAlpha(1.0f);
		m_se = g_goMgr->NewGameObject<CSoundSource>();
		m_se->Init(L"Assets/sound/SelectButton.wav");
		m_se->SetVolume(0.1f);
		m_se->Play(false);
	}


}
void Title::TitleFadeOut()
{
	//�t�F�[�h�A�E�g�B
		//�t�F�[�h�C���B
	FadeOut* fadeout = g_goMgr->NewGameObject<FadeOut>();
	fadeout->SetSprite(m_spriteRender[0]);
	fadeout = g_goMgr->NewGameObject<FadeOut>();
	fadeout->SetSprite(m_spriteRender[1]);
	fadeout = g_goMgr->NewGameObject<FadeOut>();
	fadeout->SetSprite(m_spriteRender[2]);
	fadeout = g_goMgr->NewGameObject<FadeOut>();
	fadeout->SetSprite(m_spriteRender[3]);

	if (m_spriteRender[3]->GetMulColor().x <= 0.0f &&
		m_spriteRender[3]->GetMulColor().y <= 0.0f &&
		m_spriteRender[3]->GetMulColor().z <= 0.0f)
	{
		g_goMgr->NewGameObject<Game>();
		g_goMgr->DeleteGameObject(this);
	}


}

void Title::ChangeSprite(SpriteRender* m_sprite1, SpriteRender* m_sprite2, float moveX, float moveY)
{
	CVector3 pos1 = m_sprite1->GetPosition();
	CVector3 pos2 = m_sprite2->GetPosition();

	count++;
	//�X�v���C�g�̐؂�ւ��B
	//�����Ă���悤�Ɍ����܂��B
	if (count == 15) {
		pos1.x -= moveX;
		pos1.y += moveY;
		m_sprite1->SetAlpha(0.0f);
		m_sprite2->SetAlpha(1.0f);
	}
	else if (count == 30) {
		pos1.x -= moveX*2;
		pos1.y += moveY;
		m_sprite1->SetAlpha(1.0f);
		m_sprite2->SetAlpha(0.0f);
		count = 0;
	}
	m_sprite1->SetPosition(pos1);
	m_sprite2->SetPosition(pos1);
}
void Title::SpriteSetAlpha(SpriteRender* m_nextSprite, SpriteRender* m_invisible1, SpriteRender* m_invisible2)
{
	if (m_invisible1->GetPosition().x <= m_invisible2->GetPosition().x)
	{
		m_nextSprite->SetPosition(m_invisible1->GetPosition());
	}
	else {
		m_nextSprite->SetPosition(m_invisible2->GetPosition());

	}
	m_nextSprite->SetAlpha(1.0f);
	m_invisible1->SetAlpha(0.0f);
	m_invisible2->SetAlpha(0.0f);
}

void Title::VillainSideWays1()
{
	//���ړ�1�B
	ChangeSprite(m_spriteRender[4], m_spriteRender[5],5.0f);

	//���B
	if (m_spriteRender[4]->GetPosition().x <= 300.0f||
		m_spriteRender[5]->GetPosition().x <= 300.0f) {
		SpriteSetAlpha(m_spriteRender[6],m_spriteRender[4], m_spriteRender[5]);
		m_villainState = Villain_Forward;
	}
}
void Title::VillainForward()
{
	//����ړ��B
	ChangeSprite(m_spriteRender[6], m_spriteRender[7], 5.0f, 1.0f);

	if (m_spriteRender[6]->GetPosition().x <= 150.0f ||
		m_spriteRender[7]->GetPosition().x <= 150.0f) {
		SpriteSetAlpha(m_spriteRender[8], m_spriteRender[6], m_spriteRender[7]);
		m_spriteRender[9]->SetPosition(m_spriteRender[8]->GetPosition());
		m_villainState = Villain_Stay;
	}

}
void Title::VillainStay()
{
	//���܂�B
	m_stopTimer++;
	if (m_stopTimer == 10) {
		m_spriteRender[8]->SetAlpha(0.0f);
		m_spriteRender[9]->SetAlpha(1.0f);
	}
	else if (m_stopTimer > 480) {
		m_stopTimer = 0;
		SpriteSetAlpha(m_spriteRender[10], m_spriteRender[8], m_spriteRender[9]);
		m_villainState = Villain_Back;

	}
}
void Title::VillainBack()
{
	//�E���ړ��B
	ChangeSprite(m_spriteRender[10], m_spriteRender[11], 2.5f, -1.0f);

	if (m_spriteRender[10]->GetPosition().x <= 50.0f ||
		m_spriteRender[11]->GetPosition().x <= 50.0f) {
		SpriteSetAlpha(m_spriteRender[4], m_spriteRender[10], m_spriteRender[11]);
		m_villainState = Villain_SideWays2;
	}

}
void Title::VillainSideWays2()
{
	//���ړ�2�B
	ChangeSprite(m_spriteRender[4], m_spriteRender[5], 5.0f);

	if (m_spriteRender[4]->GetPosition().x <= -450.0f ||
		m_spriteRender[5]->GetPosition().x <= -450.0f) {
		SpriteSetAlpha(m_spriteRender[8], m_spriteRender[4], m_spriteRender[5]);
		m_spriteRender[12]->SetPosition(m_spriteRender[8]->GetPosition());

		m_villainState = Villain_Stop;
	}
}
void Title::VillainStop()
{
	//��~�B
	m_stopTimer++;
	if (m_stopTimer == 10) {
		m_spriteRender[8]->SetAlpha(0.0f);
		m_spriteRender[12]->SetAlpha(1.0f);
	}
	else if (m_stopTimer > 60) {
		m_stopTimer = 0;
		SpriteSetAlpha(m_spriteRender[4], m_spriteRender[8], m_spriteRender[12]);
		m_villainState = Villain_SideWays3;

	}

}
void Title::VillainSideWays3()
{
	//���ړ�3�B
	ChangeSprite(m_spriteRender[4], m_spriteRender[5], 5.0f);

	if (m_spriteRender[4]->GetPosition().x <= -750.0f ||
		m_spriteRender[5]->GetPosition().x <= -750.0f) {
		m_spriteRender[4]->SetAlpha(1.0f);
		m_spriteRender[5]->SetAlpha(0.0f);
		m_spriteRender[4]->SetPosition({ 700.0f,-225.0f,0.0f });

		m_villainState = Villain_SideWays1;
	}

}
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
