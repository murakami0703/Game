#include "stdafx.h"
#include "PlayerHP.h"


PlayerHP::PlayerHP()
{
	//HPÇÃòg
	m_hpHartFrame.Init(L"Assets/sprite/HPWaku.dds", 200.0f, 200.0f);
	//HP
	m_hpHart.Init(L"Assets/sprite/HP.dds", 200.0f, 200.0f);
}


PlayerHP::~PlayerHP()
{
}

void PlayerHP::Update()
{
	//çXêV

	m_hpHartFrame.Update(m_hpHFPos, CQuaternion::Identity(), m_hpHFScale);
	m_hpHart.Update(m_hpHPos, CQuaternion::Identity(), m_hpScale);
}
void PlayerHP::Draw()
{
	//ï`âÊèàóù
	m_hpHartFrame.Draw();
	m_hpHart.Draw();
}

