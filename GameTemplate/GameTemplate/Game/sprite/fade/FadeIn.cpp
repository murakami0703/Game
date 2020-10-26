#include "stdafx.h"
#include "sprite/fade/FadeIn.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const float ADD_VALUE = 0.0005f;	//加算する値。
const float FADEIN_FINISHED = 1.0f;	//フェードインを終了させる値。

FadeIn::FadeIn()
{
}
FadeIn::~FadeIn()
{
}

bool FadeIn::Start(){return true;}

void FadeIn::Update()
{
		//フェードイン
	m_mulColor = m_sptiteRender->GetMulColor();

	m_mulColor.x += ADD_VALUE;
	m_mulColor.y += ADD_VALUE;
	m_mulColor.z += ADD_VALUE;

	if (m_mulColor.x > FADEIN_FINISHED && 
		m_mulColor.y > FADEIN_FINISHED && 
		m_mulColor.z > FADEIN_FINISHED) 
	{
		m_mulColor.x = FADEIN_FINISHED;
		m_mulColor.y = FADEIN_FINISHED;
		m_mulColor.z = FADEIN_FINISHED;

		m_sptiteRender->SetMulColor(m_mulColor);
		g_goMgr->DeleteGameObject(this);
	}
	else {
		m_sptiteRender->SetMulColor(m_mulColor);
	}
}