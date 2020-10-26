#include "stdafx.h"
#include "graphics/effect/EffectPlay.h"

EffectPlay::EffectPlay()
{
}


EffectPlay::~EffectPlay()
{
}

bool EffectPlay::Start()
{
	effect = g_goMgr->NewGameObject<Effect>();
	effect->Play(animation.c_str());	//Ä¶
	effect->SetScale(m_scale);
	effect->SetPosition(m_position);
	effect->SetRotation(m_rotation);
	return true;
}

void EffectPlay::Update() {
	//‚¨‘O‚Í‚à‚¤—m—œ
	bool Flag = effect->IsPlay();
	if (Flag == false) {
		g_goMgr->DeleteGameObject(this);
	}

}