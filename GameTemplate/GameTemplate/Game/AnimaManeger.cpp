#include "stdafx.h"
#include "AnimaManeger.h"

AnimaManeger* AnimaManeger::m_instance = nullptr;

AnimaManeger::AnimaManeger()
{
	m_instance = this;
}


AnimaManeger::~AnimaManeger()
{
}

void AnimaManeger::Update(Player* player)
{
	for (auto& ani : m_animas) {
		ani->Update(player);
	}
}
void AnimaManeger::Draw(EnRenderMode renderMode)
{
	for (auto& ani : m_animas) {
		ani->Draw(renderMode);
	}
}