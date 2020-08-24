#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "FadeIn.h"
#include "FadeOut.h"

Title* Title::m_instance = nullptr;

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const CVector4 TITLE_SET_MULCOLOR = { 0.0f,0.0f ,0.0f ,1.0f };	//初期乗算カラーの設定。
const float LIGHT_SET_ALPHA = 0.3f;								//ライトの初期透明度。
const float TITLENAME_SET_ALPHA = 0.0f;							//ゲーム名の初期透明度。
const CVector3 TITLENAME_SET_POSITION = { 0.0f,280.0f,0.0f };	//ゲーム名の座標。
const CVector3 TITLENAME_SET_SCALE = { 0.65f,0.65f,0.65f };		//ゲーム名の拡大率。

const CVector3 VILLAIN_SCALE = { 0.6f,0.6f,0.6f };				//小人の拡大率。
const float VILLAUN_SET_ACTIVE_TRUE = 1.0f;						//小人に設定する透明度(表示)。
const float VILLAUN_SET_ACTIVE_FALSE = 0.0f;					//小人に設定する透明度(非表示)。

const float FONT_SET_ALPHA = 0.0f;								//フォントの初期透明度。
const CVector2 FONT_START_SET_POSITION = { 250.0f,-250.0f };	//「はじめる」の座標。
const CVector2 FONT_LOAD_SET_POSITION = { 460.0f,-250.0f };		//「つづける」の座標。
const float FONT_SET_SCALE = 1.5f;								//フォントの拡大率。

const float LIGHT_INCREASE_TIME = 120.0f;					//ライトの明るさを増加させる時間。
const float LIGHT_DECREASE_TIME = 240.0f;					//ライトの明るさを減少させる時間。
const float LIGHT_DELTA_ALPHA = 0.7f/ 120.0f;				//変位させる透明度の値。
const float LIGHT_TIMER_RESET = 0.0f;						//ライトのタイマーを初期状態にする。

const CVector4 FADEIN_FINISHED = { 1.0f,1.0f,1.0f,1.0f };	//フェードインが終わる値。
const CVector4 FADEOUTO_FINISHED = { 0.0f,0.0f,0.0f,1.0f };	//フェードアウトが終わる値。

const float TITLENAME_FADE_TIME = 30.0f;					//タイトル名をフェードさせる時間。
const float TITLENAME_FADE_FONT_TIME = 50.0f;				//フォントをフェードさせる時間。
const float TITLENAME_FADE_DELTA_ALPHA = 1.0f / 30.0f;		//タイトル名の透明度を変位させる値。
const float STARTFONT_FADE_DELTA_ALPHA = 1.0f / 20.0f;		//「はじめる」の透明度を変位させる値。
const float LOADFONT_FADE_DELTA_ALPHA = 0.3f / 20.0f;		//「つづける」の透明度を変位させる値。

const float FONT_SELECT = 1.0f;								//選択中のフォント。
const float FONT_NOT_SELECT = 0.3f;							//選択外のフォント。
const float DECIDED_SE_VOLUME = 0.5f;						//決定したとき流れるSEのボリューム。
const float SELECT_SE_VOLUME = 0.1f;						//選択変更したとき流れるSEのボリューム。


const int VILLAUN_MOVE_SPRITE1_TIME = 15;					//1枚目のSpriteを移動&切り替える時間。
const int VILLAUN_MOVE_SPRITE2_TIME = 30;					//2枚目のSpriteを移動&切り替える時間。

Title::Title(){}

Title::~Title()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		g_goMgr->DeleteGameObject(m_spriteRender[i]);
	}
	//フォント
	g_goMgr->DeleteGameObject(m_startFont);
	g_goMgr->DeleteGameObject(m_loadFont);
	g_goMgr->DeleteGameObject(m_titleBgm);

}

