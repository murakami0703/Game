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
		//何もない
		break;
	case Fade::Fadein:
	//フェードイン
		mulColorin = m_sptite->GetMulColor();

		mulColorin.w += 0.005f;
		if (mulColorin.w > 1.0f) {
			mulColorin.w = 1.0f;
			m_sptite->SetMulColor(mulColorin);
			return;
		}
		else {
			m_sptite->SetMulColor(mulColorin);
		}
	break;
	case Fade::FadeOut:
	//フェードアウト
		mulColorout = m_sptite->GetMulColor();

		mulColorout.w -= 0.05f;
		if (mulColorout.w < 0.0f) {
			mulColorout.w = 0.0f;
			m_sptite->SetMulColor(mulColorout);
			return;
		}
		else {
			m_sptite->SetMulColor(mulColorout);
		}
	break;
	}
}