#include "stdafx.h"
#include "FadeOut.h"


FadeOut::FadeOut()
{
}


FadeOut::~FadeOut()
{
}
bool FadeOut::Start() {	return true; }

void FadeOut::Update()
{
		//�t�F�[�h�A�E�g
	m_mulColor = m_sptiteRender->GetMulColor();

	m_mulColor.x -= 0.001f;
	m_mulColor.y -= 0.001f;
	m_mulColor.z -= 0.001f;
	if (m_mulColor.x  < 0.0f && m_mulColor.y  < 0.0f && m_mulColor.z < 0.0f) {
		m_mulColor.x = 0.0f;
		m_mulColor.y = 0.0f;
		m_mulColor.z = 0.0f;
		m_sptiteRender->SetMulColor(m_mulColor);
		g_goMgr->DeleteGameObject(this);
	}
	else {
		m_sptiteRender->SetMulColor(m_mulColor);
	}
}