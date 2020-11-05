#include "stdafx.h"
#include "Bomb.h"
#include "player/Player.h"
#include "data/GameData.h"

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const CVector3 BOMB_SCALE = { 0.5f,0.5f ,0.5f };			//���e�̊g�嗦�B

const float DISPOSITION_ADD_Y = -250.0f;					//�z�u����ꏊ��Y���̉��Z�l�B
const float DISPOSITION_ADD_X_OR_Z = 400.0f;				//�z�u����ꏊ��Z���܂���X���̉��Z�l�B
const float BOMB_MOVE_SPEED = 5.0f;							//���e�̈ړ����x�B
const float BOMB_END_POSITION = 2.0f;						//���e�̏I�������ꏊ�B

Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}
bool Bomb::Start()
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

void Bomb::Parabolic()
{

	Player* player = Player::GetInstance();
	//�v���C���[�̌����ɂ���ĕ��蓊����ʒu�����߂܂��B
	//CMath::DegToRad(359.0f)�p�x�@IF
	if (player->GetRotation().y == CMath::DegToRad(80.0f)) {
		//��
		disPosition.x = m_position.x - DISPOSITION_ADD_X_OR_Z;
		disPosition.y = m_position.y + DISPOSITION_ADD_Y;

	}
	else if (player->GetRotation().y == CMath::DegToRad(-80.0f)) {
		//�E
		disPosition.x = m_position.x + DISPOSITION_ADD_X_OR_Z;
		disPosition.y = m_position.y + DISPOSITION_ADD_Y;

	}
	else if (player->GetRotation().y == CMath::DegToRad(0.0f)) {
		//��
		disPosition.z = m_position.z + DISPOSITION_ADD_X_OR_Z;
		disPosition.y = m_position.y + DISPOSITION_ADD_Y;

	}
	else if (player->GetRotation().y == CMath::DegToRad(110.0f)) {
		//��
		disPosition.z = m_position.z - DISPOSITION_ADD_X_OR_Z;
		disPosition.y = m_position.y + DISPOSITION_ADD_Y;

	}


}
void Bomb::MoveBomb() {

	//�ړ������B
	if (m_bombMoveFlag != false) {
		m_position = Player::GetInstance()->GetPosition();
		if (g_pad[0].IsTrigger(enButtonX)) {
			Parabolic();
			m_bombMoveFlag = false;
		}
	}
	else {
		CVector3 move = m_position - disPosition;
		move.Normalize();
		m_position += move * BOMB_MOVE_SPEED;
	}
}

void Bomb::InUse()
{
	//�g�p���B
	GameData* gamedata = GameData::GetInstance();

	MoveBomb();

	//���e�̏����I���B
	if ((m_position - disPosition).Length() <= BOMB_END_POSITION) {
		gamedata->SetItemInUseFlag(false);
	}

	m_skinModelRender->SetPosition(m_position);

}
void Bomb::EndUse()
{
	//�I���B
	//����������B

}
