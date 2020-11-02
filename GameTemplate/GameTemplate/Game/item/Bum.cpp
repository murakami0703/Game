#include "stdafx.h"
#include "item/Bum.h"
#include "player/Player.h"
#include "data/GameData.h"


/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const CVector3 BOMB_SCALE = { 0.5f,0.5f ,0.5f };
Bum::Bum()
{
}


Bum::~Bum()
{
}
bool Bum::Start()
{

	//�X�L�����f���B
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/Bum.cmo");
	m_position = Player::GetInstance()->GetPosition();
	m_position.y += 250.0f;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(BOMB_SCALE);

	return true;
}

void Bum::Parabolic()
{
	Player* player = Player::GetInstance();
	//�v���C���[�̌����ɂ���ĕ��蓊����ʒu�����߂܂��B
	//CMath::DegToRad(359.0f)�p�x�@IF
	if (player->GetRotation().y == CMath::DegToRad(80.0f)) {
		//��
	}
	else if (player->GetRotation().y == CMath::DegToRad(-80.0f)) {
		//�E
	}
	else if (player->GetRotation().y == CMath::DegToRad(0.0f)) {
		//��
	}
	else if (player->GetRotation().y == CMath::DegToRad(110.0f)) {
		//��
	}


}

void Bum::InUse()
{
	//�g�p���B
	GameData* gamedate = GameData::GetInstance();

	//�ړ������B
	if (g_pad[0].IsTrigger(enButtonX)) {
	}
	else if(gamedate->GetItemInUseFlag() != true){
		m_position = Player::GetInstance()->GetPosition();
		m_position.y += 250.0f;
	}
	m_skinModelRender->SetPosition(m_position);

}
void Bum::EndUse()
{
	//�I���B


}
