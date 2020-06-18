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
	effect->Play(animation.c_str());	//再生
	effect->SetScale(scale);
	effect->SetPosition(position);

	return true;
}

void EffectPlay::Update() {
	//お前はもう洋梨
	bool Flag = effect->IsPlay();
	if (Flag == false) {
		g_goMgr->DeleteGameObject(this);
	}

}