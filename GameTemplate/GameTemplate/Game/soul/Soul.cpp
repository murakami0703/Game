#include "stdafx.h"
#include "Soul.h"
#include "player/Player.h"
#include "data/GameData.h"

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////
const CVector3 SOUL_SETSCALE = { 5.0f,5.0f,5.0f };	//���̊g��l�B
const int SOUL_GET = 1;		//�����l��
const float SOUL_DESTROY_TIME = 600.0f;	//���̏��Ŏ��ԁB
const float GROUND_POSY = 430.0f;		//�n�ʂ�Y���W�B
const float SOUL_GET_LENGTH = 50.0f;	//�����l���ł��鋗���B
const float SOUL_MOVESPEED = 5.0f;		//���̉��~���x�B

Soul::Soul(){}
Soul::~Soul(){}

bool Soul::Start()
{
	//�A�j���[�V�����N���b�v�̃��[�h�ƃ��[�v�t���O�̐ݒ�B
	m_animClips[eAnimation_Move].Load(L"Assets/animData/AnimaMove.tka");
	m_animClips[eAnimation_Move].SetLoopFlag(true);

	//cmo�t�@�C���̓ǂݍ��݁B
	m_animaModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_animaModelRender->Init(L"Assets/modelData/Anima.cmo", m_animClips, eAnimation_Num);
	m_animaModelRender->SetPosition(m_position);
	m_animaModelRender->SetScale(SOUL_SETSCALE);
	m_animaModelRender->PlayAnimation(eAnimation_Move);

	m_animaModelRender->SetShadowCaster(true);


	return  true;
}

void Soul::Appear()
{
	//�o�����B
	//�����n�ʂ��痣��Ă����牺�~���܂��B
	if (m_position.y <= GROUND_POSY) {
		//�n�ʕt�߂Ȃ̂Ŏ擾�ł���悤�ɂȂ��I
		m_timer++;
		Player* player = Player::GetInstance();
		if ((player->GetPosition() - m_position).Length() < SOUL_GET_LENGTH) {
			//�l��
			m_state = Anima_Get;

		}
		else if (m_timer > SOUL_DESTROY_TIME) {
			//���ŁB
			m_state = Anima_Destroy;
		}
	}
	else {
		//���~�B
		m_position.y -= SOUL_MOVESPEED;
	}

}
void Soul::Get()
{
	//�擾������I�I
	GameData::GetInstance()->SoulCalc(SOUL_GET);
	m_state = Anima_Destroy;	//�l�������̂ŏ��ł�����B
}
void Soul::Destroy()
{
	//���ŁB
	g_goMgr->DeleteGameObject(m_animaModelRender);
	g_goMgr->DeleteGameObject(this);
}

void Soul::Update()
{
	switch (m_state)
	{
	case Soul::Anima_Appear:
		//�o�����B
		Appear();
		break;
	case Soul::Anima_Get:
		//�l���B
		Get();
		break;
	case Soul::Anima_Destroy:
		//���ŁB
		Destroy();
		break;
	}

	//���[���h�s��̍X�V�B
	m_animaModelRender->SetPosition(m_position);
	m_animaModelRender->SetScale(SOUL_SETSCALE);

}

