#include "stdafx.h"
#include "Fade.h"


Fade::Fade()
{

}


Fade::~Fade()
{
}

void Fade::Update()
{
	switch (m_state)
	{
	case Fade::None:
		//�����Ȃ�
		break;
	case Fade::Fadein:
	//�t�F�[�h�C��
		mulColorin = m_sptiteRender->GetMulColor();

		mulColorin.w += 0.005f;
		if (mulColorin.w > 1.0f) {
			mulColorin.w = 1.0f;
			m_sptiteRender->SetMulColor(mulColorin);
			return;
		}
		else {
			m_sptiteRender->SetMulColor(mulColorin);
		}
	break;
	case Fade::FadeOut:
	//�t�F�[�h�A�E�g
		mulColorout = m_sptiteRender->GetMulColor();

		mulColorout.w -= 0.05f;
		if (mulColorout.w < 0.0f) {
			mulColorout.w = 0.0f;
			m_sptiteRender->SetMulColor(mulColorout);
			return;
		}
		else {
			m_sptiteRender->SetMulColor(mulColorout);
		}
	break;
	}
}