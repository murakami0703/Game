#include "stdafx.h"
#include "EffectPlay.h"
#include "Player.h"

EffectPlay::EffectPlay()
{
	//�G�t�F�N�g�̃C���X�^���X�̍쐬�B
	/*effect = g_goMgr->NewGameObject<Effect>();
	effect->SetPostRenderFlag(m_isPost);
	effect->Play(animation.c_str());	//�Đ�
	effect->SetScale(scale);
	effect->SetPosition(position);

	if (P_RotationFlag == true) {
		Player * player = Player::GetInstance();
		CQuaternion Rot = player->GetRotation();
		Rot = Rot * -1.0f;
		effect->SetRotation(Rot);
	}*/
}


EffectPlay::~EffectPlay()
{
}

void EffectPlay::Update() {
	/*if (P_TuibiFlag == true) {
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		effect->SetPosition(P_Position);
	}

	//���O�͂����m��
	bool Flag = effect->IsPlay();
	if (Flag == false) {
		DeleteGO(this);
	}*/

}