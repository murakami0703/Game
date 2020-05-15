#include "stdafx.h"
#include "Ghosts.h"
#include "Player.h"
#include "SiegePoint.h"

Ghosts::Ghosts()
{
	m_animClips[Ghosts_walk].Load(L"Assets/animData/ghost_walk.tka");

	//���[�v�t���O�̐ݒ�B
	m_animClips[Ghosts_walk].SetLoopFlag(true);
	//cmo�t�@�C���̓ǂݍ��݁B
	m_enemy = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemy->Init(L"Assets/modelData/ghosts.cmo");
	m_oldPos = m_position;
	m_animation.Init(m_enemy->GetSkinModel(), m_animClips, num);	//�A�j���[�V�����̏�����


}


Ghosts::~Ghosts()
{
}

void Ghosts::Follow()
{
}

void Ghosts::move()
{
	//�ǔ�����
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	if (m_toBPVec.Length() > 10.0f){
		m_toBPVec.y = 0.0f;
		m_toBPVec.Normalize();
		m_position += m_toBPVec * m_follSpeed;
	}
	else if (m_toBPVec.Length() < 10.0f) {
		//BP���܂���
		m_battlePosflag = true;
	}
	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };

	//�@���������������̃x�N�g�����v�Z����B
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;
	

	m_animation.Play(Ghosts_walk);
}

void Ghosts::Attack()
{
	m_state = eState_Haikai;
}

void Ghosts::Return()
{
}
void Ghosts::Dead()
{
}

void Ghosts::Update()
{
	//���S����
	/*p_pos = player->GetPosition();
	m_toPlayerVec = p_pos - m_position;

	if (player->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < 60.0f) {
			m_state = eState_Dead;
		}
	}
	*/


	switch (m_state) {
	case eState_Haikai:
		//�p�j��
		move();
		if (m_toPlayerVec.Length() < m_tuisekiLength) {
			//�U���͈͂ɋ߂Â����Ƃ��o�g���|�C���g���󂢂Ă���Ǐ]���܂��B
			m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
			if (m_battlePoint != nullptr) {
				m_state = eState_TuisekiPlayer;
			}
		}
		break;
	case eState_Attack:
		Attack();
		break;
	case eState_TuisekiPlayer:
		//�v���C���[��ǐ�
		Follow();
		if (m_battlePoint != nullptr) {
			//�߂��̂ōU��
			if (m_toPlayerVec.Length() < 80.0f) {
				EneAttackflag = true;
				m_state = eState_Attack;
			}
		}
		//�����Ȃ����̂Ŝp�j�ʒu�ɖ߂�
		if (m_toPlayerVec.Length() > m_ReturnLength) {
			m_state = eState_Haikai;
		}
		break;
	case eState_Return:
		//�p�j�ʒu�ɖ߂�
		break;
	case eState_Dead:
		//��
		Dead();
		break;
	}
	m_animation.Update(0.05f);//�A�j���[�V�����Đ�

	//���[���h�s��̍X�V�B
	m_enemy->SetPosition(m_position);
	m_enemy->SetRotation(m_rotation);
	m_enemy->SetScale(m_scale);

}
void Ghosts::Render()
{
}

void Ghosts::PostRender()
{

}
