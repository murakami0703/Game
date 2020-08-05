#include "stdafx.h"
#include "FadeOut.h"


FadeOut::FadeOut()
{
}


FadeOut::~FadeOut()
{
}
bool FadeOut::Start() 
{
	return true; 
}

void FadeOut::Update()
{
		//フェードアウト
	m_mulColor = m_sptiteRender->GetMulColor();

	m_mulColor.w -= 0.05f;
	if (m_mulColor.w < 0.0f) {
		m_mulColor.w = 0.0f;
		m_sptiteRender->SetMulColor(m_mulColor);
		g_goMgr->DeleteGameObject(this);
		return;
	}
	else {
		m_sptiteRender->SetMulColor(m_mulColor);
	}
}