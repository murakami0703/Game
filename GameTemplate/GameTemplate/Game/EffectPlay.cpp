#include "stdafx.h"
#include "EffectPlay.h"

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
	effect->SetScale(scale);
	effect->SetPosition(position);

	return true;
}

void EffectPlay::Update() {
	//‚¨‘O‚Í‚à‚¤—m—œ
	bool Flag = effect->IsPlay();
	if (Flag == false) {
		g_goMgr->DeleteGameObject(this);
	}

}