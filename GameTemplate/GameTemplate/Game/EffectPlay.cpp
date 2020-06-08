#include "stdafx.h"
#include "EffectPlay.h"

EffectPlay::EffectPlay()
{
	//�G�t�F�N�g�̃C���X�^���X�̍쐬�B
	effect = g_goMgr->NewGameObject<Effect>();
	effect->Play(animation.c_str());	//�Đ�
	effect->SetScale(scale);
	effect->SetPosition(position);

}


EffectPlay::~EffectPlay()
{
}

void EffectPlay::Update() {
	//���O�͂����m��
	bool Flag = effect->IsPlay();
	if (Flag == false) {
		g_goMgr->DeleteGameObject(this);
	}

}