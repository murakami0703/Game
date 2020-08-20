#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "FadeIn.h"
#include "FadeOut.h"

Title* Title::m_instance = nullptr;

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////
const CVector2 m_startFontPos = { 250.0f,-250.0f };	//�u�͂��߂�v�̍��W
const CVector2 m_loadFontPos = { 460.0f,-250.0f };		//�u�Â���v�̍��W
const float m_startFontScale = 1.50f;	//�u�͂��߂�v�̍��W

const float m_lightsUpTime = 120.0f;
const float m_lightsOffTime = 240.0f;
const float m_lightAlpha = 0.2f / 120.0f;
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

	//���X
	{
		//0�ԁ�Title(�w�i)
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/title.dds", 1280.0f, 720.0f);
		m_titleSprite->SetMulColor({ 0.0f,0.0f ,0.0f ,1.0f });
		m_spriteRender.push_back(m_titleSprite);

		//1�ԁ�star_chips(����)
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/star_chips.dds", 1280.0f, 720.0f);
		m_titleSprite->SetMulColor({ 0.0f,0.0f ,0.0f ,1.0f });
		m_spriteRender.push_back(m_titleSprite);

		//2�ԁ�light
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/light.dds", 1280.0f, 720.0f);
		m_titleSprite->SetAlpha(0.3f);
		m_titleSprite->SetMulColor({ 0.0f,0.0f ,0.0f ,1.0f });
		m_spriteRender.push_back(m_titleSprite);

		//3�ԁ�Game_title
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/game_title.dds", 650.0f, 150.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetPosition({ 0.0f,280.0f,0.0f });
		m_titleSprite->SetScale({ 0.65f,0.65f,0.65f });
		m_spriteRender.push_back(m_titleSprite);

	}
	//���l
	{
		//4�ԁ�Villain1
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain1.dds", 100.0f, 200.0f);
		m_titleSprite->SetPosition({ 450.0f,-225.0f,0.0f });
		m_titleSprite->SetAlpha(1.0f);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//5�ԁ�Villain2
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain2.dds", 100.0f, 200.0f);
		m_titleSprite->SetPosition({ 450.0f,-225.0f,0.0f });
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//6�ԁ�Villain3
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain3.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//7�ԁ�Villain4
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain4.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//8�ԁ�Villain5
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain5.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//9�ԁ�Villain6
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain6.dds", 120.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//10�ԁ�Villain7
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain7.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//11�ԁ�Villain8
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain8.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//12�ԁ�Villain9
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain9.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.5f,0.5f,0.5f });
		m_spriteRender.push_back(m_titleSprite);
	}
	//�t�H���g
	{
		//�͂��߂�
		m_startFont = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* start = L"Start";
		m_startFont->SetText(start);
		m_startFont->SetAlpha(0.0);
		m_startFont->SetPosition(m_startFontPos);
		m_startFont->SetScale(m_startFontScale);
		//��������
		m_loadFont = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* load = L"Load";
		m_loadFont->SetText(load);
		m_loadFont->SetScale(m_startFontScale);
		m_loadFont->SetAlpha(0.0);
		m_loadFont->SetPosition(m_loadFontPos);
	}
	

	m_titleBgm = g_goMgr->NewGameObject<CSoundSource>();
	m_titleBgm->Init(L"Assets/sound/TitleBGM.wav");

	
	return true;
}

void Title::LightFlashing()
{
	//���C�g�̓_��
	m_flashingTimer++;
	if (m_flashingTimer <= m_lightsUpTime) {
		m_spriteRender[2]->DeltaAlpha(m_lightAlpha);
	}
	else if (m_flashingTimer <= m_lightsOffTime)
	{
		m_spriteRender[2]->DeltaAlpha(-m_lightAlpha);
	}
	else {
		m_flashingTimer = 0.0f;
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
	if (count == 30) {
		pos1.x -= moveX;
		m_sprite1->SetAlpha(0.0f);
		m_sprite2->SetAlpha(1.0f);
	}
	else if (count == 60) {
		pos1.x -= moveX*2;
		m_sprite1->SetAlpha(1.0f);
		m_sprite2->SetAlpha(0.0f);
		count = 0;
	}
	m_sprite1->SetPosition(pos1);
	m_sprite2->SetPosition(pos1);
}
void Title::VillainSideWays1()
{
	//���ړ�1�B
	ChangeSprite(m_spriteRender[4], m_spriteRender[5],5.0f);
}
void Title::VillainForward()
{
	//����ړ��B
}
void Title::VillainStay()
{
	//���܂�B
}
void Title::VillainBack()
{
	//�E���ړ��B
}
void Title::VillainSideWays2()
{
	//���ړ�2�B
}
void Title::VillainStop()
{
	//��~�B
}
void Title::VillainSideWays3()
{
	//���ړ�3�B
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
		break;
	case Title::Villain_Stay:
		break;
	case Title::Villain_Back:
		break;
	case Title::Villain_SideWays2:
		break;
	case Title::Villain_Stop:
		break;
	case Title::Villain_SideWays3:
		break;
	}
}