bool Title::Start()
{
	m_instance = this;

	//諸々。
	{
		//0番→Title(背景)
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/title.dds", 1280.0f, 720.0f);
		m_titleSprite->SetMulColor(TITLE_SET_MULCOLOR);
		m_spriteRender.push_back(m_titleSprite);

		//1番→star_chips(星屑)
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/star_chips.dds", 1280.0f, 720.0f);
		m_titleSprite->SetMulColor(TITLE_SET_MULCOLOR);
		m_spriteRender.push_back(m_titleSprite);

		//2番→light
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/light.dds", 1280.0f, 720.0f);
		m_titleSprite->SetAlpha(LIGHT_SET_ALPHA);
		m_titleSprite->SetMulColor(TITLE_SET_MULCOLOR);
		m_spriteRender.push_back(m_titleSprite);

		//3番→Game_title
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/game_title.dds", 650.0f, 150.0f);
		m_titleSprite->SetAlpha(TITLENAME_SET_ALPHA);
		m_titleSprite->SetPosition(TITLENAME_SET_POSITION);
		m_titleSprite->SetScale(TITLENAME_SET_SCALE);
		m_spriteRender.push_back(m_titleSprite);

	}
	//小人。
	{
		//4番→Villain1
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain1.dds", 100.0f, 200.0f);
		m_titleSprite->SetPosition({ 700.0f,-225.0f,0.0f });
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_TRUE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//5番→Villain2
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain2.dds", 100.0f, 200.0f);
		m_titleSprite->SetPosition({ 450.0f,-225.0f,0.0f });
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//6番→Villain3
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain3.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//7番→Villain4
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain4.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//8番→Villain5
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain5.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//9番→Villain6
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain6.dds", 120.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//10番→Villain7
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain7.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//11番→Villain8
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain8.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);

		//12番→Villain9
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain9.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(VILLAUN_SET_ACTIVE_FALSE);
		m_titleSprite->SetScale(VILLAIN_SCALE);
		m_spriteRender.push_back(m_titleSprite);
	}
	//フォント。
	{
		//はじめる
		m_startFont = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* m_start = L"Start";
		m_startFont->SetText(m_start);
		m_startFont->SetAlpha(FONT_SET_ALPHA);
		m_startFont->SetPosition(FONT_START_SET_POSITION);
		m_startFont->SetScale(FONT_SET_SCALE);
		//続きから
		m_loadFont = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* m_load = L"Load";
		m_loadFont->SetText(m_load);
		m_loadFont->SetAlpha(FONT_SET_ALPHA);
		m_loadFont->SetPosition(FONT_LOAD_SET_POSITION);
		m_loadFont->SetScale(FONT_SET_SCALE);

	}
	
	//音。
	m_titleBgm = g_goMgr->NewGameObject<CSoundSource>();
	m_titleBgm->Init(L"Assets/sound/TitleBGM.wav");

	return true;
}
void Title::LightFlashing()
{
	//ライトの点滅
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
	//フェードイン。
	FadeIn* fadein = g_goMgr->NewGameObject<FadeIn>();
	fadein->SetSprite(m_spriteRender[0]);
	fadein = g_goMgr->NewGameObject<FadeIn>();
	fadein->SetSprite(m_spriteRender[1]);
	fadein = g_goMgr->NewGameObject<FadeIn>();
	fadein->SetSprite(m_spriteRender[2]);

	m_spriteMul = m_spriteRender[2]->GetMulColor();	

	//フェードインが完了したので次へ。
	if (m_spriteMul.x >= FADEIN_FINISHED.x && m_spriteMul.y >= FADEIN_FINISHED.y && m_spriteMul.z >= FADEIN_FINISHED.z)
	{
		//BGMの再生
		m_titleBgm->Play(true);
		m_state = Title_GameTitle;
	}
}
void Title::TitleGameTitle()
{
	//文字の表示。
	//タイトルの後に選択ボタンを表示させます。
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
	//ライトの点滅。
	LightFlashing();

	//ボタン選択。
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
		//「はじめる」を選択する。
		m_buttonState = Button_Start;
		m_startFont->SetAlpha(FONT_SELECT);
		m_loadFont->SetAlpha(FONT_NOT_SELECT);
		m_se = g_goMgr->NewGameObject<CSoundSource>();
		m_se->Init(L"Assets/sound/SelectButton.wav");
		m_se->SetVolume(SELECT_SE_VOLUME);
		m_se->Play(false);
	}
	else if (m_buttonState == Button_Start && g_pad[0].IsTrigger(enButtonRight)) {
		//「つづける」を選択する。
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
	//フェードアウト。
	FadeOut* fadeout = g_goMgr->NewGameObject<FadeOut>();
	fadeout->SetSprite(m_spriteRender[0]);
	fadeout = g_goMgr->NewGameObject<FadeOut>();
	fadeout->SetSprite(m_spriteRender[1]);
	fadeout = g_goMgr->NewGameObject<FadeOut>();
	fadeout->SetSprite(m_spriteRender[2]);
	fadeout = g_goMgr->NewGameObject<FadeOut>();
	fadeout->SetSprite(m_spriteRender[3]);

	m_spriteMul = m_spriteRender[3]->GetMulColor();

	//フェードインが完了したのでゲーム開始。
	if (m_spriteMul.x <= FADEOUTO_FINISHED.x && m_spriteMul.y <= FADEOUTO_FINISHED.y && m_spriteMul.z <= FADEOUTO_FINISHED.z)
	{
		g_goMgr->NewGameObject<Game>();
		g_goMgr->DeleteGameObject(this);
	}


}

