#include "stdafx.h"
#include "HPManeger.h"

HPManeger* HPManeger::m_instance = nullptr;

HPManeger::HPManeger()
{
	m_instance = this;

}

HPManeger::~HPManeger()
{
}
HPSetPoint* HPManeger::HpSetPoint(float count)
{
	int clse = (int)count;
	return &m_hpPoint[clse];
}

void HPManeger::Update()
{

	for (auto& pHP : m_playerHPs) {
		pHP->Update();
	}
	//À•W‚ÌÝ’è
	{
		m_hpPoint[0].position = { -610.0f,340.0f,0.0f };
		m_hpPoint[1].position = { -610.0f,290.0f,0.0f };
		m_hpPoint[2].position = { -610.0f,340.0f,0.0f };
		m_hpPoint[3].position = { -610.0f,340.0f,0.0f };
		m_hpPoint[4].position = { -610.0f,340.0f,0.0f };
		m_hpPoint[5].position = { -610.0f,340.0f,0.0f };
		m_hpPoint[6].position = { -610.0f,340.0f,0.0f };
		m_hpPoint[7].position = { -610.0f,340.0f,0.0f };
		m_hpPoint[8].position = { -610.0f,340.0f,0.0f };
		m_hpPoint[9].position = { -610.0f,340.0f,0.0f };
		m_hpPoint[10].position = { -610.0f,340.0f,0.0f };
		m_hpPoint[11].position = { -610.0f,340.0f,0.0f };
	}

}
void HPManeger::Draw()
{
	for (auto& pHP : m_playerHPs) {
		pHP->Draw();
	}
}
