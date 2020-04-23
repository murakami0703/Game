#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManeger.h"
#include "GameData.h"
#include "Anima.h"
#include "AnimaManeger.h"


Enemy::Enemy()
{

	//�A�j���[�V�����N���b�v�̃��[�h�B
	/*m_animClips[eneidle].Load(L"Assets/animData/eneIdle.tka");
	m_animClips[enewalk].Load(L"Assets/animData/eneWalk.tka");
	m_animClips[eneAttack_1].Load(L"Assets/animData/eneAT1.tka");
	m_animClips[eneDead].Load(L"Assets/animData/eneDeath.tka");

	//���[�v�t���O�̐ݒ�B
	m_animClips[eneidle].SetLoopFlag(true);
	m_animClips[enewalk].SetLoopFlag(true);
	*/
	//cmo�t�@�C���̓ǂݍ��݁B
	m_enemy = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemy->Init(L"Assets/modelData/slime.cmo");
	m_oldPos = m_position;
	m_enemy->SetPosition({ -4500.0f, 400.0f, -2500.0f });
	//�܂���
	/*{
		//�@���}�b�v���܂�
		DirectX::CreateDDSTextureFromFileEx(
			g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Normal.dds", 0,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			false, nullptr, &g_normalMapSRV
		);
		//�X�؃L�����}�b�v���܂�
		DirectX::CreateDDSTextureFromFileEx(
			g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Specular.dds", 0,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			false, nullptr, &g_specularMapSRV
		);
		//�A���r�G���g�}�b�v���܂�
		DirectX::CreateDDSTextureFromFileEx(
			g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/AO.dds", 0,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			false, nullptr, &g_ambientMapSRV
		);

		//���f���ɖ@���}�b�v�A�X�؃L�����}�b�v�A�A���r�G���g�}�b�v��ݒ肷��B
		//m_enemy.SetNormalMap(g_normalMapSRV);
		//m_enemy.SetSpecularMap(g_specularMapSRV);
		//m_enemy.SetAmbientMap(g_ambientMapSRV);
	}
	*/
	//m_animation.Init(m_enemy->GetSkinModel(), m_animClips, num);	//�A�j���[�V�����̏�����

}

Enemy::~Enemy()
{
	// �@���}�b�v������B
	/*if (g_normalMapSRV != nullptr) {
		g_normalMapSRV->Release();
	}
	*/
}

void Enemy::Follow()
{
	/*//�ǔ�����
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
	CVector3 targetVector = player->GetPosition() - m_position;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;
	*/
}

void Enemy::move()
{
	//�p�j��
	m_moveCount++;
	m_position.z += m_moveSpeed;
	//�㉺�p�j
	if (m_moveCount == 100) {
		m_moveSpeed = -m_moveSpeed;
	}
	if (m_moveCount == 200) {
		m_moveSpeed = m_moveSpeed;
		m_moveCount = 0;
	}
	

}

void Enemy::Attack()
{
	/*m_animation.Play(eneAttack_1);//�U��
	//���̍s���ցB�B
	if (m_animation.IsPlaying() == false) {
		if ((player->GetPosition() - m_position).Length() < 80.0f) {
			//�ߋ����ōU��������
			//HP���炷
			GameData::GetInstance()->HPCalc(-0.5f);
		}

		if (m_battlePoint != nullptr) {
			m_state = eState_TuisekiPlayer;
		}
		else {
			m_state = eState_Haikai;
		}
	}*/
}

void Enemy::Return()
{
	/*//�p�j�ʒu�ɖ߂�B
	CVector3 diff = m_position - m_oldPos;
	diff.y = 0.0f;
	diff.Normalize();
	m_position += diff * m_moveSpeed;
	if (diff.Length() < 1.0f) {
		m_state = eState_Haikai;
	}

	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
	//�@���������������̃x�N�g�����v�Z����B
	CVector3 targetVector = m_oldPos - m_position;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;
	*/
}
void Enemy::Dead()
{
	/*m_animation.Play(eneDead);//��
	if (m_animation.IsPlaying() == false) {
		//���ɂ܂���
		EnemyManager::GetInstance()->DeleteEnemy(this);
	}*/
}

void Enemy::Update()
{
	
	/*p_pos = player->GetPosition();
	m_toPlayerVec = p_pos - m_position;

	if (player->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < 60.0f) {
			m_state = eState_Dead;
		}
	}
	*/
	//m_animation.Update(0.05f);//�A�j���[�V�����Đ�

	/*switch (m_state) {
	case eState_Haikai:
		//�p�j��
		m_animation.Play(enewalk);//����
		move();
		if (m_toPlayerVec.Length() < m_tuisekiLength ) {
			m_battlePoint = EnemyManager::GetInstance()->TryGetBattlePoint(m_position);
			if(m_battlePoint!= nullptr){
				m_state = eState_TuisekiPlayer;
			}
		}
		break;
	case eState_Attack:
		Attack(player);
		break;
	case eState_TuisekiPlayer:
		//�v���C���[��ǐ�
		m_animation.Play(enewalk);//����
		Follow(player);
		//�߂��̂ōU��
		if (m_battlePoint != nullptr) {
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
		m_animation.Play(enewalk);//����
		Return();
		break;
	case eState_Dead:
		//��
		Dead();
		break;
	}*/

	//���[���h�s��̍X�V�B
	m_enemy->SetPosition(m_position);
	m_enemy->SetRotation(m_rotation);

}
void Enemy::Render()
{
}

void Enemy::PostRender()
{

}
