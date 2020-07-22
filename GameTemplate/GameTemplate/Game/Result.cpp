#include "stdafx.h"
#include "Result.h"
#include "Gamedata.h"

Result* Result::m_instance = nullptr;

Result::Result()
{
	if (m_instance != nullptr) {
			std::abort();//���łɏo�Ă��邽�߃N���b�V��
		}
	m_instance = this;

	//�w�i�œ�����texture
	{
		//0�ԁ�Result_Backgraund1
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Backgraund.dds", 1280.0f, 720.0f);
		m_itemSprite->SetAlpha(m_backTexAlpha);
		m_spriteRender.push_back(m_itemSprite);
		//1�ԁ�Result_Backgraund2
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Backgraund.dds", 1280.0f, 720.0f);
		m_itemSprite->SetPosition({ m_backTexXPos,0.0f,0.0f });
		m_itemSprite->SetAlpha(m_backTexAlpha);
		m_spriteRender.push_back(m_itemSprite);
	}
	
	//2�ԁ����U���g�̑��
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/Result_Frame.dds", 1280, 720.0f);
	m_itemSprite->SetPosition(m_bgStartPos);
	m_itemSprite->SetAlpha(m_startAlpha);
	m_spriteRender.push_back(m_itemSprite);

	//���U���g����
	{
		//3�ԁ�R
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_R.dds", 300.0f, 100.0f);
		m_itemSprite->SetPosition(m_resultFontPos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

		//4�ԁ�e
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_e.dds", 300.0f, 100.0f);
		m_itemSprite->SetPosition(m_resultFontPos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

		//5�ԁ�s
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_s.dds", 300.0f, 100.0f);
		m_itemSprite->SetPosition(m_resultFontPos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

		//6�ԁ�u
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_u.dds", 300.0f, 100.0f);
		m_itemSprite->SetPosition(m_resultFontPos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

		//7�ԁ�l
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_l.dds", 300.0f, 100.0f);
		m_itemSprite->SetPosition(m_resultFontPos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

		//8�ԁ�t
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_t.dds", 300.0f, 100.0f);
		m_itemSprite->SetPosition(m_resultFontPos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);
	}

	//��ɕ\��������g�Ȃ�
	{
		//9�ԁ��_��
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_DotLine.dds", 650.0f, 25.0f);
		m_itemSprite->SetPosition(m_dotLinePos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

		//10�ԁ����p�g
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Soulframe.dds", 450.0f, 175.0f);
		m_itemSprite->SetPosition(m_soulFramePos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

		//11�ԁ��A�C�e���p�g
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Frame2.dds", 650.0f, 125.0f);
		m_itemSprite->SetPosition(m_itemFramePos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);
	}

	//������
	{
		//12�ԁ���
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/soul.dds", 400.0f, 400.0f);
		m_itemSprite->SetPosScale(m_soulPos, m_soulScale);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

		//13�ԁ����t�H���g
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Font3.dds", 100.0f, 25.0f);
		m_itemSprite->SetPosition(m_soulFontPos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

	}
	
	//�A�C�e������\��
	{
		//14�ԁ�ItemGet�t�H���g
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Font1.dds", 175.0f, 50.0f);
		m_itemSprite->SetPosition(m_itemFontPos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

		//�A�C�e������@�@������123...
		//15�ԁ����1
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_ItemFrame.dds", 150.0f, 150.0f);
		m_itemSprite->SetPosScale(m_itemTablePos1, {0.0f,0.0f,0.0f});
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

		//16�ԁ����2
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_ItemFrame.dds", 150.0f, 150.0f);
		m_itemSprite->SetPosScale(m_itemTablePos2, { 0.0f,0.0f,0.0f });
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

		//17�ԁ����3
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_ItemFrame.dds", 150.0f, 150.0f);
		m_itemSprite->SetPosScale(m_itemTablePos3, { 0.0f,0.0f,0.0f });
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);

		//18�ԁ����4
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_ItemFrame.dds", 150.0f, 150.0f);
		m_itemSprite->SetPosScale(m_itemTablePos4, { 0.0f,0.0f,0.0f });
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);
	}

	//Next����
	{
		//19�ԁ�Next�t�H���g
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Font2.dds", 150.0f, 50.0f);
		m_itemSprite->SetPosition(m_nextFontPos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);
		//20�ԁ��O�p
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Triangle.dds", 50.0f, 50.0f);
		m_itemSprite->SetPosition(m_trianglePos);
		m_itemSprite->SetAlpha(m_startAlpha);
		m_spriteRender.push_back(m_itemSprite);
	}

	//21�ԁ��v���C���[�C���X�g
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/Player_Illustration.dds", 1690.0f, 3142.0f);
	m_itemSprite->SetPosition(m_nextFontPos);
	m_itemSprite->SetAlpha(m_startAlpha);
	m_spriteRender.push_back(m_itemSprite);

	//�t�H���g
	{
		//�X�e�[�W��
		m_stageNameFont = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* str = L"Stage1";
		m_stageNameFont->SetText(str);
		m_stageNameFont->SetPosition({ 650.0f,225.0f });
		m_stageNameFont->SetPivot({ 0.0f,0.0f });
		//���̐�
		m_soulNumFont = g_goMgr->NewGameObject<FontRender>();
	}
}
Result::~Result()
{
	m_instance = nullptr;

}
void Result::BackMove()
{
	//�w�i(�_�}�X�N��)�𓮂���
	m_backTexpos1 = m_spriteRender[0]->GetPosition();
	m_backTexpos2 = m_spriteRender[1]->GetPosition();

	m_backTexpos1.x += m_backMove;
	m_backTexpos2.x += m_backMove;

	//���ʒu�ɂȂ�ƈꖇ�ڂ̉E�[�Ɉړ�������B
	//�w�i��Texture���r�؂�Ȃ���I�I
	if (m_backTexpos1.x <= -m_backTexXPos) {
		m_backTexpos1.x = m_backTexXPos;
	}
	else if (m_backTexpos2.x <= -m_backTexXPos) {
		m_backTexpos2.x = m_backTexXPos;
	}

	m_spriteRender[0]->SetPosition(m_backTexpos1);
	m_spriteRender[1]->SetPosition(m_backTexpos2);
	
}
void Result::SpriteMove(SpriteRender* m_sprite)
{
	//Sprite���~����
	CVector3 m_position = m_sprite->GetPosition();	
	if (m_position.y > m_resultFontYPos) {
			m_position.y += m_fallMoveSpeed;

	}
	m_sprite->SetAlpha(1.0f);
	m_sprite->SetPosition(m_position);
}
void Result::SpriteIndicate(SpriteRender* m_sprite)
{
	//�X�v���C�g�̕\������
	float m_alpha = m_sprite->GetAlpha();
	if (m_alpha < 1.0f) {
		m_alpha += m_Indicate;

	}
	m_sprite->SetAlpha(m_alpha);

}
void Result::SpriteScaleUp(SpriteRender* m_sprite)
{
	//�X�v���C�g�̊g��\�������B
	CVector3 m_scale = m_sprite->GetScale();
	float m_alpha = m_sprite->GetAlpha();

	if (m_scale.x < 1.0f && m_scale.y < 1.0f && m_scale.z < 1.0f) {
		m_scale.x += m_Indicate;
		m_scale.y += m_Indicate;
		m_scale.z += m_Indicate;

		if (m_alpha < 1.0f) {
			m_alpha += m_Indicate;

		}

	}
	m_sprite->SetAlpha(m_alpha);
	m_sprite->SetScale(m_scale);


}

void Result::BackTable()
{
	//���U���g�����\���B
	//�E����\��������B
	CVector3 m_position = m_spriteRender[2]->GetPosition();	//���W�B

	if (m_position.x > 0.0f && bound == false) {
		m_position.x -= m_tableSpeed;
	}
	else {
		bound = true;
		//��������o�E���h����
		if (bound == true && m_position.x < m_boundStopXPos) {
			m_position.x += m_boundSpeed;
		}
		else {
			//�o�E���h�I���A���̏�����...�B
			bound = false;
			m_state = Result_FallMove;
		}

	}
	m_spriteRender[2]->SetAlpha(1.0f);
	m_spriteRender[2]->SetPosition(m_position);

}
void Result::FallMove()
{
	//Result�t�H���g��\���B
	m_timer++;
	//���ԍ���Result�����\��
	if (m_timer >= m_timeLag[0]) {
		SpriteMove(m_spriteRender[3]);
	}
	if (m_timer >= m_timeLag[1]) {
		SpriteMove(m_spriteRender[4]);
	}
	if (m_timer >= m_timeLag[2]) {
		SpriteMove(m_spriteRender[5]);
	}
	if (m_timer >= m_timeLag[3]) {
		SpriteMove(m_spriteRender[6]);
	}
	if (m_timer >= m_timeLag[4]) {
		SpriteMove(m_spriteRender[7]);
	}
	if (m_timer >= m_timeLag[5]) {
		SpriteMove(m_spriteRender[8]);
	}

	//�\�������A���̏�����...�B
	if (m_timer >= m_timeLag[6]) {
		m_timer = 0;
		m_state = Result_Frame;
	}


}
void Result::Frame()
{
	//�t���[���̕\���B
	SpriteIndicate(m_spriteRender[9]);
	SpriteIndicate(m_spriteRender[10]);
	SpriteIndicate(m_spriteRender[11]);
	
	//�\�������A���̏�����...�B
	if (m_spriteRender[11]->GetAlpha() >= 1.0f) {
		m_state = Result_StageName;
	}

}
void Result::StageName()
{
	//�Q�[���X�e�[�W���̕\���B
	CVector2 m_position = m_stageNameFont->GetPosition();
	//���ʒu�Ȃ�A���̏�����...�B
	if (m_position.x <= m_nameStopXPos) {
		m_state = Result_GetSoul;

	}
	m_position.x -= m_nameSpeed;
	m_stageNameFont->SetPosition(m_position);
}
void Result::GetSoul()
{
	//�l�����̕\���B
	SpriteIndicate(m_spriteRender[12]);
	SpriteIndicate(m_spriteRender[13]);

	//�\�������A���̏�����...�B
	if (m_spriteRender[13]->GetAlpha() >= 1.0f) {
		m_state = Result_SoulNumber;
	}

}
void Result::SoulNumber()
{
	//�l�����̐��B

	//�Q�[���f�[�^������������Ă���
	GameData* m_gamedate = GameData::GetInstance();
	//�Q�[���f�[�^�̒l�܂ŉ��Z
	m_soulNumber++;
	if (m_soulNumber <= m_gamedate->GetAnima()) {
		wchar_t text[256];
		swprintf(text, L"%d", m_soulNumber);
		m_soulNumFont->SetText(text);
		m_soulNumFont->SetPosition(m_soulNumPos);
		m_soulNumFont->SetColor(m_soulNumColor);
		m_soulNumFont->SetScale(m_soulNumScale);
	}
	else {
		//���Z�I��
		//��������o�E���h����
		CVector2 m_position = m_soulNumFont->GetPosition();	

		if (bound == true && m_position.y <= m_soulNumStopYPos) {
			//�o�E���h�I���A���̏�����...�B
			bound = false;
			m_state = Result_GetItem;
		}
		else if (bound == false && m_position.y < m_soulNumYPos) {
			//�㏸
			m_position.y += m_soulNumSpeed;
		}
		else if (bound == true || m_position.y >= m_soulNumYPos) {
			//���~
			bound = true;
			m_position.y -= m_soulNumSpeed;
		}
		m_soulNumFont->SetPosition(m_position);
	}
}
void Result::GetItem()
{
	//�l���A�C�e������̕\���B
	SpriteIndicate(m_spriteRender[14]);		//ItemGet��Sprite

	m_timer++;
	//���ԍ��ŃA�C�e������\��
	if (m_timer >= m_itemtimeLag[0]) {
		SpriteScaleUp(m_spriteRender[15]);
	}
	if (m_timer >= m_itemtimeLag[1]) {
		SpriteScaleUp(m_spriteRender[16]);
	}
	if (m_timer >= m_itemtimeLag[2]) {
		SpriteScaleUp(m_spriteRender[17]);
	}
	if (m_timer >= m_itemtimeLag[3]) {
		SpriteScaleUp(m_spriteRender[18]);
	}

	//�\�������A���̏�����...�B
	if (m_timer >= m_itemtimeLag[4]) {
		m_timer = 0;
		m_state = Result_Next;
	}

}
void Result::Next()
{
	//Next�̕\���B
	SpriteIndicate(m_spriteRender[19]);
	SpriteIndicate(m_spriteRender[20]);

	//���E�ɓ�������
	CVector3 m_position = m_spriteRender[20]->GetPosition();

	if (bound == true && m_position.x <= m_triangleStopXPos) {
		bound = false;
	}
	else if (bound == false && m_position.x < m_triangleXPos) {
		m_position.x += m_triangleSpeed;

	}
	else if (bound == true || m_position.x >= m_triangleXPos) {
		bound = true;
		m_position.x -= m_triangleSpeed;
	}
	m_spriteRender[20]->SetPosition(m_position);

	//�\��������A�{�^���������ꂽ��A���̏�����...�B
	if (m_spriteRender[20]->GetAlpha() >= 1.0f && g_pad[0].IsTrigger(enButtonA)) {
		m_state = Result_Removal;
	}

}
void Result::Removal()
{
	//��U���U���g�Ɠ_���ȊO�r���B
	//�����x���������Ă䂭��
	SpriteIndicate(m_spriteRender[10]);
	SpriteIndicate(m_spriteRender[11]);
	SpriteIndicate(m_spriteRender[12]);
	SpriteIndicate(m_spriteRender[13]);
	SpriteIndicate(m_spriteRender[14]);
	SpriteIndicate(m_spriteRender[15]);
	SpriteIndicate(m_spriteRender[16]);
	SpriteIndicate(m_spriteRender[17]);
	SpriteIndicate(m_spriteRender[18]);
	SpriteIndicate(m_spriteRender[19]);
	SpriteIndicate(m_spriteRender[20]);

	//�r�������A���̏�����...�B
	if (m_spriteRender[20]->GetAlpha() >= 1.0f) {
		m_state = Result_GetJewelry;
	}


}
void Result::GetJewelry()
{
	//��Ε\���B
	//���U���g����̐^�񒆂ŕ\��
	//SpriteIndicate(m_spriteRender[10]);
	//�G�t�F�N�g�Đ����Ă�����ƍ��؂ɂ��܁B

}
void Result::SelectNext()
{
	//SelsctNext�̕\���B
}

void Result::Update()
{
	BackMove();
	switch (m_state)
	{
	case Result::Result_BackTable:
		BackTable();
		break;
	case Result::Result_FallMove:
		FallMove();
		break;
	case Result::Result_Frame:
		Frame();
		break;
	case Result::Result_StageName:
		StageName();
		break;
	case Result::Result_GetSoul:
		GetSoul();
		break;
	case Result::Result_SoulNumber:
		SoulNumber();
		break;
	case Result::Result_GetItem:
		GetItem();
		break;
	case Result::Result_Next:
		Next();
		break;
	case Result::Result_Removal:
		Removal();
		break;
	case Result::Result_GetJewelry:
		GetJewelry();
		break;
	case Result::Result_SelectNext:
		SelectNext();
		break;
	}
}
