#include "stdafx.h"
#include "SpeedUp.h"
#include "Player.h"
#include "GameData.h"
#include "EffectManager.h"


const CVector3 ITEMFRAME_SET_POTITION = { -600.0f,100.0f ,0.0f };		//�t���[���̍��W�B
const CVector3 ITEMFRAME_SET_SCALE = { 1.5f,1.5f ,1.5f };			//�t���[���̊g�嗦�B

const CVector3 ITEM_SET_POTITION = { -600.0f,100.0f ,0.0f };		//�A�C�e���̍��W�B
const CVector3 ITEM_SET_SCALE = { 0.65f,0.65f ,0.65f };			//�A�C�e���̊g�嗦�B

const float ICON_INCREASE_TIME = 30.0f;						//�A�C�R���̖��邳�𑝉������鎞�ԁB
const float ICON_DECREASE_TIME = 60.0f;						//�A�C�R���̖��邳�����������鎞�ԁB
const float ICON_DELTA_ALPHA = 0.7f / 30.0f;				//�ψʂ����铧���x�̒l�B
const float ICON_TIMER_RESET = 0.0f;						//�A�C�R���̃^�C�}�[��������Ԃɂ���B

SpeedUp::SpeedUp()
{
}


SpeedUp::~SpeedUp()
{
}

bool SpeedUp::Start()
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

	return true;
}
void SpeedUp::InUse()
{
	//�g�p���B
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
void SpeedUp::EndUse()
{
	//�I���B
	g_goMgr->DeleteGameObject(this);
}
void SpeedUp::Update() {

}

