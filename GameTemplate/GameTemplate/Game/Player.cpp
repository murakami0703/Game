#include "stdafx.h"
#include "Player.h"
#include "ShadowMap.h"
#include "GameData.h"
#include "EffectManager.h"


Player* Player::m_instance = nullptr;

Player::Player()
{
	m_instance = this;
}
Player::~Player()
{
}

bool Player::Start()
{

	//�A�j���[�V�����N���b�v�̃��[�h�ƃ��[�v�t���O�̐ݒ�B
	m_animClips[Animation_Idel].Load(L"Assets/animData/eneIdle.tka");
	m_animClips[Animation_Idel].SetLoopFlag(true);
	m_animClips[Animation_Walk].Load(L"Assets/animData/eneWalk.tka");
	m_animClips[Animation_Walk].SetLoopFlag(true);
	m_animClips[Animation_Attack1].Load(L"Assets/animData/eneAT1.tka");
	m_animClips[Animation_Dead].Load(L"Assets/animData/eneDeath.tka");

	//cmo�t�@�C���̓ǂݍ��݁B
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/Footman_Default.cmo", m_animClips, AnimationClip_Num);
	m_position = { -4300.0f, 400.0f, -3000.0f };
	m_skinModelRender->SetPosition(m_position);

	m_scale = { 50.0f, 50.0f, 50.0f };
	m_skinModelRender->SetScale(m_scale);
	m_characon.Init(20.0f, 30.0f, m_position);//�L�����R��
	m_move = m_position;

	//�@���}�b�v���܂�
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/modelData/Normal.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_normalMapSRV
	);
	//�X�؃L�����}�b�v���܂�
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/modelData/MatallicSmoothness.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_specularMapSRV
	);

	//�A���r�G���g�}�b�v���܂�
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/modelData/AO.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_ambientMapSRV
	);
	m_skinModelRender->SetNormalMap(g_normalMapSRV);
	m_skinModelRender->SetSpecularMap(g_specularMapSRV);
	m_skinModelRender->SetSpecularMap(g_ambientMapSRV);

	m_nowHP = GameData::GetInstance()->GetHitPoint();
	m_skinModelRender->SetShadowMap(true);
	return true;
}

void Player::Idel()
{
	m_skinModelRender->PlayAnimation(0);

	//�ҋ@��ԂȂɂ����Ȃ�
	if (g_pad[0].IsPressAnyKey())
	{
		m_state = Player_Walk;
	}

}
void Player::Move()
{
	m_move.x = 0.0f;
	m_move.z = 0.0f;

	//�\���ړ��Ɖ�]�B
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_move.x -= m_movespeed;
		m_rotation.SetRotation(CVector3().AxisY(), m_rotationLR);

	}
	else if (g_pad[0].IsPress(enButtonRight)) {
		m_move.x += m_movespeed;
		m_rotation.SetRotation(CVector3().AxisY(), -m_rotationLR);

	}
	else if (g_pad[0].IsPress(enButtonUp)) {
		m_move.z += m_movespeed;
		m_rotation.SetRotation(CVector3().AxisY(), 0.0f);

	}
	else if (g_pad[0].IsPress(enButtonDown)) {
		m_move.z -= m_movespeed;
		m_rotation.SetRotation(CVector3().AxisY(), m_rotationD);

	}
	else if (g_pad[0].IsTrigger(enButtonA) && m_characon.IsOnGround() == false) {
		//�W�����v
		//m_move.y = m_jumpPos;
	}

	m_move.y -= 1.0f;
	if (m_characon.IsOnGround()) {
		//�d�̓X�g�b�v
		m_move.y = 0.0f;
	}
	m_position = m_characon.Execute(m_caraTime, m_move);
	m_skinModelRender->PlayAnimation(1);

}
void Player::Attack()
{
	EffectManager* effect = EffectManager::GetInstance();
	if (Atcount == 1 && attackflag == false) {
		//�U��1���
		m_skinModelRender->PlayAnimation(2);
		//effect->EffectPlayer(EffectManager::Bat_memai, m_position, { 10.0f,10.0f,10.0f });
		//m_se.Play(false);
		attackflag = true;
		Atcount = 0;
	}
	/*if (Atcount >= 2) {
		//�U��2���
		m_animation.Play(Animation_Attack2, 0.5f);
		attackflag = true;
		if (m_animation.IsPlaying() == false) {
			//�Đ��I��������ҋ@�ɖ߂�
			Atcount = 0;
			attackflag = false;
			m_anime = Animation_Idel;
		}

	}*/
	if (m_skinModelRender->IsPlayingAnimation() == false && attackflag == true) {
		//�Đ��I��������ҋ@�ɖ߂�
		attackflag = false;
		m_state = Player_Idle;
	}

}
void Player::Dead()
{
	//���S
}

void Player::Damage()
{
	GameData* gamedata = GameData::GetInstance();
	//�_���[�W�󂯂܂����B
	//�Ԃ����܂��您
	m_skinModelRender->SetLightColor({ 0.7f,0.0f,0.0f,1.0f });
	m_damageTimer++;
	//������Ǝ��Ԍo�߂����猳�ɖ߂��B
	if (m_damageTimer>=10) {
		m_skinModelRender->SetLightColor({ 0.7f,0.7f,0.7f,1.0f });
		m_nowHP = gamedata->GetHitPoint();
		m_state = Player_Idle;
	}

}
void Player::Update()
{
	GameData* gamedata = GameData::GetInstance();
	//�U�����܂��B
	if (g_pad[0].IsTrigger(enButtonA) ) {
		Atcount = 1;
		m_state = Player_Attack;
	}
	/*//�_���[�W�󂯂܂������
	if (gamedata->GetHitPoint() <= m_nowHP) {
		m_state = Player_Damage;
	}
	*/
	switch (m_state)
	{
	case Player::Player_Idle:
		Idel();			//�ҋ@
		break;
	case Player::Player_Walk:
		Move();			//�ړ�
		break;
	case Player::Player_Attack:
		Attack();		//�U��
		break;
	case Player::Player_Dead:
		Dead();			//���S
		break;
	case Player::Player_Damage:
		Damage();		//�_���[�W�󂯂܂�����
		break;
	}

	//���[���h�s��̍X�V�B
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}

