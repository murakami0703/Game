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
		{
		//フェードイン
			CVector4 mulColor = m_sptite->GetMulColor();

			mulColor.w += 0.005f;
			if (mulColor.w > 1.0f) {
				mulColor.w = 1.0f;
				m_sptite->SetMulColor(mulColor);
				return;
			}
			else {
				m_sptite->SetMulColor(mulColor);
			}
		}
	break;
	case Fade::FadeOut:
	{
		//フェードアウト
		CVector4 mulColor = m_sptite->GetMulColor();

		mulColor.w -= 0.05f;
		if (mulColor.w < 0.0f) {
			mulColor.w = 0.0f;
			m_sptite->SetMulColor(mulColor);
			return;
		}
		else {
			m_sptite->SetMulColor(mulColor);
		}
	}
	break;
	}
}