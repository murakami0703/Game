#include "stdafx.h"
#include "FadeIn.h"


FadeIn::FadeIn()
{
}


FadeIn::~FadeIn()
{
}

bool FadeIn::Start()
{
	return true;
}

void FadeIn::Update()
{
		//フェードイン
	m_mulColor = m_sptiteRender->GetMulColor();

	m_mulColor.x += 0.005f;
	m_mulColor.y += 0.005f;
	m_mulColor.z += 0.005f;

	if (m_mulColor.x > 1.0f && m_mulColor.y > 1.0f && m_mulColor.z > 1.0f) {
		m_mulColor.x = 1.0f;
		m_mulColor.y = 1.0f;
		m_mulColor.z = 1.0f;

		m_sptiteRender->SetMulColor(m_mulColor);
		g_goMgr->DeleteGameObject(this);
		return;
	}
	else {
		m_sptiteRender->SetMulColor(m_mulColor);
	}
}