#include "stdafx.h"
#include "FadeOut.h"

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const float DECREASE_VALUE = 0.001f;	//��������l�B
const float FADEOUT_FINISHED = 0.0f;	//�t�F�[�h�A�E�g���I��������l�B

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

	m_mulColor.x -= DECREASE_VALUE;
	m_mulColor.y -= DECREASE_VALUE;
	m_mulColor.z -= DECREASE_VALUE;
	if (m_mulColor.x  < FADEOUT_FINISHED && 
		m_mulColor.y  < FADEOUT_FINISHED && 
		m_mulColor.z < FADEOUT_FINISHED) 
	{
		m_mulColor.x = FADEOUT_FINISHED;
		m_mulColor.y = FADEOUT_FINISHED;
		m_mulColor.z = FADEOUT_FINISHED;

		m_sptiteRender->SetMulColor(m_mulColor);
		g_goMgr->DeleteGameObject(this);
	}
	else {
		m_sptiteRender->SetMulColor(m_mulColor);
	}
}