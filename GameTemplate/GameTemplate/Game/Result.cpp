#include "stdafx.h"
#include "Result.h"

Result* Result::m_instance = nullptr;

Result::Result()
{
	if (m_instance != nullptr) {
			std::abort();//���łɏo�Ă��邽�߃N���b�V��
		}
	m_instance = this;

	//�ӂ����
	m_font = g_goMgr->NewGameObject<FontRender>();
	const wchar_t* str = L"�����`�`�`�`�`�`�`";
	m_font->SetText(str);
	m_font->SetPosition({ -500.0f,0.0f });

	m_font->SetPivot({ 0.2f,0.2f });
	
}
Result::~Result()
{
	m_instance = nullptr;

}
void Result::Update()
{

}
void Result::Render()
{
}

void Result::PostRender() {}