////////////////////////////////小人の移動処理////////////////////////////////

void Title::ChangeSprite(SpriteRender* m_sprite1, SpriteRender* m_sprite2, float moveX, float moveY)
{
	CVector3 pos1 = m_sprite1->GetPosition();

	count++;
	//スプライトの切り替え。
	//歩いているように見せます。
	if (count == VILLAUN_MOVE_SPRITE1_TIME) {
		pos1.x -= moveX;
		pos1.y += moveY;
		m_sprite1->SetAlpha(0.0f);
		m_sprite2->SetAlpha(1.0f);
	}
	else if (count == VILLAUN_MOVE_SPRITE2_TIME) {
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
	//横移動1。
	ChangeSprite(m_spriteRender[4], m_spriteRender[5],5.0f);

	//次。
	if (m_spriteRender[4]->GetPosition().x <= 300.0f||
		m_spriteRender[5]->GetPosition().x <= 300.0f) {
		SpriteSetAlpha(m_spriteRender[6],m_spriteRender[4], m_spriteRender[5]);
		m_villainState = Villain_Forward;
	}
}
void Title::VillainForward()
{
	//左上移動。
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
	//留まる。
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
	//右下移動。
	ChangeSprite(m_spriteRender[10], m_spriteRender[11], 2.5f, -1.0f);

	if (m_spriteRender[10]->GetPosition().x <= 50.0f ||
		m_spriteRender[11]->GetPosition().x <= 50.0f) {
		SpriteSetAlpha(m_spriteRender[4], m_spriteRender[10], m_spriteRender[11]);
		m_villainState = Villain_SideWays2;
	}

}
void Title::VillainSideWays2()
{
	//横移動2。
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
	//停止。
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
	//横移動3。
	ChangeSprite(m_spriteRender[4], m_spriteRender[5], 5.0f);

	if (m_spriteRender[4]->GetPosition().x <= -750.0f ||
		m_spriteRender[5]->GetPosition().x <= -750.0f) {
		m_spriteRender[4]->SetAlpha(1.0f);
		m_spriteRender[5]->SetAlpha(0.0f);
		m_spriteRender[4]->SetPosition({ 700.0f,-225.0f,0.0f });

		m_villainState = Villain_SideWays1;
	}

}

//////////////////////////////////////////////////////////////////////////////

void Title::Update()
{
	switch (m_state)
	{
	case Title::Title_FadeIn:
		TitleFadeIn();			//フェードイン。
		break;
	case Title::Title_GameTitle:
		TitleGameTitle();		//文字の表示。
		break;
	case Title::Title_Select:
		TitleSelect();			//ボタン選択。
		break;
	case Title::Title_FadeOut:
		TitleFadeOut();		//フェードアウト。
		break;
	}

	switch (m_villainState)
	{
	case Title::Villain_SideWays1:
		//横移動1。
		VillainSideWays1();
		break;
	case Title::Villain_Forward:
		//左上移動。
		VillainForward();
		break;
	case Title::Villain_Stay:
		//留まる。
		VillainStay();
		break;
	case Title::Villain_Back:
		//右下移動。
		VillainBack();
		break;
	case Title::Villain_SideWays2:
		//横移動2。
		VillainSideWays2();
		break;
	case Title::Villain_Stop:
		//停止。
		VillainStop();
		break;
	case Title::Villain_SideWays3:
		//横移動3。
		VillainSideWays3();
		break;
	}

}
