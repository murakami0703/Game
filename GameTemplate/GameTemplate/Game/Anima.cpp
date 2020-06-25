#include "stdafx.h"
#include "Anima.h"
#include "Player.h"
#include "GameData.h"

Anima::Anima()
{
}


Anima::~Anima()
{
}


bool Anima::Start()
{
	//�A�j���[�V�����N���b�v�̃��[�h�ƃ��[�v�t���O�̐ݒ�B
	m_animClips[eAnimation_Move].Load(L"Assets/animData/AnimaMove.tka");
	m_animClips[eAnimation_Move].SetLoopFlag(true);
	//cmo�t�@�C���̓ǂݍ��݁B
	m_animaModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_animaModelRender->Init(L"Assets/modelData/Anima.cmo", m_animClips, eAnimation_Num);
	m_animaModelRender->SetPosition(m_position);
	m_animaModelRender->SetScale(m_soulScale);

	m_animaModelRender->PlayAnimation(0);
	m_animaModelRender->SetShadowMap(true);

	return  true;
}

void Anima::Appear()
{	
	//�n�ʂ��痣��Ă����牺�~������B
	if (m_position.y <= m_GroundYPos) {
		//�o�����B
		m_timer++;
		Player* player = Player::GetInstance();
		if ((player->GetPosition() - m_position).Length() < m_toPlayerPos) {
			//�擾
			m_state = Anima_Get;

		}
		else if (m_timer > m_destroyTimer) {
			//���ŁB
			m_state = Anima_Destroy;
		}
	}
	else {
		m_position.y -= m_moveSpeed;
	}

}

void Anima::Get()
{	//�擾������I�I
	GameData::GetInstance()->AnimaCalc(1);
	g_goMgr->DeleteGameObject(m_animaModelRender);
	g_goMgr->DeleteGameObject(this);
}
void Anima::Destroy()
{	//���Ԍo�߂̂��ߏ��ŁB
	g_goMgr->DeleteGameObject(m_animaModelRender);
	g_goMgr->DeleteGameObject(this);
}
void Anima::Update()
{
	switch (m_state)
	{
	case Anima::Anima_Appear:
		Appear();
		break;
	case Anima::Anima_Get:
		Get();
		break;
	case Anima::Anima_Destroy:
		Destroy();
		break;
	}


	//���[���h�s��̍X�V�B
	m_animaModelRender->SetPosition(m_position);
	m_animaModelRender->SetScale(m_soulScale);

}

