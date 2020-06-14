#include "stdafx.h"
#include "Ghost.h"
#include "GameData.h"
#include "Anima.h"
#include "AnimaManeger.h"
#include "Player.h"
#include "SiegePoint.h"



Ghost::Ghost()
{

	//�A�j���[�V�����N���b�v�̃��[�h�ƃ��[�v�t���O�̐ݒ�B
	m_animClips[eAnimation_Idle].Load(L"Assets/animData/ghost/ghost_Idle.tka");
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/ghost/ghost_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/ghost/ghost_premove.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/ghost/ghost_death.tka");
	//cmo�t�@�C���̓ǂݍ��݁B
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/ghosts.cmo", m_animClips, eAnimation_Num);
	m_position = { -4200.0f, 410.0f, -2500.0f };
	m_scale = { 2.0f, 2.0f, 2.0f };

	//m_oldPos = m_position;		//�������W��m_oldPos�ɐݒ�B
	m_characon.Init(20.0f, 30.0f, m_position);//�L�����R��
	m_enemyModelRender->SetShadowMap(true);

}

Ghost::~Ghost()
{
}
void Ghost::Idle()
{
	//�ҋ@�B

	if (timer >= a) {
		m_state = eState_Loitering;
	}
	timer++;
	m_enemyModelRender->PlayAnimation(1);
}

void Ghost::Follow()
{
	//�ǔ�����
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	if (m_toBPVec.Length() > 50.0f) {
		m_toBPVec.y = 0.0f;
		m_toBPVec.Normalize();
		moveVec = m_toBPVec * 200.0f;

	}
	/*else if (m_toBPVec.Length() < 10.0f) {
		//BP���܂���
		m_battlePosflag = true;
	}*/
	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };

	//�@���������������̃x�N�g�����v�Z����B
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;


	//�߂��̂ōU��
	if (m_battlePoint != nullptr) {
		if (m_toPlayerVec.Length() <= 200.0f) {
			EneAttackflag = true;
			m_state = eState_Premove;
		}
	}
	//�����Ȃ����̂ł��̏�Ŝp�j�B
	if (m_toPlayerVec.Length() > 600.0f) {
		m_battlePoint->enemyCount = 0;
		m_battlePoint = nullptr;
		m_state = eState_Loitering;
	}
	m_position = m_characon.Execute(m_caraTime, moveVec);
	m_enemyModelRender->PlayAnimation(1);

}

void Ghost::Loitering()
{
	//�p�j�B
	Player* player = Player::GetInstance();
	CVector3 P_Position = player->GetPosition();
	CVector3 diff = P_Position - m_position;
	m_position;
	count++;
	if (flag == true) {
		//�����_���ŕ��������肵�ē����܂�
		wrandom = rand() % 360;
		m_rotation.SetRotation(CVector3::AxisY(), (float)wrandom);
		walkmove = { 0.0f, 0.0f,-1.0f };
		m_rotation.Multiply(walkmove);
		count = 0;
		flag = false;
	}
	else if (count >= randomCount) {
		flag = true;
	}
	moveVec = walkmove * randomSpeed;
	m_position = m_characon.Execute(m_caraTime, moveVec);

	if (diff.Length() < 500.0f) {
		//�v���C���[�Ƃ̋������߂��Ȃ�����ǐՂ��܂�
		m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
		//�󂢂Ă�o�g���|�C���g�Ɍ������Ă�����
		if (m_battlePoint != nullptr) {
			flag = true;
			m_state = eState_Follow;
		}
	}

	m_enemyModelRender->PlayAnimation(1);
	
}
void Ghost::Premove()
{	

	CVector3 diff = m_toPlayerVec;
	diff.Normalize();

	timer1++;
	if (timer1 <= 20) {
		moveVec = diff * 200.0f;
	}
	else if (timer1 >= 20 && timer1 <= 50) {
		moveVec += diff * 0.2f;
		moveVec.y += 20.0f;
	}
	else {
		timer1 = 0;
		dff = m_toPlayerVec;
		dff.Normalize();
		m_state = eState_Attack;

	}


	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };

	//��]�̏���
	if (fabsf(m_position.x) < 0.001f
		&& fabsf(m_position.z) < 0.001f) {
		//�킩���
		return;
	}
	//�@���������������̃x�N�g�����v�Z����B
	CVector3 targetVector = m_toPlayerVec;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

	m_position = m_characon.Execute(m_caraTime, moveVec);
	m_enemyModelRender->PlayAnimation(2,0.5f);
}
void Ghost::Attack()
{
	//�U�������I�I�I

	//�}�~�����܂�


	if (m_position.y >= 400.0f) {
		moveVec = dff * 1000.0f;
	}
	else {
		moveVec = { 0.0f,0.0f,0.0f };

	}
	m_position = m_characon.Execute(m_caraTime, moveVec);



		/*if (m_battlePoint != nullptr) {
			m_state = eState_Follow;
		}
		else {
			m_battlePoint->enemyCount = 0;
			m_battlePoint = nullptr;
			m_state = eState_Loitering;
		}
		if ((Player::GetInstance()->GetPosition() - m_position).Length() < 150.f) {
			//�ߋ����ōU��������
			//HP���炷
			GameData::GetInstance()->HPCalc(-0.5f);
		}*/
	m_enemyModelRender->PlayAnimation(0);

}

void Ghost::Dead()
{
	m_enemyModelRender->PlayAnimation(3);
	if (m_enemyModelRender->IsPlayingAnimation() == false) {
		//�A�j���[�V�����̍Đ����I������̂ŏ�����
		//�G�l�~�[�̐����炵�܂�
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();
		//�����Ȃ����B
		g_goMgr->DeleteGameObject(this);
		g_goMgr->DeleteGameObject(m_enemyModelRender);
	}

}

void Ghost::Update()
{
	//�v���C���[�Ƃ̋����𒲂ׂ�B
	m_playerPos = Player::GetInstance()->GetPosition();
	m_toPlayerVec = m_playerPos - m_position;

	//�U�������������̂Ŏ��ʁB
	if (Player::GetInstance()->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < 200.0f) {
			m_state = eState_Dead;
		}
	}

	switch (m_state) {
	case Ghost::eState_Idle:
		Idle();
		break;
	case Ghost::eState_Loitering:
		Loitering();		//�p�j��
		break;
	case Ghost::eState_Follow:
		Follow();			//�v���C���[��ǐ�
		break;
	case Ghost::eState_Premove:
		Premove();			//�p�j�ʒu�ɖ߂�
		break;
	case Ghost::eState_Attack:
		Attack();			//�U��
		break;
	case Ghost::eState_Dead:
		Dead();				//��
		break;
	}

	//���[���h�s��̍X�V�B
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);
}
