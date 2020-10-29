#include "stdafx.h"
#include "item/AttackUp.h"
#include "player/Player.h"
#include "data/GameData.h"
#include "manager/EffectManager.h"


/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////
const CVector3 ITEMFRAME_SET_POTITION = { -600.0f,100.0f ,0.0f };		//�t���[���̍��W�B
const CVector3 ITEMFRAME_SET_SCALE = { 1.5f,1.5f ,1.5f };			//�t���[���̊g�嗦�B

const CVector3 ITEM_SET_POTITION = { -600.0f,100.0f ,0.0f };		//�A�C�e���̍��W�B
const CVector3 ITEM_SET_SCALE = { 0.65f,0.65f ,0.65f };			//�A�C�e���̊g�嗦�B

const float ICON_INCREASE_TIME = 30.0f;						//�A�C�R���̖��邳�𑝉������鎞�ԁB
const float ICON_DECREASE_TIME = 60.0f;						//�A�C�R���̖��邳�����������鎞�ԁB
const float ICON_DELTA_ALPHA = 0.7f / 30.0f;				//�ψʂ����铧���x�̒l�B
const float ICON_TIMER_RESET = 0.0f;						//�A�C�R���̃^�C�}�[��������Ԃɂ���B

const int ITEM_USE_TIME = 600;						//�A�C�e���g�p���ԁB
const int ITEM_USE_ICON_FLASHINGTIME = 420;			//�A�C�e���A�C�R���̓_�ŊJ�n���ԁB
AttackUp::AttackUp()
{
}


AttackUp::~AttackUp()
{
	g_goMgr->DeleteGameObject(m_frameSprite);
	g_goMgr->DeleteGameObject(m_itemiconSprite);
}

bool AttackUp::Start()
{
	//����ɕ\������A�C�R���֌W��sprite
	{
		//0�ԁ��g
		m_frameSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_frameSprite->Init(L"Assets/sprite/itemframe.dds", 75.0f, 50.0f);
		m_frameSprite->SetPosition(ITEMFRAME_SET_POTITION);
		m_frameSprite->SetScale(ITEMFRAME_SET_SCALE);

		//1�ԁ��X�s�[�h�A�b�v��
		m_itemiconSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemiconSprite->Init(L"Assets/sprite/SpeedUp.dds", 125.0f, 125.0f);
		m_itemiconSprite->SetPosition(ITEM_SET_POTITION);
		m_itemiconSprite->SetScale(ITEM_SET_SCALE);
	}

	//�U����UP�B
	GameData* gamedata = GameData::GetInstance();
	gamedata->ATKIncrease();

	return true;
}

void AttackUp::Flashing()
{
	//�A�C�R���̓_�ŁB
	m_flashingTimer++;
	if (m_flashingTimer <= ICON_INCREASE_TIME) {
		m_itemiconSprite->DeltaAlpha(ICON_DELTA_ALPHA);
	}
	else if (m_flashingTimer <= ICON_DECREASE_TIME)
	{
		m_itemiconSprite->DeltaAlpha(-ICON_DELTA_ALPHA);
	}
	else {
		m_flashingTimer = ICON_TIMER_RESET;
	}

}
void AttackUp::InUse()
{
	GameData* gamedata = GameData::GetInstance();
	//�g�p���B
	m_timer++;

	if (m_timer >= ITEM_USE_TIME) {
		//��莞�Ԍo�߂����̂ŃA�C�e�����ʂ������B
		gamedata->SetItemInUseFlag(false);
	}
	else if (m_timer >= ITEM_USE_ICON_FLASHINGTIME) {
		//���������Ō��ʂ��؂��̂ŃA�C�R�����_�ł����ĕ�����₷�����܂��B
		Flashing();
	}

}
void AttackUp::EndUse()
{
	//�I���B
		//�I���B
	GameData* gamedata = GameData::GetInstance();
	gamedata->ATKRevert();
	g_goMgr->DeleteGameObject(this);

}
